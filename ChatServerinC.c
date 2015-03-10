/*
    C socket server example
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define MAX_BUFFER 2048
#define MAX_IP 20
#define MAX_USERNAME 1024
#define MAX_PASSWORD 1024

//struct client
typedef struct client_struct
{
    char ip[20];
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int busy;
    int online;
    int user_number;
    
    int session_key;
    struct client_struct *next;
    
} client_data;

//struct thread arguments
typedef struct args
{
    int thread_id;
    int client_socket;
    char client_ip[MAX_IP];
} thread_arguments;

//fungsi insert user
void insert_user(client_data **head, client_data user_data)
{
    client_data *temp = (client_data *) malloc(sizeof(client_data)), *iter = *head;
    strcpy(temp->username, user_data.username);
    strcpy(temp->password, user_data.password);
    temp->next = NULL;
    if(*head == NULL)
    {
        *head = temp;
    }
    else
    {
        while(iter->next != NULL)
        {
            iter = iter->next;
        }
        iter->next = temp;
    }
}

//fungsi set ip
void set_ip(client_data **head, client_data user, char ip[20])
{
    client_data *iter = *head;
    for(; iter != NULL; iter = iter->next)
    {
        if(strcmp(iter->username, user.username) == 0)
        {
            strcpy(iter->ip, ip);
            return;
        }
    }
}

//fungsi set user online
void set_user_online(client_data **head, client_data user)
{
    client_data *iter = *head;
    for(; iter != NULL; iter = iter->next)
    {
        if(strcmp(iter->username, user.username) == 0)
        {
            iter->online = 1;
            return;
        }
    }
}

//fungsi set user offline
void set_user_offline(client_data **head, client_data user)
{
    client_data *iter = *head;
    for(; iter != NULL; iter = iter->next)
    {
        if(strcmp(iter->username, user.username) == 0)
        {
            iter->online = 0;
            return;
        }
    }
}

//fungsi melihat user online
void show_online_users(client_data **head)
{
    client_data *iter = *head;
    printf("List of online users :\n");
    for(; iter != NULL; iter = iter->next)
    {
        if(iter->online == 1)
        {
            printf("%s\t\t%s\n", iter->ip, iter->username);
        }
    }
}

//fungsi melihat semua user
void show_all_users(client_data **head)
{
    client_data *iter = *head;
    printf("List of all users :\n");
    for(; iter != NULL; iter = iter->next)
    {
        printf("%s %s %d\n", iter->username, iter->password, iter->online);
    }
}

//fungsi kirim data user yang online P.S = Masih berupa stream
void send_data_online_users(client_data **head, int clisock)
{
    client_data *iter = *head;
    char garbage[MAX_BUFFER] = ""; //dump
    for(; iter != NULL; iter = iter->next)
    {
        if(iter->online == 1)
        {
            write(clisock,iter->username,strlen(iter->username));
            recv(clisock,garbage,MAX_BUFFER,0); //dump
        }
    }
    write(clisock,"done",strlen("done"));
    recv(clisock,garbage,MAX_BUFFER,0); //dump
}

//fungsi cek username ada atau tidak
bool username_exist(client_data **head, char username[MAX_USERNAME])
{
    client_data *iter = *head;
    for(; iter != NULL; iter = iter->next)
    {
        if(strcmp(iter->username, username) == 0)
        {
            return true;
        }
    }
    return false;
}

//fungsi user autentifikasi
bool user_authentication(client_data **head, client_data user)
{
    client_data *iter = *head;
    for(; iter != NULL; iter = iter->next)
    {
        if(strcmp(iter->username, user.username) == 0 && strcmp(iter->password, user.password) == 0)
        {
            return true;
        }
    }
    return false;
}

//fungsi hapus user
void delete_user(client_data **head, char username_find[MAX_USERNAME])
{
    client_data *iter = *head, *prev = NULL;
    for(; iter != NULL; prev = iter, iter = iter->next)
    {
        if(strcmp(iter->username, username_find) == 0)
        {
            if(iter == *head)
            {
                *head = iter->next;
            }
            else
            {
                prev->next = iter->next;
            }
            iter->next = NULL;
            free(iter);
            return;
        }
        else
        {
            printf("USERNAME YANG DIMASUKKAN TIDAK VALID");
            break;
        }
    }
}

//fungsi hapus semua data user
void delete_all(client_data **head)
{
    client_data *iter = *head, *prev = NULL;
    for(; iter != NULL; prev = iter, iter = iter->next)
    {
        if(iter == *head)
        {
            *head = iter->next;
        }
        else
        {
            prev->next = iter->next;
        }
        iter->next = NULL;
        free(iter);
    }
}

client_data *head = NULL; //pointer linked list
char users_online[20][20]; //belum diimplementasi
int user_count = 0; //belum diimplementasi


//fungsi signup
void signup(client_data *connected_user, int client_socket, char client_ip[MAX_IP])
{
    char username[MAX_USERNAME] = "",
    password[MAX_PASSWORD] = "",
    garbage[MAX_BUFFER] = "";
    
    write(client_socket,"Please enter username:",strlen("Please enter username\n"));
    recv(client_socket,username,MAX_BUFFER,0);
    
    write(client_socket,"Please enter password:",strlen("Please enter password\n"));
    recv(client_socket,password,MAX_BUFFER,0);
    
    if(!username_exist(&head, username))
    {
        strcpy(connected_user->username, username);
        strcpy(connected_user->password, password);
    
        insert_user(&head, *connected_user);
        set_ip(&head, *connected_user, client_ip);
        set_user_online(&head, *connected_user);
        
        write(client_socket,"Signup Success!\n",strlen("Signup Success!\n"));
        recv(client_socket,garbage,MAX_BUFFER,0);
        printf("%s is connected with ip = %s\n", connected_user->username, connected_user->ip);
    }
    else
    {
        write(client_socket,"Invalid username or password\n",strlen("Invalid username or password\n"));
        recv(client_socket,garbage,MAX_BUFFER,0);
    }
}

//fungsi login
void login(client_data *connected_user, int client_socket, char client_ip[MAX_IP])
{
    char username[MAX_USERNAME] = "",
    password[MAX_PASSWORD] = "",
    garbage[MAX_BUFFER] = "";
    
    int not_valid = 1; //variable cek autentifikasi

    write(client_socket,"Please enter username:",strlen("Please enter username\n"));
    recv(client_socket,username,MAX_BUFFER,0);
    
    write(client_socket,"Please enter password:",strlen("Please enter password\n"));
    recv(client_socket,password,MAX_BUFFER,0);
    
    strcpy(connected_user->username, username);
    strcpy(connected_user->password, password);
    
    //Autentikasi
    if(user_authentication(&head, *connected_user) == true)
    {
        write(client_socket,"Authenticated\n",strlen("Authenticated\n"));
        recv(client_socket,garbage,MAX_BUFFER,0);
        set_user_online(&head, *connected_user);
        set_ip(&head, *connected_user, client_ip);
        //strcpy(connected_user->ip, client_ip);
        not_valid=0;
        printf("%s is connected with ip = %s\n", connected_user->username, connected_user->ip);
    }
    
    if(not_valid==1)
    {
        write(client_socket,"Invalid username or password\n",strlen("Invalid username or password\n"));
        recv(client_socket,garbage,MAX_BUFFER,0);
    }
}

//fungsi handler menggunakan thread
void *user_handler(void *arguments)
{
    //Autentikasi user
    thread_arguments *user = arguments;
    char mode[MAX_BUFFER] = "",
         username[MAX_USERNAME] = "",
         password[MAX_PASSWORD] = "",
         garbage[MAX_BUFFER] = "";
    
    client_data connected_user;
    
    write(user->client_socket,"signup or login? <type it with lowercase>",strlen("Signup or login? <type it type it with lowercase>\n"));
    recv(user->client_socket,mode,MAX_BUFFER,0);
    
    if(strcmp(mode, "signup") == 0)
    {
        signup(&connected_user, user->client_socket, user->client_ip);
    }
    else
    if(strcmp(mode, "login") == 0)
    {
        login(&connected_user, user->client_socket, user->client_ip);
    }
    else
    {
        write(user->client_socket,"ERROR INPUT!!!\n",strlen("ERROR INPUT!!!\n"));
        recv(user->client_socket,garbage,MAX_BUFFER,0);
    }
    
    show_online_users(&head);
    
    char client_message[MAX_BUFFER];
    int read_size;
    
    send_data_online_users(&head, user->client_socket); //kirim list nama
    
    //Menerima pesan dari client
    
    while( (read_size = recv(user->client_socket , client_message , MAX_BUFFER , 0)) > 0 )
    {
        //Mengirim pesan kembali ke client
        write(user->client_socket , client_message , strlen(client_message));
        puts(client_message);
        memset(&client_message[0], 0, sizeof(client_message));
        
    }
    
    if(read_size == 0)
    {
        puts("Client disconnected");
        set_user_offline(&head, connected_user);
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    
    return NULL;
}

int main(int argc , char *argv[])
{
    int socket_desc, //variable menyimpan tipe socket
        client_sock, //variable socket client
        conn, //variable koneksi
        thread_counter = 0, //thread id counter
        read_size; //variable membaca size
    
    pthread_t tid;
    
    thread_arguments arguments;
    
    struct sockaddr_in server , client;
    
    char str[INET_ADDRSTRLEN],
         username[MAX_USERNAME] = "",
         password[MAX_PASSWORD] = "",
         garbage[MAX_BUFFER] = ""; //dump
    
    srand(time(NULL));
    
    //data user P.S masih di deklarasi di awal, belum membuat sendiri
    client_data user1;
    client_data user2;
    client_data user3;
    
    strcpy(user1.username, "vijay");
    strcpy(user1.password, "vertikaldash");
    insert_user(&head, user1);
    set_user_offline(&head, user1);
    //client_database[0].busy=0;
    //client_database[0].online=0;
    //client_database[0].user_number=0;
    strcpy(user2.username,"feeljay");
    strcpy(user2.password,"feels");
    insert_user(&head, user2);
    set_user_offline(&head, user2);
    //client_database[1].busy=0;
    //client_database[1].online=0;
    //client_database[1].user_number=0;
    strcpy(user3.username,"nofeel");
    strcpy(user3.password,"demfeel");
    insert_user(&head, user3);
    set_user_offline(&head, user3);
    //client_database[2].busy=0;
    //client_database[2].online=0;
    //client_database[2].user_number=0;

    //Buat socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Menyiapkan struktur sockaddr_in
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print pesan error
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and koneksi masuk
    puts("Waiting for incoming connections...");
    conn = sizeof(struct sockaddr_in);

    //Menerima koneksi dari client
    while(1)
    {
        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&conn);
        //Incrementing usercount
        inet_ntop(AF_INET, &(client.sin_addr), str, INET_ADDRSTRLEN); //extracting ip address
        printf("%s\n", str); // print ip address e.x = "192.0.2.33"

            if (client_sock < 0)
            {
                perror("accept failed");
                return 1;
            }
            puts("Connection accepted");
        
            arguments.thread_id = thread_counter;
            arguments.client_socket = client_sock;
            strcpy(arguments.client_ip, str);
        
            if(pthread_create(&tid, NULL, &user_handler, (void *)&arguments) != 0)
            {
                printf("error while creating thread!\n");
            }
            else
            {
                printf("thread has been created!\n");
            }
        
    }
    return pthread_join(tid, NULL);
}

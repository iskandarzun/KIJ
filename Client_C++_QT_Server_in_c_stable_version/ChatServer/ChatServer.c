/*
 C socket server
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

#define MAX_BUFFER 8192
#define MAX_STRING 4096
#define MAX_IP 20
#define MAX_USERNAME 1024
#define MAX_PASSWORD 1024
#define AES_MODE 128 //AES-128, AES-192, AES-256

//struct client data
typedef struct client_struct
{
    char ip[MAX_IP];
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int busy;
    int online;
    int session_key;
    int socket;
    struct client_struct *next;
} client_data;

//struct thread arguments
typedef struct args
{
    int thread_id;
    int client_socket;
    char client_ip[MAX_IP];
} thread_arguments;

client_data *head = NULL; //pointer linked list
char users_online[20][20]; //belum diimplementasi
int user_count = 0; //belum diimplementasi

/******************************
****** Enkripsi AES + OFB *****
*******************************/
#define Nb 4
#define MAX_BUFF_DIVIDE MAX_BUFFER / 32
#define MAX_DIVIDE MAX_STRING / 16

// Round dalam AES, Inisialisasi = 0
int Nr=0;

// satuan bit Key, Inisialisasi = 0
int Nk=0;

int getSBoxValue(int num)
{
    int sbox[256] =   {
        //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }; //F
    return sbox[num];
}

// The round constant word array, Rcon[i], contains the values given by
// x to th e power (i-1) being powers of x (x is denoted as {02}) in the field GF(28)
// Note that i starts at 1, not 0).
int Rcon[255] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
    0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
    0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
    0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
    0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
    0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
    0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
    0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
    0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb  };

// Ekspansi key
void KeyExpansion(unsigned char RoundKey[240], unsigned char Key[32])
{
    int i,j;
    unsigned char temp[4],k;
    
    // round key pertama.
    for(i=0;i<Nk;i++)
    {
        RoundKey[i*4]=Key[i*4];
        RoundKey[i*4+1]=Key[i*4+1];
        RoundKey[i*4+2]=Key[i*4+2];
        RoundKey[i*4+3]=Key[i*4+3];
    }
    
    // round key untuk round lainnya.
    while (i < (Nb * (Nr+1)))
    {
        for(j=0;j<4;j++)
        {
            temp[j]=RoundKey[(i-1) * 4 + j];
        }
        if (i % Nk == 0)
        {
            // Fungsi rotasi 4 byte ke kiri.
            // [a0,a1,a2,a3] jadi [a1,a2,a3,a0]
            
            // Fungsi RotWord()
            {
                k = temp[0];
                temp[0] = temp[1];
                temp[1] = temp[2];
                temp[2] = temp[3];
                temp[3] = k;
            }
            
            // SubWord() fungsi yang mengambil 4 byte word
            // dan dilakukan subtitusi terhadap S-Box.
            
            // Fungsi Subword()
            {
                temp[0]=getSBoxValue(temp[0]);
                temp[1]=getSBoxValue(temp[1]);
                temp[2]=getSBoxValue(temp[2]);
                temp[3]=getSBoxValue(temp[3]);
            }
            
            temp[0] =  temp[0] ^ Rcon[i/Nk];
        }
        else if (Nk > 6 && i % Nk == 4)
        {
            // Function Subword()
            {
                temp[0]=getSBoxValue(temp[0]);
                temp[1]=getSBoxValue(temp[1]);
                temp[2]=getSBoxValue(temp[2]);
                temp[3]=getSBoxValue(temp[3]);
            }
        }
        RoundKey[i*4+0] = RoundKey[(i-Nk)*4+0] ^ temp[0];
        RoundKey[i*4+1] = RoundKey[(i-Nk)*4+1] ^ temp[1];
        RoundKey[i*4+2] = RoundKey[(i-Nk)*4+2] ^ temp[2];
        RoundKey[i*4+3] = RoundKey[(i-Nk)*4+3] ^ temp[3];
        i++;
    }
}

// Fungsi menambahkan round key terhadap state.
// Round key ditambahkan dengan XOR function.
void AddRoundKey(unsigned char RoundKey[240], int round, unsigned char state[4][4])
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[j][i] ^= RoundKey[round * Nb * 4 + i * Nb + j];
        }
    }
}

// SubBytes adalah fungsi subtitusi nilai
// array state dengan nilai di S-box.
void SubBytes(unsigned char state[4][4])
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[i][j] = getSBoxValue(state[i][j]);
            
        }
    }
}

// Fungsi ShiftRows() adalah fungsi menggeser array ke kiri.
// Setiap row digeser dengan perbedaan offset.
// Offset = nomor Row. Jadi row awal(row ke 0) tidak digeser.
void ShiftRows(unsigned char state[4][4])
{
    unsigned char temp;
    
    // Rotasi row pertama 1 kolom ke kiri
    temp=state[1][0];
    state[1][0]=state[1][1];
    state[1][1]=state[1][2];
    state[1][2]=state[1][3];
    state[1][3]=temp;
    
    // Rotasi row kedua 2 kolom ke kiri
    temp=state[2][0];
    state[2][0]=state[2][2];
    state[2][2]=temp;
    
    temp=state[2][1];
    state[2][1]=state[2][3];
    state[2][3]=temp;
    
    // Rotasi row ketiga 3 kolom ke kiri
    temp=state[3][0];
    state[3][0]=state[3][3];
    state[3][3]=state[3][2];
    state[3][2]=state[3][1];
    state[3][1]=temp;
}

// xtime adalah variabel macro untuk menemukan product dari {02} dan argument xtime modulo {1b}
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

// MixColumns function mixes the columns of the state matrix
void MixColumns(unsigned char state[4][4])
{
    int i;
    unsigned char Tmp,Tm,t;
    for(i=0;i<4;i++)
    {
        t=state[0][i];
        Tmp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i] ;
        Tm = state[0][i] ^ state[1][i] ; Tm = xtime(Tm); state[0][i] ^= Tm ^ Tmp ;
        Tm = state[1][i] ^ state[2][i] ; Tm = xtime(Tm); state[1][i] ^= Tm ^ Tmp ;
        Tm = state[2][i] ^ state[3][i] ; Tm = xtime(Tm); state[2][i] ^= Tm ^ Tmp ;
        Tm = state[3][i] ^ t ; Tm = xtime(Tm); state[3][i] ^= Tm ^ Tmp ;
    }
}

// Cipher adalah main function yang mengenkripsi PlainText.
void Cipher(unsigned char RoundKey[240], unsigned char in[16], unsigned char out[16], unsigned char state[4][4])
{
    int i,j,round=0;
    
    //Copy input PlainText ke state array.
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[j][i] = in[i*4 + j];
        }
    }
    
    // Tambahkan round key pertama ke state sebelum memulai rounds.
    AddRoundKey(RoundKey, 0, state);
    
    // Akan ada rounds sebanyak Nr.
    // Nr-1 rounds pertama identik.
    // Nr-1 rounds dijalankan dengan loop dibawah.
    for(round=1;round<Nr;round++)
    {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(RoundKey, round, state);
    }
    
    // Round terakhir.
    // Fungsi MixColumns tidak dilakukan di round ini.
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(RoundKey, Nr, state);
    
    // Proses enkripsi berakhir.
    // Copy state array ke output array.
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            out[i*4+j]=state[j][i];
        }
    }
}

// Fungsi ubah hex->digit
char hexDigit(unsigned n)
{
    if (n < 10) {
        return n + '0';
    } else {
        return (n - 10) + 'A';
    }
}

// Fungsi ubah char->hex
void charToHex(char c, char hex[2])
{
    hex[0] = hexDigit(c / 0x10);
    hex[1] = hexDigit(c % 0x10);
    //hex[2] = '\0';
}

// Fungsi ubah hex->Ascii
char hexToAscii(char first, char second)
{
    char hex[5], *stop;
    hex[0] = '0';
    hex[1] = 'x';
    hex[2] = first;
    hex[3] = second;
    hex[4] = 0;
    return strtol(hex, &stop, 16);
}


// Fungsi ubah unsigned char -> char
void uncharToChar(char *dst, unsigned char *src,size_t src_len)
{
    while (src_len--)
        dst += sprintf(dst,"%02x",*src++);
    *dst = '\0';
}

// Fungsi ubah string hex -> ascii
void convertToReal(char *dest, char *source)
{
    int i;
    int count = 0;
    for(i = 0; i < strlen(source)/2; i++)
    {
        if(source[count] == '0' && source[count+1] == '0')
        {
            dest[i] = 0;
        }
        else
        {
            dest[i] = hexToAscii(source[count], source[count+1]);
        }
        
        count += 2;
    }
}

// Fungsi menyimpan hex value per array
void containHex(char dest[MAX_BUFFER][1], char *source)
{
    int i;
    int count = 0;
    for(i = 0; i < strlen(source)/2; i++)
    {
        dest[i][0] = hexToAscii(source[count], source[count+1]);
        count += 2;
    }
}

// Fungsi char -> hex versi 2
void char2hex(char* A, char *Hex) {
    int i=0;
    int j=0;
    int t;
    char temp[32];
    
    while(A[i] != '\0') {
        
        //printf("%d %lu\n", i, strlen(A));
        
        t = A[i] >> 4;
        if (t < 10) {
            temp[j] = '0' + t;
        }
        else {
            temp[j] = 'a' + t - 10;
        }
        j++;
        t = A[i] % 16;
        if (t < 10) {
            temp[j] = '0' + t;
        }
        else {
            temp[j] = 'a' + t - 10;
        }
        j++;
        i++;
    }
    
    for(i = 0; i < (int)strlen(A)*2; i++)
    {
        Hex[i] = temp[i];
    }
}

// Fungsi xor versi 2
void xor_str(char *A, char *B, char *res) {
    int i = 0;
    int a, b, x;
    
    while (A[i] != 0) {//kalau belum null
        if (A[i] >= '0' && A[i] <= '9') {
            a = A[i] - '0';
        }
        else if (A[i] >= 'a' && A[i] <= 'z'){
            a = A[i] - 'a' + 10;
        }
        if (B[i] >= '0' && B[i] <= '9') {
            b = B[i] - '0';
        }
        else if (B[i] >= 'a' && B[i] <= 'z'){
            b = B[i] - 'a' + 10;
        }
        x = a ^ b;
        if (x < 10) {
            res[i] = '0' + x;
        }
        else {
            res[i] = 'a' + x - 10;
        }
        i++;
    }
    res[i] = 0;
}

// Fungsi XOR
char *xor(char *source1, int src_sz, char *source2) {
    
    int i, j = 0;
    int k_len = strlen(source2);
    char *result = calloc(src_sz+1, sizeof(char));
    
    for (i = 0; i < src_sz; i++) {
        result[i] = source1[i] ^ source2[j];
        j++;
        j = j > k_len ? 0 : j;
        //printf("perulangan -> %d\nlength -> %d\nkarakter -> %c\n", i, src_sz, result[i]);
    }
    return result;
}

// Fungsi memisah menjadi 16 byte input
void divideAscii(char dest[MAX_DIVIDE][17], char *source)
{
    int i, j, part;
    part = (strlen(source) - 1) / 16;
    //printf("part : %d\nlength : %d\n", part, strlen(source));
    for(i = 0; i <= part; i++)
    {
        memset(&dest[i][0], 0, sizeof(dest[i]));
        for(j = i * 16; j < ((i+1) * 16); j++)
        {
            if(j >= strlen(source))
            {
                dest[i][j] = '\0';
                break;
            }
            dest[i][j%16] = source[j];
            //printf("karakter : %c\n", source[j]);
            //printf("%d -> %d\n", j, strlen(dest[i]));
            
        }
    }
    //printf("%d\n", strlen(dest[0]));
}

void divideHexa(char dest[MAX_BUFFER][33], char *source)
{
    int i, j, part;
    part = (strlen(source) - 1) / 32;
    for(i = 0; i <= part; i++)
    {
        memset(&dest[i][0], 0, sizeof(dest[i]));
        for(j = i * 32; j < ((i+1) * 32); j++)
        {
            if(j >= (int)strlen(source))
            {
                dest[i][j] = '\0';
                break;
            }
            dest[i][j%32] = source[j];
        }
    }
}

void AES_Encrypt(char* input, char *output)
{
    //Enkripsi
    
    // in - array dari pesan yang dienkripsi.
    // out - array hasil enkripsi.
    // state - array hasil sementara enkripsi.
    unsigned char in[16], out[16], state[4][4];
    
    // Round key.
    unsigned char RoundKey[240];
    
    // key input
    unsigned char Key[32];
    
    char convert[MAX_BUFFER] = "";
    char real[MAX_STRING] = "";
    char result[MAX_BUFFER][33];
    int b, i, blocksIV, blocksAscii;

    //assign Nk dan Nr
    Nk = AES_MODE / 32;
    Nr = Nk + 6;
    
    //Initialization Vector 16 byte
    char IV[17] = "0123456789abcdef";
    
    //Key Enkripsi
    unsigned char tempkey[32] = {0x00  ,0x01  ,0x02  ,0x03  ,0x04  ,0x05  ,0x06  ,0x07  ,0x08  ,0x09  ,0x0a  ,0x0b  ,0x0c  ,0x0d  ,0x0e  ,0x0f};
    
    for(i=0;i<Nk*4;i++)
    {
        Key[i]=tempkey[i];
    }
    
    blocksAscii = ((strlen(input) - 1) / 16);
    
    //dipisah 16 byte
    char partAscii[MAX_DIVIDE][17];
    divideAscii(partAscii, input);
    
    char hasilxorencrypt[MAX_BUFF_DIVIDE][33];
    
    //Mulai enkripsi
    for (int ba = 0; ba <= blocksAscii; ba++)
    {
        if(ba == 0)
        {
            blocksIV = ((strlen(IV) - 1) / 16);
            //printf("jumlah : %d\n", blocksIV);
        }
        else
        {
            blocksIV = ((strlen(convert) - 1) / 16);
        }
        
        for(b = 0; b <= blocksIV; b++)
        {
            for(i = 0; i < Nb*4; i++)
            {
                if(ba == 0)
                {
                    if((i + (b * 16) < strlen(IV)))
                    {
                        in[i] = (unsigned char)IV[ (i + (b * 16) ) ];
                    }
                    else
                    {
                        in[i] = 0x00;
                    }
                }
                else
                {
                    if((i + (b * 16) < strlen(convert)))
                    {
                        in[i] = (unsigned char)convert[ (i + (b * 16) ) ];
                    }
                    else
                    {
                        in[i] = 0x00;
                    }
                }
            }
            
            printf("\n");
            
            printf("hexadecimal in in: ");
            
            for(i=0;i<Nb*4;i++)
            {
                printf("%02x ", in[i]);
            }
            printf("\n");
            
            // Fungsi KeyExpansion untuk ekspan key
            KeyExpansion(RoundKey, Key);
            
            // Fungsi Cipher
            Cipher(RoundKey, in, out, state);
            
            // Output encrypted text.
            printf("\nText after encryption:\n");
            
            printf("Encryption : ");
            
            for(i=0;i<Nb*4;i++)
            {
                printf("%02x ", out[i]);
            }
            printf("\n\n");
            
            char tempconvert[16];
            uncharToChar(tempconvert, out, sizeof(out));
            
            memset(&convert[0], 0, sizeof(convert));
            strcat(convert, tempconvert);
            
            memset(&in[0], 0, sizeof(in));
            memset(&out[0], 0, sizeof(out));
        }
        
        char plainInHex[33];
        char xorResult[MAX_BUFFER];
        char convSelected[MAX_BUFFER];
        
        memset(&convSelected[0], 0, sizeof(convSelected));
        strncpy(convSelected, convert, strlen(partAscii[ba])*2);
        char2hex(partAscii[ba], plainInHex);
        xor_str(plainInHex, convSelected, xorResult);
        
        strcpy(hasilxorencrypt[ba], xorResult);
        strcpy(result[ba], hasilxorencrypt[ba]);
        
        printf("blok ke : %d\n", ba);
        printf("panjang convert %lu -> %s\n", strlen(convert), convert);
        printf("partAscii -> %s\npanjang partAscii -> %lu\nkali 2 -> %lu\n", partAscii[ba], strlen(partAscii[ba]), strlen(partAscii[ba])*2);
        printf("panjang hexaAscii %lu -> %s\n", strlen(plainInHex), plainInHex);
        printf("panjang convertSelected %lu -> %s\n", strlen(convSelected), convSelected);
        printf("panjang hasilxorencrypt %lu -> %s\n", strlen(hasilxorencrypt[ba]), hasilxorencrypt[ba]);
        
        char tempConvResult[MAX_BUFFER];
        convertToReal(tempConvResult, convSelected);
        memset(&convert[0], 0, sizeof(convert));
        strcpy(convert, tempConvResult);
        memset(&plainInHex[0], 0, sizeof(plainInHex));
        memset(&xorResult[0], 0, sizeof(xorResult));
    }
    
    char encrypted_message[MAX_BUFFER];
    memset(&encrypted_message[0], 0, sizeof(encrypted_message));
    
    for(i = 0; i <= blocksAscii; i++)
    {
        strcat(encrypted_message, result[i]);
        memset(&result[i][0], 0, sizeof(result[i]));
    }
    
    strcpy(output, encrypted_message);
}

void AES_Decrypt(char* input, char*output)
{
    // in - array dari pesan yang dienkripsi.
    // out - array hasil enkripsi.
    // state - array hasil sementara enkripsi.
    unsigned char in[16], out[16], state[4][4];
    
    // Round key.
    unsigned char RoundKey[240];
    
    // key input
    unsigned char Key[32];

    char convert[MAX_BUFFER] = "";
    char coba[MAX_STRING][17];
    int b, i, blocksIV, blocksHexa;
    
    //assign Nk dan Nr
    Nk = AES_MODE / 32;
    Nr = Nk + 6;
    
    //Initialization Vector 16 byte
    char IV[17] = "0123456789abcdef";
    
    //Key Enkripsi
    unsigned char tempkey[32] = {0x00  ,0x01  ,0x02  ,0x03  ,0x04  ,0x05  ,0x06  ,0x07  ,0x08  ,0x09  ,0x0a  ,0x0b  ,0x0c  ,0x0d  ,0x0e  ,0x0f};
    
    for(i=0;i<Nk*4;i++)
    {
        Key[i]=tempkey[i];
    }
    
    blocksHexa = ((strlen(input) - 1) / 32);
    
    //dipisah 16 byte
    char partHexa[MAX_BUFFER][33];
    divideHexa(partHexa, input);
    
    char hasilxordecrypt[MAX_BUFF_DIVIDE][33];
    
    //Mulai enkripsi
    for (int ba = 0; ba <= blocksHexa; ba++)
    {
        if(ba == 0)
        {
            blocksIV = ((strlen(IV) - 1) / 16);
            //printf("jumlah : %d\n", blocksIV);
        }
        else
        {
            blocksIV = ((strlen(convert) - 1) / 16);
        }
        
        for(b = 0; b <= blocksIV; b++)
        {
            for(i=0;i<Nb*4;i++)
            {
                if(ba == 0)
                {
                    if((i + (b * 16) < (int)strlen(IV)))
                    {
                        in[i] = (unsigned char)IV[ (i + (b * 16) ) ];
                    }
                    else
                    {
                        in[i] = 0x00;
                    }
                }
                else
                {
                    if((i + (b * 16) < (int)strlen(convert)))
                    {
                        in[i] = (unsigned char)convert[ (i + (b * 16) ) ];
                    }
                    else
                    {
                        in[i] = 0x00;
                    }
                }
            }
            
            // Fungsi KeyExpansion untuk ekspan key
            KeyExpansion(RoundKey, Key);
            
            // Fungsi Cipher
            Cipher(RoundKey, in, out, state);
            
            char tempconvert[33];
            uncharToChar(tempconvert, out, sizeof(out));
            
            memset(&convert[0], 0, sizeof(convert));
            strcat(convert, tempconvert);
            
            memset(&in[0], 0, sizeof(in));
            memset(&out[0], 0, sizeof(out));
        }
        
        char tempRes[MAX_BUFFER];
        char convSelected2[MAX_BUFFER];
        
        memset(&convSelected2[0], 0, sizeof(convSelected2));
        strncpy(convSelected2, convert, strlen(partHexa[ba]));
        xor_str(partHexa[ba], convSelected2, tempRes);
        
        strcpy(hasilxordecrypt[ba], tempRes);
        printf("Encrypted message dengan panjang %lu -> %s\n", strlen(partHexa[ba]), partHexa[ba]);
        printf("panjang convertSelected2 %lu -> %s\n", strlen(convSelected2), convSelected2);
        printf("hasil xor ke %d -> %s\n", ba, hasilxordecrypt[ba]);
        
        char tempConvResult[MAX_BUFFER];
        convertToReal(tempConvResult, convSelected2);
        memset(&convert[0], 0, sizeof(convert));
        strcpy(convert, tempConvResult);
        memset(&tempRes[0], 0, sizeof(tempRes));
        
        convertToReal(coba[ba], hasilxordecrypt[ba]);
    }
    
    char decrypted_message[MAX_STRING];
    memset(&decrypted_message[0], 0, sizeof(decrypted_message));
    
    for(i = 0; i <= blocksHexa; i++)
    {
        strcat(decrypted_message, coba[i]);
        memset(&coba[i][0], 0, sizeof(coba[i]));
    }
    
    strcpy(output, decrypted_message);
}

/******************************
 ********* End of AES *********
 ******************************/

//fungsi write data (encrypt here)
void send_data(int socket, char output[MAX_STRING])
{
    char encrypted_message[MAX_BUFFER];
    
    AES_Encrypt(output, encrypted_message);
    
    printf("pesan :\npanjang = %lu\nmessage -> %s\n", strlen(output), output);
    
    printf("enkripsi :\npanjang = %lu\nmessage -> %s\n", strlen(encrypted_message), encrypted_message);

    write(socket,encrypted_message,strlen(encrypted_message));
    
    memset(&encrypted_message[0], 0, sizeof(encrypted_message));
}

//fungsi read data (decrypt here)
int read_data(int socket, char input[MAX_STRING])
{
    char decrypted_message[MAX_BUFFER];
    int read_size;
    
    read_size = recv(socket , decrypted_message , MAX_BUFFER , 0);
    
    AES_Decrypt(decrypted_message, input);
    
    printf("pesan :\npanjang = %lu\nmessage -> %s\n", strlen(decrypted_message), decrypted_message);
    
    printf("hasil dekripsi :\npanjang = %lu\nmessage -> %s\n", strlen(input), input);
    
    return read_size;
}

//fungsi format untuk pesan protocol
void format_message(char output[MAX_STRING], char state[20], char flag[30], char receiver[MAX_USERNAME], char sender[MAX_USERNAME], char content_type[10], char content[MAX_STRING/2])
{
    strcpy(output, state);
    strcat(output, "\r\n");
    strcat(output, flag);
    strcat(output, "\r\n");
    strcat(output, receiver);
    strcat(output, "\r\n");
    strcat(output, sender);
    strcat(output, "\r\n");
    strcat(output, content_type);
    strcat(output, "\r\n");
    strcat(output, content);
}

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
            iter->socket = user.socket;
            iter->session_key = user.session_key;
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
            iter->session_key = 0;
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

//fungsi sementara kirim data users
void send_data_online_users(client_data **head, int clisock, char username[MAX_USERNAME])
{
    client_data *iter = *head;
    char data_users[MAX_STRING/2];
    printf("SEBELUM KIRIM\n");
    for(; iter != NULL; iter = iter->next)
    {
        if(iter->online == 1)
        {
            strcat(data_users, iter->username);
            strcat(data_users, ":");
            printf("%s online\n", iter->username);
        }
    }
    
    
    char output[MAX_STRING];
    format_message(output, "LIST_USER","LIST_USER_SEND","0",username,"LIST",data_users);
    send_data(clisock,output);
    printf("SESUDAH KIRIM, panjang = %d\n", (int)strlen(output));
    
    memset(&output[0], 0, sizeof(output));
}

//fungsi kirim data user yang baru online P.S = Masih berupa stream
void broadcast_user_availability(client_data **head, char except[MAX_USERNAME], char state[10])
{
    client_data *iter = *head;
    
    printf("SEBELUM BROADCAST\n");
    
    /*
    for(; iter != NULL; iter = iter->next)
    {
        if(iter->online == 1)
        {
            strcat(data_users, iter->username);
            strcat(data_users, ":");
            //printf("ada si : %s\n", iter->username);
        }
    }*/
    
    char output[MAX_STRING];
    if(strcmp(state, "ONLINE") == 0)
    {
        format_message(output, "LIST_USER","LIST_USER_SEND_ONLINE","0","0","LIST",except);
    }
    else
    if (strcmp(state, "OFFLINE") == 0)
    {
        format_message(output, "LIST_USER","LIST_USER_SEND_OFFLINE","0","0","LIST",except);
    }
    
    //iter = *head;
    for(; iter != NULL; iter = iter->next)
    {
        if(iter->online == 1 && strcmp(iter->username, except) != 0)
        {
            send_data(iter->socket, output);
            //printf("kirim ke : %s\n", iter->username);
        }
    }
    memset(&output[0], 0, sizeof(output));
    printf("SESUDAH BROADCAST\n");
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


//fungsi cek session
bool check_session(client_data **head, client_data *connected_user, int session_key)
{
    client_data *iter = *head;
    for(; iter != NULL; iter = iter->next)
    {
        if((strcmp(iter->username, connected_user->username) == 0) && (iter->session_key == session_key))
        {
            return true;
        }
    }
    return false;
}

//fungsi cek session exist
bool is_session_exist(client_data **head, int session_key)
{
    client_data *iter = *head;
    for(; iter != NULL; iter = iter->next)
    {
        if(iter->session_key == session_key)
        {
            return true;
        }
    }
    return false;
}



//fungsi get receiver socket
int get_receiver_socket(client_data **head, char receiver[MAX_USERNAME])
{
    client_data *iter = *head;
    for(; iter != NULL; iter = iter->next)
    {
        if(strcmp(iter->username, receiver) == 0 && iter->online == 1)
        {
            return iter->socket;
        }
    }
    return -1;
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

//fungsi strip pesan sesuai protocol
void strip_message(char output[6][MAX_STRING], char buffer[MAX_STRING])
{
    char *container;
    int counter = 0;
    container = strtok (buffer,"\r\n");
    strcpy(output[counter], container); //sini
    counter++;
    while (container != NULL && counter <= 5)
    {
        container = strtok (NULL, "\r\n");
        strcpy(output[counter], container);
        counter++;
    }
}

//fungsi free buffer
void clear_buffer_protocol(char buffer_protocol[6][MAX_STRING])
{
    int counter;
	for(counter = 0; counter <= 5; counter++)
    {
        memset(&buffer_protocol[counter][0], 0, sizeof(buffer_protocol[counter]));
    }
}

//fungsi signup
void signup(client_data *connected_user, char client_ip[MAX_IP], char username[MAX_USERNAME], char password[MAX_PASSWORD])
{
    char output[MAX_STRING] = "",
         input[MAX_STRING] = "",
         user_and_session[MAX_STRING] = "",
         buffer_protocol[6][MAX_STRING];
    
    if(!username_exist(&head, username))
    {
        strcpy(connected_user->username, username);
        strcpy(connected_user->password, password);
        
        //session key give
        int random_number = rand();
        char buffer_random[MAX_STRING] = "";
        
        while (is_session_exist(&head, random_number))
        {
            random_number = rand();
        }
        
        connected_user->session_key = random_number;
        
        insert_user(&head, *connected_user);
        set_ip(&head, *connected_user, client_ip);
        set_user_online(&head, *connected_user);
        
        sprintf(buffer_random, "%d", random_number);
        
        strcpy(user_and_session, connected_user->username);
        strcat(user_and_session, ":");
        strcat(user_and_session, buffer_random);
        
        format_message(output, "LIST_USER", "SIGNUP_SUCCESS", "0", user_and_session, "NULL", "NULL");
        send_data(connected_user->socket, output);
        
        broadcast_user_availability(&head, connected_user->username, "ONLINE");
        printf("%s is connected with ip = %s\n", connected_user->username, connected_user->ip);
        memset(&output[0], 0, sizeof(output));
    }
    else
    {
        format_message(output, "SIGNUP", "SIGNUP_FAILED", "0", "0", "NULL", "NULL");
        send_data(connected_user->socket, output);
        
        memset(&output[0], 0, sizeof(output));
    }
}

//fungsi login
void login(client_data *connected_user, char client_ip[MAX_IP], char username[MAX_USERNAME], char password[MAX_PASSWORD])
{
    char output[MAX_STRING] = "",
         input[MAX_STRING] = "",
         user_and_session[MAX_STRING] = "",
         buffer_protocol[6][MAX_STRING];
    
    strcpy(connected_user->username, username);
    strcpy(connected_user->password, password);
    
    //Autentikasi
    if(user_authentication(&head, *connected_user) == true)
    {
        //session key give
        int random_number = rand();
        char buffer_random[MAX_STRING] = "";
        
        while (is_session_exist(&head, random_number))
        {
            random_number = rand();
        }
        
        connected_user->session_key = random_number;
        
        set_user_online(&head, *connected_user);
        set_ip(&head, *connected_user, client_ip);
        
        sprintf(buffer_random, "%d", random_number);
        
        strcpy(user_and_session, connected_user->username);
        strcat(user_and_session, ":");
        strcat(user_and_session, buffer_random);
        
        format_message(output, "LIST_USER", "LOGIN_SUCCESS", "0", user_and_session, "NULL", "NULL");
        send_data(connected_user->socket, output);
        
        printf("%s is connected with ip = %s\n", connected_user->username, connected_user->ip);
        broadcast_user_availability(&head, connected_user->username, "ONLINE");
        memset(&output[0], 0, sizeof(output));
        memset(&user_and_session[0], 0, sizeof(user_and_session));
    }
    else
    {
        format_message(output, "LOGIN", "LOGIN_FAILED", "0", "0", "NULL", "NULL");
        send_data(connected_user->socket, output);
        
        memset(&output[0], 0, sizeof(output));
    }
}

//fungsi list_user
void list_user(client_data *connected_user, char client_ip[MAX_IP], char username[MAX_USERNAME])
{
    char buffer_protocol[6][MAX_STRING];
    int not_valid = 1; //variable cek autentifikasi
    
    //Menerima pesan dari client
    send_data_online_users(&head, connected_user->socket, username);
}

//fungsi inchat
void inchat(client_data *connected_user, char client_ip[MAX_IP], char SIGNAL[MAX_USERNAME], char receiver[MAX_USERNAME], char sender[MAX_USERNAME], char content_type[MAX_USERNAME], char content[MAX_USERNAME])
{
    char client_message[MAX_STRING] = "",
         output[MAX_STRING] = "";
    
    int read_size;
    int not_valid = 1; //variable cek autentifikasi
    
    //Mengirim pesan kembali ke client
    int receiver_socket = get_receiver_socket(&head, receiver);
    
    format_message(output, "INCHAT", "SEND_RECEIVE", receiver, sender, "MESSAGE", content);
    printf("content : %s\n", content);
    send_data(receiver_socket, output);
    puts(client_message);
    memset(&client_message[0], 0, sizeof(client_message));
    memset(&output[0], 0, sizeof(output));
    
    format_message(output, "INCHAT", "SEND_MESSAGE_OK", "0", sender, "NULL", "NULL");
    send_data(connected_user->socket , output);
    
    memset(&output[0], 0, sizeof(output));
}

//fungsi logout
void logout(client_data *connected_user)
{
    char output[MAX_STRING] = "";
    set_user_offline(&head, *connected_user);
    format_message(output, "LOGOUT", "LOGOUT_SUCCESS", "0", connected_user->username, "NULL", "NULL");
    send_data(connected_user->socket , output);
}

//fungsi handler menggunakan thread
void *user_handler(void *arguments)
{
    //Autentikasi user
    thread_arguments *user = arguments;
    char mode[MAX_STRING] = "",
    input[MAX_STRING] = "",
    username[MAX_STRING] = "",
    password[MAX_STRING] = "",
    username_in_session[MAX_STRING] = "",
    session_key_temp[MAX_STRING] = "",
    buffer_protocol[6][MAX_STRING];
    int read_size;
    int error = 0;
    client_data connected_user;
    connected_user.socket = user->client_socket;
    while( (read_size = read_data(connected_user.socket , input)) > 0)
    {
        strip_message(buffer_protocol,input);
        printf("%s\n", buffer_protocol[0]);
        printf("%s\n", buffer_protocol[1]);
        printf("%s\n", buffer_protocol[2]);
        printf("%s\n", buffer_protocol[3]);
        printf("%s\n", buffer_protocol[4]);
        printf("%s\n", buffer_protocol[5]);
        if(strcmp(buffer_protocol[4], "AUTH") == 0)
        {
            char *temp;
            temp = strtok (buffer_protocol[5], ":");
            strcpy(username, temp);
            while (temp != NULL)
            {
                temp = strtok (NULL, ":");
                strcpy(password, temp);
                break;
            }
        }
        if(strcmp(buffer_protocol[0], "SIGNUP") == 0)
        {
            //printf("signup\n");
            signup(&connected_user, user->client_ip, username, password);
        }
        else
            if(strcmp(buffer_protocol[0], "LOGIN") == 0)
            {
                login(&connected_user, user->client_ip, username, password);
            }
            else
                if(strcmp(buffer_protocol[0], "LIST_USER") == 0)
                {
                    char *temp_sender;
                    temp_sender = strtok (buffer_protocol[3], ":");
                    strcpy(username_in_session, temp_sender);
                    while (temp_sender != NULL)
                    {
                        temp_sender = strtok (NULL, ":");
                        strcpy(session_key_temp, temp_sender);
                        break;
                    }
                    
                    if(check_session(&head, &connected_user, atoi(session_key_temp)))
                    {
                        list_user(&connected_user, user->client_ip, username_in_session);
                    }
                    else
                    {
                        printf("Intruder Detected!!!");
                        char error_message[MAX_STRING] = "";
                        format_message(error_message, "HOME", "ERROR", "0", "0", "NULL", "NULL");
                        send_data(connected_user.socket,error_message);
                    }
                }
                else
                    if(strcmp(buffer_protocol[0], "INCHAT") == 0)
                    {
                        char *temp_sender;
                        temp_sender = strtok (buffer_protocol[3], ":");
                        strcpy(username_in_session, temp_sender);
                        while (temp_sender != NULL)
                        {
                            temp_sender = strtok (NULL, ":");
                            strcpy(session_key_temp, temp_sender);
                            break;
                        }
                        
                        if(check_session(&head, &connected_user, atoi(session_key_temp)))
                        {
                            inchat(&connected_user, user->client_ip, buffer_protocol[1], buffer_protocol[2], username_in_session, buffer_protocol[4], buffer_protocol[5] );
                        }
                        else
                        {
                            printf("Intruder Detected!!!");
                            char error_message[MAX_STRING] = "";
                            format_message(error_message, "HOME", "ERROR", "0", "0", "NULL", "NULL");
                            send_data(connected_user.socket,error_message);
                        }
                    }
                    else
                        if(strcmp(buffer_protocol[0], "LOGOUT") == 0)
                        {
                            char *temp_sender;
                            temp_sender = strtok (buffer_protocol[3], ":");
                            strcpy(username_in_session, temp_sender);
                            while (temp_sender != NULL)
                            {
                                temp_sender = strtok (NULL, ":");
                                strcpy(session_key_temp, temp_sender);
                                break;
                            }
                            
                            if(check_session(&head, &connected_user, atoi(session_key_temp)))
                            {
                                logout(&connected_user);
                                break;
                            }
                            else
                            {
                                printf("Intruder Detected!!!");
                                char error_message[MAX_STRING] = "";
                                format_message(error_message, "HOME", "ERROR", "0", "0", "NULL", "NULL");
                                send_data(connected_user.socket,error_message);
                            }
                        }
                        else
                        {
                            char error_message[MAX_STRING] = "";
                            format_message(error_message, "HOME", "ERROR", "0", "0", "NULL", "NULL");
                            send_data(connected_user.socket,error_message);
                            //error = 1;
                        }
        show_online_users(&head);
        clear_buffer_protocol(buffer_protocol);
        memset(&input[0], 0, sizeof(input));
    }
    
    if(read_size == 0)
    {
        puts("Client disconnected");
        //printf("%s\n", connected_user.username);
        if(strlen(connected_user.username) > 0)
        {
            set_user_offline(&head, connected_user);
            broadcast_user_availability(&head, connected_user.username, "OFFLINE");
        }
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
         password[MAX_PASSWORD] = "";
    
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
    strcpy(user2.password,"feeels");
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
        if(pthread_create(&tid, NULL, &user_handler, (void *)&arguments) < 0)
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

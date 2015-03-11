package javaclient;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Fathur
 */
public class javaClient {

    private int port;
    private String username;
    private String password;
    private InetAddress servAddr;
    private String receiver;
    private JavaClientUI2 clientUI;

    private Socket socket;
    //  private ObjectInputStream input = null;
    //  private ObjectOutputStream output = null;
    private PrintWriter sOut = null;
    private BufferedReader sIn = null;
    private BufferedReader stdIn = null;

    private String message;
    private ArrayList<String> listUser;

    String STATE;
    String FLAG;
    String TUJUAN;
    String PENGIRIM;
    String CONTENT;
    String TYPE;

    boolean cek = false, cek2 = false;
    String temp;
    int ctr;

    //constructor ketika sign in
    javaClient(String username, String password, int port, InetAddress ipAddr) {
        this.username = username;
        this.password = password;
        this.port = port;
        this.servAddr = ipAddr;
    }

    //costructor ketika login
    javaClient(JavaClientUI2 gUI, String nama, String password, int port, InetAddress ipAddr) {
        this.clientUI = gUI;
        this.username = nama;
        this.password = password;
        this.port = port;
        this.servAddr = ipAddr;
        // this.listUser = new ArrayList<String>();
    }

    public boolean start() {
        try {
            socket = new Socket(this.servAddr, this.port);
        } catch (Exception ex) {
            System.out.println("you got error sir, can't create socket : " + ex);
            return false;
        }

        String msg = "Connection accepted " + socket.getInetAddress() + ":" + socket.getPort();
        System.out.println(msg);
        // display(msg);

        try {
            sOut = new PrintWriter(socket.getOutputStream(), true);
            sIn = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            stdIn = new BufferedReader(new InputStreamReader(System.in));
            
            System.out.println("user :" + this.username + "has connected");
        } catch (Exception ex) {
            String msg2 = "you got error creating streams dude : " + ex;
            System.out.println(msg2);
            // display(msg2);
            return false;
        }
        
        //minta respond success login atau ga
        this.STATE = "LogIn";
        this.FLAG = "0";
        this.TUJUAN = "0";
        this.PENGIRIM = "0";
        this.CONTENT = this.username + ";" + this.password;
        this.TYPE = "Sign In";
        try {
            sOut.write(STATE + "/r/n" + FLAG + "/r/n" + TUJUAN + "/r/n" + PENGIRIM + "/r/n" + TYPE + "/r/n" + CONTENT);
            temp = "";
            cek2 = false;
            while ((temp = sIn.readLine()) != null) {
                if (temp.equals("SUCCESS")) {
                    cek2 = true;
                    break;
                } else {
                    cek2 = false;
                }
            }

        } catch (Exception e) {
        }
        temp = "";
        ctr = 0;
        try {
            //MINTAlist user
            this.STATE = "LogIn";
            this.FLAG = "0";
            this.TUJUAN = "0";
            this.PENGIRIM = "0";
            this.CONTENT = 
            this.TYPE = "SendArray";
            
            while ((temp = sIn.readLine()) != null) {
                if (ctr % 6 == 0 && ctr > 0 && !temp.equals("0")) {
                    listUser.add(temp); 
                }
            }
        } catch (IOException ex) {
            Logger.getLogger(javaClient.class.getName()).log(Level.SEVERE, null, ex);
        }
        return true;
    }

    public boolean startCreate() {
        try {
            socket = new Socket(this.servAddr, this.port);
        } catch (Exception ex) {
            System.out.println("you got error sir, can't create socket : " + ex);
            return false;
        }
        String msg = "Connection signIn accepted " + socket.getInetAddress() + ":" + socket.getPort();
        System.out.println(msg);

        try {
            sOut = new PrintWriter(socket.getOutputStream(), true);
            sIn = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            stdIn = new BufferedReader(new InputStreamReader(System.in));
            System.out.println("user :" + this.username + "has created account");
        } catch (Exception ex) {
            String msg2 = "you got error creating streams dude : " + ex;
            System.out.println(msg2);
            return false;
        }
        this.STATE = "SIGNUP";
        this.FLAG = "SIGNUP_REQ";
        this.TUJUAN = "0";
        this.PENGIRIM = "0";
        this.CONTENT = this.username + ";" + this.password;
        this.TYPE = "Sign Up";
        try {
            sOut.write(STATE + "/r/n" + FLAG + "/r/n" + TUJUAN + "/r/n" + PENGIRIM + "/r/n" + TYPE + "/r/n" + CONTENT);
            //cek ok apa ga? klo OK, tutup socket
            temp = "";
            cek = false;
            while ((temp = sIn.readLine()) != null) {
                if (temp.equals("SUCCESS")) {
                    cek = true;
                    break;
                } else {
                    cek = false;
                }
            }

        } catch (Exception e) {
        }
        return true;
    }

   // private void display(String s) {
    //    clientUI.append(s + "\n");
    // }

    /*void sendMessage(chatHandler msg) {
     try {
     output.writeObject(msg);
     } catch (IOException e) {
     //display("Exception write ke server: " + e);
     }
     }*/
    //nanti ada sendPM
    void sendMessage(String msg) { //sendMessage = broadcast
        try {
            this.STATE = "SendMsg";
            this.FLAG = "0";
            this.TUJUAN = "0";
            this.PENGIRIM = "0";
            this.CONTENT = msg;
            sOut.write(msg);
        } catch (Exception e) {

        }
    }

    void disconnect() {
        try {
            if (sIn != null) {
                sIn.close();
            }
        } catch (Exception e) {
        }

        try {
            if (sOut != null) {
                sOut.close();
            }
        } catch (Exception e) {
        }

        try {
            if (socket != null) {
                socket.close();
            }
        } catch (Exception e) {
        }
    }

    ArrayList getUser() {
        return this.listUser;
    }

    class ListenFromServer extends Thread {

        public void run() {
            while (true) {
                try {
                    String msg = (String) sIn.readLine();
                    clientUI.append(msg);
                } catch (IOException e) {
                    System.out.println("Server has close the connection: " + e);
                    break;
                }
            }
        }
    }
}

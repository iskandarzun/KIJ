package javaclient;

import java.net.InetAddress;
import java.io.*;
import java.net.Socket;

/**
 *
 * @author Fathur
 */
public class javaClient {

    private int port;
    private String username;
    private InetAddress servAddr;
    private String receiver;
    private JavaClientUI2 clientUI;

    private Socket socket;
    private ObjectInputStream input = null;
    private ObjectOutputStream output = null;

    private String message;

    javaClient(JavaClientUI2 gUI, String nama, int port, InetAddress ipAddr) {
        this.clientUI = gUI;
        this.username = nama;
        this.port = port;
        this.servAddr = ipAddr;
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
        display(msg);

        try {
            input = new ObjectInputStream(socket.getInputStream());
            output = new ObjectOutputStream(socket.getOutputStream());
            System.out.println("user :" + this.username + "has connected");
        } catch (Exception ex) {
            String msg2 = "you got error creating streams dude : " + ex;
            System.out.println(msg2);
            display(msg2);
            return false;
        }

        new ListenFromServer().start();

        try {
            output.writeObject(username);
        } catch (IOException eIO) {
            display("Exception login : " + eIO);
            disconnect();
            return false;
        }
        return true;
    }

    private void display(String s) {
        clientUI.append(s + "\n");
    }

    void sendMessage(chatHandler msg) {
        try {
            output.writeObject(msg);
        } catch (IOException e) {
            display("Exception write ke server: " + e);
        }
    }

    private void disconnect() {
        try {
            if (input != null) {
                input.close();
            }
        } catch (Exception e) {
        }

        try {
            if (output != null) {
                output.close();
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

    class ListenFromServer extends Thread {

        public void run() {
            while (true) {
                try {
                    String msg = (String) input.readObject();
                    if (clientUI == null) {
                        System.out.println(msg);
                        System.out.print("> ");
                    } else {
                        clientUI.append(msg);
                    }
                } catch (IOException e) {
                    System.out.println("Server has close the connection: " + e);
                    break;
                } catch (ClassNotFoundException e2) {
                }
            }
        }
    }
}

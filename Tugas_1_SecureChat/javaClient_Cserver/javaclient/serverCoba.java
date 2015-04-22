package javaclient;

import java.io.*;
import java.net.*;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;
import java.util.ArrayList;

/**
 *
 * @author Fathur
 */
public class serverCoba {

    private static int clientId;
    private serverCobaUI sGui;
    private int PORT;
    private boolean keepgoing;
    private ArrayList<ClientHandler> al;
    private ArrayList<String> DAFTAR_USER;
    private SimpleDateFormat sdf;

    public serverCoba(int port, serverCobaUI sf) {
        this.sGui = sf;
        this.PORT = port;
        sdf = new SimpleDateFormat("HH:mm:ss");
        al = new ArrayList<ClientHandler>();
        DAFTAR_USER = new ArrayList<String>();
    }

    public void start() {
        keepgoing = true;
        try {
            ServerSocket serverSocket = new ServerSocket(PORT);
            while (keepgoing) {
                display("Server membuka koneksi Clients pada port " + PORT + ".");
                Socket socket = serverSocket.accept();
                if (!keepgoing) {
                    break;
                }
                ClientHandler clthread = new ClientHandler(socket);
                al.add(clthread);
                DAFTAR_USER.add(clthread.getUsername());
                clthread.start();
            }
            try {
                serverSocket.close();
                for (int i = 0; i < al.size(); ++i) {
                    ClientHandler ch = al.get(i);
                    try {
                        ch.sInput.close();
                        ch.sOutput.close();
                        ch.socket.close();
                    } catch (IOException ioE) {
                        System.out.println("\nError ClientHandler! Problem pada ArrayList!" + ioE);
                    }
                }
            } catch (Exception e) {
                display("gak bisa close: " + e);
            }
        } catch (IOException e) {
            String msg = sdf.format(new Date()) + " Error server socket: " + e + "\n";
            display(msg);
        }
    }

    protected void stop() {
        keepgoing = false;
        try {
            new Socket("localhost", PORT);
        } catch (Exception e) {
           System.out.println("error sir : " + e);
        }
    }

    private void display(String msg) {
        String time = sdf.format(new Date()) + " " + msg;
            sGui.appendEvent(time + "\n");
    }

    private void broadcast(String message) {
        String time = sdf.format(new Date());
        String msgtime = time + " " + message + "\n";
        sGui.appendRoom(msgtime);
        for (int i = al.size(); --i >= 0;) {
            ClientHandler ch = al.get(i);
            if (!ch.writeMsg(msgtime)) {
                al.remove(i);
                display("Disconnected Client " + ch.username + " removed from list.");
            }
        }
    }

    private void PM(String msg, String userPM) {
        String time = sdf.format(new Date());
        String msgtime = time + " " + msg + "\n";
        System.out.println("ini msgtime" + msgtime);
        for (int i = DAFTAR_USER.size(); i-- >= 0;) {
            if (userPM.equals(DAFTAR_USER.get(i))) {
                ClientHandler ch = al.get(i);
                ch.writeMsg(msgtime);
                System.out.println("ini userPM " + userPM + " ini user_ke_" + i + DAFTAR_USER.get(i));

            } else {
            }
        }
    }

    private void remove(int id) {
        for (int i = 0; i < al.size(); ++i) {
            ClientHandler ct = al.get(i);
            if (ct.id == id) {
                al.remove(i);
                return;
            }
        }
    }

    class ClientHandler extends Thread {
        Socket socket;
        ObjectInputStream sInput;
        ObjectOutputStream sOutput;
        int id;
        String username;
        chatHandler ch;
        String date;

        ClientHandler(Socket socket) {
            id = ++clientId;
            this.socket = socket;
            try {
                sOutput = new ObjectOutputStream(socket.getOutputStream());
                sInput = new ObjectInputStream(socket.getInputStream());
                username = (String) sInput.readObject();
                display(username + " just connected.");
            } catch (IOException e) {
                display("Exception creating new Input/output Streams: " + e);
                return;
            } 
            catch (ClassNotFoundException e) {
            }
            date = new Date().toString() + "\n";
        }

        public void run() {
            boolean keepGoing = true;
            while (keepGoing) {
                try {
                    ch = (chatHandler) sInput.readObject();
                } catch (IOException e) {
                    display(username + " Exception reading Streams: " + e);
                    break;
                } catch (ClassNotFoundException e2) {
                    break;
                }
                String message = ch.getMessage();
                String userPM = ch.getUserPM();
                System.out.println("ini user :" + username);
                int tipe = ch.getType();
                System.out.println("ini messagenya :" + message);
                System.out.println("ini tipenya :" + tipe);
                if (tipe == 1) {
                    broadcast(username + ": " + message);
                } else if (tipe == 0) {
                    display(username + " disconnected with a LOGOUT message.");
                    keepGoing = false;
                } else {
                    PM(username + ": " + message, userPM);
                    for (int i = 0; i < DAFTAR_USER.size(); i++) {
                        System.out.println(DAFTAR_USER.get(i));
                    }
                }
            }
            remove(id);
            close();
        }

        private String getUsername() {
            return this.username;
        }

        private void close() {
            try {
                if (sOutput != null) {
                    sOutput.close();
                }
            } catch (Exception e) {
            }
            try {
                if (sInput != null) {
                    sInput.close();
                }
            } catch (Exception e) {
            };
            try {
                if (socket != null) {
                    socket.close();
                }
            } catch (Exception e) {
            }
        }

        private boolean writeMsg(String msg) {
            if (!socket.isConnected()) {
                close();
                return false;
            }
            try {
                sOutput.writeObject(msg);
            }
            catch (IOException e) {
                display("Error sending message to " + username);
                display(e.toString());
            }
            return true;
        }
    }
}

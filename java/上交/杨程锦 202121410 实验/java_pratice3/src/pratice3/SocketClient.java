package pratice3;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

class myClientFrame extends Frame{
    Socket client = null;
    TextField port = new TextField("8888");
    TextField ip = new TextField("127.0.0.1");
    Button connect = new Button("Connect");
    TextArea TA = new TextArea(25, 60);
    TextField TF = new TextField(40);
    Button send = new Button("Send");

    myClientFrame(String title){
        super(title);
        init();

        connect.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    connect.setEnabled(false);
                    int i = Integer.parseInt(port.getText());
                    TA.append("Socket Connect IP:" + ip.getText() + "\nConnect Port:" + port.getText() + "\n");
                    client = new Socket(ip.getText(), i);
                    TA.append("Connect...\n");

                    ClientThread CT = new ClientThread();
                    CT.start();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        });

        send.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    String ss = TF.getText();
                    PrintWriter aa = new PrintWriter(client.getOutputStream());
                    if (ss != ""){
                        aa.write("Client send:" + ss + "\n");
                        TA.append("Client send:" + ss + "\n");
                        aa.flush();;

                    }
                    TF.setText("");
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        });

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                try {
                    client.close();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
                System.exit(0);
            }
        });

        setVisible(true);
    }

    void init() {
        setLocation(500,10);
        setSize(400,400);
        setResizable(false);
        setBackground(Color.MAGENTA);
        TA.setBackground(Color.white);

        Panel Up = new Panel();
        Up.add(new Label("IP"));
        Up.add(this.ip);
        Up.add(new Label("Port"));
        Up.add(this.port);
        Up.add(this.connect);
        this.add(Up, BorderLayout.NORTH);

        Panel Mid = new Panel();
        Mid.add(this.TA);
        this.add(Mid, BorderLayout.CENTER);

        Panel Down = new Panel();
        Down.add(new Label("Send"));
        Down.add(this.TF);
        Down.add(this.send);
        this.add(Down, BorderLayout.SOUTH);

        pack();
    }

    class ClientThread extends Thread{
        @Override
        public void run() {
            try {
                BufferedReader br = new BufferedReader(new InputStreamReader(client.getInputStream()));
                String s = br.readLine();
                if (s == "Server send:bye"){
                    client.close();
                }
                while (!"Server send:bye".equals(s) && s != null){
                    TA.append(s + "\n");
                    s = br.readLine();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }

        }
    }
}

public class SocketClient {
    public static void main(String[] args) {
        myClientFrame cf = new myClientFrame("客户端");
    }
}

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
import java.net.ServerSocket;
import java.net.Socket;

//窗体
class myServerFrame extends Frame{
    ServerSocket server = null;
    Socket client = null;
    TextField port = new TextField("8888");
    Button start = new Button("Start");
    TextArea TA = new TextArea(25, 60);
    TextField TF = new TextField(40);
    Button send = new Button("Send");

    myServerFrame(String title) {
        super(title);
        init();  //初始化窗口

        start.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    start.setEnabled(false);
                    int i = Integer.parseInt(port.getText());
                    TA.append("Server Port:" + port.getText() + "\n");
                    server = new ServerSocket(i);
                    client  = server.accept();
                    TA.append("A client connect...\n");

                    ServerThread ST = new ServerThread();
                    ST.start();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }

            }
        });

        send.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    PrintWriter s = new PrintWriter(client.getOutputStream());
                    String ss = TF.getText();
                    if (ss != ""){
                        s.write("Server send:" + ss + "\n");
                        TA.append("Server send:" + ss + "\n");
                        s.flush();
                    }
                    TF.setText("");
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        });

        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                try {
                    server.close();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
                System.exit(0);
            }
        });

        this.setVisible(true);
    }

    void init() {
        setLocation(10,10);
        setSize(400,400);
        setResizable(false);
        setBackground(Color.MAGENTA);
        TA.setBackground(Color.white);

        Panel Up = new Panel();
        Up.add(new Label("Port"));
        Up.add(this.port);
        Up.add(this.start);
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

    class  ServerThread extends Thread{
        @Override
        public void run() {
            try {
                BufferedReader br = new BufferedReader(new InputStreamReader(client.getInputStream()));
                String s = br.readLine();
                if (s == "Client send:bye"){
                    client.close();
                }
                while (!"Client send:bye".equals(s) && s != null){
                    TA.append(s + "\n");
                    s = br.readLine();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

}

public class SocketServer {
    public static void main(String[] args) {
        myServerFrame frame = new myServerFrame("服务端");
    }
}

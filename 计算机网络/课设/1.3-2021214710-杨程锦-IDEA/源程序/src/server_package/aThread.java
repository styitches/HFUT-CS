package server_package;
import java.net.*;
import java.io.*;
import java.io.InputStreamReader;
import javax.swing.*;

import java.awt.event.*;

public class aThread extends Thread implements ActionListener{
    private Socket clientLinking;
    private ServerSocket serverInter;
    private OutputStream outStream;
    private JTextArea in;
    private JTextArea out;
    private JButton send_button;
    private String message_out;

    public aThread(ServerSocket serverInter,JTextArea in,JTextArea out,JButton send_button){
        this.serverInter=serverInter;
        this.in=in;
        this.out=out;
        this.send_button=send_button;
    }

    @Override
    public void actionPerformed(ActionEvent e) {        //输出公告
        
        try{
            this.message_out=this.out.getText();
            this.outStream.write(("Server："+this.message_out+"\n").getBytes());
            this.outStream.flush();
        }catch(IOException f){
            System.out.println("Error"+f);
        }
        // out.setText("");
    }

    @Override
    public void run() {
        System.out.println("now "+Thread.currentThread().getName()+" is running...");
        try{
            this.clientLinking = this.serverInter.accept();
            this.in.append("LINKING SUCCESS\n");
            this.in.append("IP:"+this.clientLinking.getInetAddress()+"\n");
            this.in.append("Port:"+this.clientLinking.getPort()+"\n");

            

            this.send_button.addActionListener(this);     //点击后链接actionPerformed

            InputStream inStream = this.clientLinking.getInputStream();
            this.outStream=this.clientLinking.getOutputStream();

            new sockets(this.outStream,Thread.currentThread().getName());
            

            BufferedReader clientin=new BufferedReader(new InputStreamReader(inStream));
            String message_in=clientin.readLine();
        
            while(!message_in.equals("disconnect")){
                this.in.append(message_in+"\n");
                char flag=message_in.charAt(0);
                if(flag!='f'){
                    sockets.outStreams[flag-'0'].write(("（私聊）"+message_in.substring(1)+"\n").getBytes());
                    this.outStream.write(("（私聊）"+message_in.substring(1)+"\n").getBytes());
                }
                else{
                    for(int i=0;i<sockets.index_serverOut;i++){
                        sockets.outStreams[i].write((message_in.substring(1)+"\n").getBytes());
                        sockets.outStreams[i].flush();
                        
                    }
                }
                
                message_in=clientin.readLine();
            }

            this.in.append(Thread.currentThread().getName()+" linking disconnected!\n");
            this.outStream.write("disconnect\n".getBytes());
            clientLinking.close();
            for(int i=0;i<sockets.index_serverOut;i++){
                if(sockets.names[i].equals(Thread.currentThread().getName())){
                    sockets.names[i]+="（离线）";
                    break;
                }
            }
            
        }catch(IOException e){
            System.out.println("Error:"+e);
        }
    }
}


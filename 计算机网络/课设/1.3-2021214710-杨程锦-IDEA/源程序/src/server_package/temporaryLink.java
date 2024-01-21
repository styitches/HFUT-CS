package server_package;
import java.net.*;
import java.io.*;


public class temporaryLink extends Thread {
    ServerSocket tempInter;
    Socket tempLinking;
    OutputStream outStream;
    public temporaryLink(){
        System.out.println("now v0 is running...");
        while(true){          //持续接受请求
            System.out.println("now restart templinking...");
            try{
                tempInter = new ServerSocket(7000);
                tempLinking = tempInter.accept();
                System.out.println("templink SUCC!");
                outStream = tempLinking.getOutputStream();

                outStream.write(String.format("%d\n",sockets.index_serverOut).getBytes());
                System.out.println(sockets.index_serverOut);
                for(int i=0;i<sockets.index_serverOut;i++){
                        outStream.write(String.format("%d：%s\n",i+1,sockets.names[i]).getBytes());
                        System.out.println(String.format("%d：%s\n",i+1,sockets.names[i]));
                }
                outStream.flush();
                tempInter.close();
            }catch(IOException e){
                System.out.println("Error:"+e);
                break;
            }
        }
    }
    
    
    
}

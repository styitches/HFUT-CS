package server_package;
import java.net.*;
import java.awt.*;
import java.io.*;

import javax.swing.*;
import javax.swing.border.Border;

public class serverDemo extends JFrame{
	JButton send_botton;
	JTextArea out = new JTextArea(1, 30);   //send box
	JTextArea in = new JTextArea(15, 30);   //receive box
	JPanel pan = new JPanel();


    public serverDemo(){      //create UI
        super("Server");
		Border border = BorderFactory.createLineBorder(Color.magenta, 1);
	    in.setBorder(border);
	    out.setBorder(border);
		send_botton = new JButton("公告");
		// send_botton.addActionListener(this);3

		pan.setLayout(new FlowLayout());
		pan.add(in);
	    pan.add(out);
		pan.add(send_botton);

		add(pan);
		setSize(350,370);
		setVisible(true);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        

        try{                    //try linking and get stream
            ServerSocket serverInter1 = new ServerSocket(6666);
            ServerSocket serverInter2 = new ServerSocket(6667);
            ServerSocket serverInter3 = new ServerSocket(6668);
            
            aThread v1 = new aThread(serverInter1,in,out,send_botton);
            v1.setName("user1");
            v1.start();
            aThread v2 = new aThread(serverInter2,in,out,send_botton);
            v2.setName("user2");
            v2.start();
            aThread v3 = new aThread(serverInter3,in,out,send_botton);
            v3.setName("user3");
            v3.start();
            temporaryLink v0 = new temporaryLink();
            v0.start();

            
        }catch(IOException e){
            System.out.println("Error:"+e);
        }
        

    }



    public static void main(String[] args) {
        new serverDemo();
    }

}

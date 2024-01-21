package client_package;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.*;
import java.io.*;

public class selectUser extends JFrame{
    JTextArea user;
    static String temp="f";
    public selectUser(String name){
        super(name);
        JLabel text = new JLabel("输入要私聊者序号：");
        text.setBounds(30,180,120,20);

        user = new JTextArea();
        this.user.setBounds(150,180,100,20);

        JTextArea lists = new JTextArea();
        lists.setBounds(20,20,260,150);

        JButton yesButton = new JButton("确定");
        yesButton.setBounds(30, 220, 100, 20);
        yes yes_do = new yes(this);
        yesButton.addActionListener(yes_do);

        JButton noButton = new JButton("取消");
        noButton.setBounds(150,220,100,20);
        no no_do = new no();
        noButton.addActionListener(no_do);

        JPanel pan = new JPanel();
        pan.setLayout(null);
        pan.add(yesButton);
        pan.add(noButton);
        pan.add(text);
        pan.add(user);
        pan.add(lists);

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setSize(300,320);
        setVisible(true);
        add(pan);

        try{
            Socket a=new Socket("127.0.0.1",7000);
            InputStream inStream = a.getInputStream();
            BufferedReader clientin=new BufferedReader(new InputStreamReader(inStream));
            int rows = clientin.readLine().charAt(0)-'0';  //计算输入行数
            String one_row;
            for(int i=0;i<rows;i++){
                one_row=clientin.readLine();
                lists.append(one_row+"\n");
            }
            a.close();
            
        }catch(IOException e){
            System.out.println("Error"+e);
        }
    }


    class no implements ActionListener{
        @Override
        public void actionPerformed(ActionEvent e) {
            dispose();
        }
    }
 

    
}


class yes implements ActionListener {
    selectUser a;
    public yes(selectUser a){
        this.a = a;
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        try{
            String select_string=a.user.getText();
            int select = Integer.parseInt(select_string);
            selectUser.temp=String.format("%d",select-1);
            
            
        }catch(NumberFormatException n){
            System.out.println("group mod");
            selectUser.temp="f";
        }
    }
}

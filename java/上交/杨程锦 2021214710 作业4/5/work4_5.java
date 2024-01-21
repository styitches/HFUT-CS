import javax.xml.soap.Text;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.*;
import java.util.Collections;
import java.util.Vector;


class fileControl extends Frame{
    fileControl(String s) throws FileNotFoundException {
        super(s);
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
        setBounds(400,200,500,200);
        setinit();
        setResizable(false);
        setVisible(true);
    }

    public void setinit() throws FileNotFoundException {
        Panel panel1 = new Panel();
        Label labelName = new Label("姓名：");
        Label labelGrades = new Label("成绩：");
        Label labelId = new Label("学号：");
        TextField fieldName = new TextField(10);
        TextField fieldGrades = new TextField(10);
        TextField fieldId = new TextField(10);
        panel1.add(labelName);
        panel1.add(fieldName);
        panel1.add(labelGrades);
        panel1.add(fieldGrades);
        panel1.add(labelId);
        panel1.add(fieldId);
        panel1.setLayout(new FlowLayout());
        add(panel1);

        Panel panel3 = new Panel();
        Label maxLabel = new Label("Max:");
        TextField maxText = new TextField(5);
        Label averageLabel = new Label("Average:");
        TextField averageText = new TextField(5);
        Label minLabel = new Label("Min:");
        TextField minText = new TextField(5);
        panel3.add(maxLabel);
        panel3.add(maxText);
        panel3.add(minLabel);
        panel3.add(minText);
        panel3.add(averageLabel);
        panel3.add(averageText);
        panel3.setLayout(new FlowLayout());
        add(panel3);

        Panel panel2 = new Panel();
        Button addBtn = new Button("   Add   ");
        Button conBtn = new Button("Continue");
        Button couBtn = new Button("Counter");
        panel2.add(addBtn);
        panel2.add(conBtn);
        panel2.add(couBtn);
        panel2.setLayout(new FlowLayout());
        add(panel2);

        this.setLayout(new FlowLayout());


        File StudentFile = new File("D:\\Student.txt");
        File StudentMark = new File("D:\\StudentMark.txt");
        FileOutputStream fosFile = new FileOutputStream(StudentFile);
        FileOutputStream fosMark = new FileOutputStream(StudentMark);
        FileInputStream fis = new FileInputStream(StudentFile);

        addBtn.addActionListener(new ActionListener() {    //把文本框中内容读入byte数组中再写入fos流中
            @Override
            public void actionPerformed(ActionEvent e) {
                try{
                    String i = fieldName.getText() + " " + fieldId.getText() + "#" + fieldGrades.getText() + "\n";
                    byte[] bytes = new byte[1024];
                    bytes = i.getBytes();
                    fosFile.write(bytes,0,bytes.length);  //将bytes.length字节从位于偏移量 off的指定字节数组写入此文件输出流。
                    System.out.println("信息录入成功");
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        });

        conBtn.addActionListener(new ActionListener() {  //置空三个文本框
            @Override
            public void actionPerformed(ActionEvent e) {
                fieldName.setText("");
                fieldId.setText("");
                fieldGrades.setText("");
            }
        });

        couBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                BufferedReader bf = new BufferedReader(new InputStreamReader(fis));
                String s;
                Vector<Double> markArray = new Vector<>(0);
                Double sum = 0.0;
                try{
                    while ((s = bf.readLine()) != null){         //用于读取流中的一行字符
                        String temp = s.substring(s.indexOf('#') + 1);  //用于返回#后面的代表成绩的字符串
                        markArray.add(Double.parseDouble(temp));  //强转为double之后写入容器
                    }
                    Collections.sort(markArray);
                    for (int i = 0; i < markArray.size(); i++){
                        sum += markArray.get(i);
                    }
                    maxText.setText(String.valueOf(markArray.get(0)));
                    averageText.setText(String.valueOf(sum / markArray.size()));
                    minText.setText(String.valueOf(markArray.get((markArray.size() - 1))));
                    String i = maxText.getText() + " " + averageText.getText() + " " + minText.getText() + "\n";
                    byte[] b = new byte[1024];
                    b = i.getBytes();
                    fosFile.write(b,0,b.length);
                    System.out.println("成绩录入成功");

                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        });
    }


}


public class work4_5 {
    public static void main(String[] args) throws Exception {
        new fileControl("sss");
    }
}
import java.awt.*;


class myFrame1 extends Frame{
    myFrame1(String s) {
        super(s);
        this.setSize(600,400);
        this.setVisible(true);
        this.setResizable(true);
    }

    public void paint(Graphics g){
        g.setColor(Color.red);
        g.drawRect(90,90,130,130);
        g.fillOval(100,100,50,50);
        g.fillOval(160,100,50,50);
        g.fillOval(100,160,50,50);
        g.fillOval(160,160,50,50);
    }
}


public class work3_6 {
    public static void main(String[] args){
        myFrame1 f1 = new myFrame1("hello");
    }
}


import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;


class myFrame2 extends Frame{
    myFrame2(String s){
        super(s);
        this.setBounds(200,200,500,500);
        this.setVisible(true);
        this.addMouseListener(new MyMouseListener());
    }

    private class MyMouseListener extends MouseAdapter{
        public void mousePressed(MouseEvent e){
            if (e.getClickCount() == 1){
                if (e.getButton() == e.BUTTON1){
                    Graphics g=getGraphics();
                    g.setColor(Color.green);
                    g.fillOval(e.getX(),e.getY(),60,60);
                } else if (e.getButton() == e.BUTTON3){
                    Graphics g=getGraphics();
                    g.setColor(Color.red);
                    g.fillRect(e.getX(),e.getY(),60,60);
                }
            } else if (e.getClickCount() == 2){
                if (e.getButton() == e.BUTTON1){
                    repaint();;
                }
            }
        }
    }
}

public class work3_7 {
    public static void main(String[] args) {
        new myFrame2("sss");
    }
}

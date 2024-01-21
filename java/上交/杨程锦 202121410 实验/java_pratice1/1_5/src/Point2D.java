public class Point2D {
    int x, y;
    public Point2D(int x, int y){
        this.x = x;
        this.y = y;
    }

    public Point2D() {
    }

    public void offset(int a, int b){
        this.x = a;
        this.y = b;
    }
}

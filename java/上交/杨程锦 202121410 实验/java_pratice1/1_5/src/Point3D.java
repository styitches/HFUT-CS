import java.math.*;
public class Point3D extends Point2D {
    int z;

    public Point3D(int x, int y, int z) {
        super(x, y);
        this.z = z;
    }

    public Point3D(Point2D p, int z) {
        this.x = p.x;
        this.y = p.y;
        this.z = z;
    }

    public void offset(int a, int b, int c) {
        this.x = a;
        this.y = b;
        this.z = c;
    }

    public static void main(String[] args) {
        Point2D p2d1 = new Point2D(10, 20);
        Point2D p2d2 = new Point2D(20, 40);
        double p2distance = Math.sqrt(Math.pow((p2d1.x - p2d2.x), 2) + Math.pow((p2d1.y - p2d2.y), 2));
        System.out.printf(String.valueOf(p2distance));
        System.out.println("   ");
        Point3D p3d1 = new Point3D(p2d1, 30);
        Point3D p3d2 = new Point3D(p2d2, 40);
        double p3distace = Math.sqrt(Math.pow((p3d1.x - p3d2.x), 2) + Math.pow((p3d1.y - p3d2.y), 2) + Math.pow((p3d1.z - p3d2.z), 2));
        System.out.println(String.valueOf(p3distace));
    }
}

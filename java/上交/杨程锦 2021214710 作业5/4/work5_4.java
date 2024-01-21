import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;

public class work5_4 {
    public static void main(String[] args) throws IOException {
        URL myurl = new URL("https://mirror.tuna.tsinghua.edu.cn/github-release/FreeCAD/FreeCAD/FreeCAD%200.19.4/FreeCAD-0.19.4-WIN-x64-installer-1.exe-SHA256.txt");
        URLConnection uc = myurl.openConnection();
        InputStreamReader isr = new InputStreamReader(uc.getInputStream());
        BufferedReader in = new BufferedReader(isr);
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            System.out.println(inputLine);
        }
        in.close();
    }
}

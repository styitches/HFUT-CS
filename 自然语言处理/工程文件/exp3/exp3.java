package exp3;
import java.io.*;
import java.util.*;

public class exp3 {
    public static String segment(String str, Map<String, String> map, boolean forward) {
        str = str.replace("/r", "");
        int length = 2;
        String sub;
        String result = "";

        while (str.length() >= length) { // 添加判断字符串长度是否足够

            if (forward) {
                sub = str.substring(0, length);
            } else {
                sub = str.substring(str.length() - length);
            }

            while (!map.containsKey(sub)) {
                if (sub.length() > 1) {
                    if (forward) {
                        sub = sub.substring(1);
                    } else {
                        sub = sub.substring(0, sub.length() - 1);
                    }
                } else {
                    break;
                }
            }

            if (forward) {
                result += sub + "/";
                str = str.substring(sub.length());
            } else {
                result = sub + "/" + result;
                str = str.substring(0, str.length() - sub.length());
            }
        }
        return result;
    }
    public static void main(String args[]) {
        //定义变量
        Map<String, String> map = new HashMap<>();

        try {
            // 预读取文件
            String words;
            String first, second;

            BufferedReader doubleBufferRead = new BufferedReader(new FileReader("src/data/doubleWord_new.txt"));

            words = doubleBufferRead.readLine();
            while (words != null) {
                first = words.split(":")[0];
                second = words.split(":")[1];
                map.put(first, second);
                words = doubleBufferRead.readLine();
            }
            doubleBufferRead.close();
        } catch (Exception e) {
            System.out.println(e);
        }

        System.out.println("请输入字符串:");
        Scanner input = new Scanner(System.in);
        String words = input.nextLine();
        input.close();

        System.out.println("FMM:" + segment(words, map, true));
        System.out.println("BMM:" + segment(words, map, false));
    }
}

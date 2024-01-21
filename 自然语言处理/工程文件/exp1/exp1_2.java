package exp1;
import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class exp1_2 {

    public static void main(String args[]) {
        HashMap<String, Integer> singleWord = new HashMap<>();
        HashMap<String, Integer> doubleWord = new HashMap<>();
        Pattern pat = Pattern.compile("(([\u4E00-\u9FA5])*)");

        try (BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(new FileInputStream("src/data/new.txt"), "gb18030"));
             BufferedWriter singleWordWriter = new BufferedWriter(new FileWriter("src/data/singleWord_new.txt"));
             BufferedWriter doubleWordWriter = new BufferedWriter(new FileWriter("src/data/doubleWord_new.txt"))) {

            String text;
            String Text = "B";

            while ((text = bufferedReader.readLine()) != null) {
                Matcher mat = pat.matcher(text);
                while (mat.find()) {
                    String group = mat.group(1);
                    if (!group.isEmpty()) {
                        Text += group;
                    }
                }
            }

            for (int i = 0; i < Text.length() - 1; i++) {
                String currentChar = Text.substring(i, i + 1);
                singleWord.put(currentChar, singleWord.getOrDefault(currentChar, 0) + 1);

                if (!"B".equals(currentChar) && !"E".equals(Text.substring(i + 1, i + 2))) {
                    String doubleChars = Text.substring(i, i + 2);
                    doubleWord.put(doubleChars, doubleWord.getOrDefault(doubleChars, 0) + 1);
                }
            }

            singleWordWriter.write("单字频率:\n");
            singleWord.forEach((k, v) -> {
                try {
                    singleWordWriter.write(k + ": " + v + "\n");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });

            doubleWordWriter.write("双字频率:\n");
            doubleWord.forEach((k, v) -> {
                try {
                    doubleWordWriter.write(k + ": " + v + "\n");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });

        } catch (FileNotFoundException e) {
            System.err.println("File not found: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("IO Exception: " + e.getMessage());
        }
    }
}

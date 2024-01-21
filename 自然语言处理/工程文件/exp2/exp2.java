package exp2;

import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class exp2 {

    public static void main(String args[]) {
        Map<String, String> map = new HashMap<>();
        ArrayList<String> singleWord = new ArrayList<>();
        ArrayList<String> doubleWord = new ArrayList<>();
        Boolean exist[] = new Boolean[100];
        Arrays.fill(exist, false);

        readWords("src/data/singleWord_ci.txt", singleWord);
        readWords("src/data/doubleWord_ci.txt", doubleWord);

        readAndProcessCiFile("src/data/Ci.txt", map, singleWord, doubleWord, exist);

        generateSongCi(map, singleWord, doubleWord, exist);
    }

    private static void readWords(String filePath, ArrayList<String> wordsList) {
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(filePath))) {
            String word;
            while ((word = bufferedReader.readLine()) != null) {
                wordsList.add(word);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void readAndProcessCiFile(String filePath, Map<String, String> map,
                                             ArrayList<String> singleWord, ArrayList<String> doubleWord,
                                             Boolean[] exist) {
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(filePath));
             BufferedWriter bufferWriter = new BufferedWriter(new FileWriter("src/data/Struct.txt"))) {

            Pattern pattern = Pattern.compile("([\u4E00-\u9FA5]*)(.)");
            Matcher mat;
            String title = new String(), text, sent, struct;

            while ((text = bufferedReader.readLine()) != null) {
                if (text.length() < 2) {
                    continue;
                } else if (text.length() < 6) {
                    title = text.trim();
                } else {
                    if (map.containsKey(title)) {
                        continue;
                    } else {
                        mat = pattern.matcher(text);
                        struct = "";
                        while (mat.find()) {
                            sent = mat.group(1);
                            int len = sent.length();
                            while (len > 0) {
                                if (len > 3) {
                                    struct += 2;
                                    len -= 2;
                                } else {
                                    struct += len;
                                    len = 0;
                                }
                            }
                            struct += mat.group(2);
                        }
                        map.put(title, struct);
                        bufferWriter.write(title + ":" + struct + "\r\n");
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void generateSongCi(Map<String, String> map, ArrayList<String> singleWord,
                                       ArrayList<String> doubleWord, Boolean[] exist) {
        System.out.println("请输入你想生成的词牌名:");
        Scanner input = new Scanner(System.in);
        String userInput = input.nextLine().trim();  // Trim to remove leading and trailing whitespaces
        input.close();

        String text;
        String title = findMatchingTitle(map, userInput);

        if (title != null) {
            text = map.get(title);
            String output = title + "\n";
            Random random = new Random();
            int m, clen = 100;

            for (int i = 0; i < text.length(); i++) {
                m = rouletteWheelSelection(clen, exist, random);
                exist[m] = true;
                if (text.charAt(i) == '1') {
                    output += singleWord.get(m).split(":")[0];
                } else if (text.charAt(i) == '2') {
                    output += doubleWord.get(m).split(":")[0];
                } else if (text.charAt(i) == '3') {
                    output += singleWord.get(m).split(":")[0];
                    output += doubleWord.get(m).split(":")[0];
                } else {
                    output += (text.charAt(i) + "\n");
                }
            }
            System.out.println(output);
        } else {
            System.out.println("词牌名不存在！");
        }
    }

    private static int rouletteWheelSelection(int clen, Boolean[] exist, Random random) {
        int selected = random.nextInt(clen);
        while (exist[selected]) {
            selected = random.nextInt(clen);
        }
        return selected;
    }

    private static String findMatchingTitle(Map<String, String> map, String userInput) {
        for (String title : map.keySet()) {
            if (title.trim().equalsIgnoreCase(userInput)) {
                return title;
            }
        }
        return null;
    }
}

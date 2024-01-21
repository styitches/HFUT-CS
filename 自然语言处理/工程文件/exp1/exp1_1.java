package exp1;

import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Pattern;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class exp1_1 {
    public static void main(String[] args) {
        Map<String, Integer> singleWordMap = new HashMap<>(); // 用于存储单字的Map
        Map<String, Integer> doubleWordMap = new HashMap<>(); // 用于存储双字的Map

        try {
            File file = new File("src/data/Ci.txt");
            InputStreamReader reader = new InputStreamReader(new FileInputStream(file), "GBK");
            BufferedReader bufferedReader = new BufferedReader(reader);

            String line = bufferedReader.readLine();

            while (line != null) {
                if (line.length() > 5) {
                    processLine(line, singleWordMap, doubleWordMap);
                }

                line = bufferedReader.readLine();
            }

            bufferedReader.close();
            reader.close();

            writeToFile("src/data/singleWord_ci.txt", singleWordMap);
            writeToFile("src/data/doubleWord_ci.txt", doubleWordMap);

            System.out.println("程序运行结束，请检查文件");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void processLine(String line, Map<String, Integer> singleWordMap, Map<String, Integer> doubleWordMap) {
        int len = line.length();

        for (int i = 0; i < len; i++) {
            String currentChar = line.substring(i, i + 1);

            if (isChineseCharacter(currentChar)) {
                singleWordMap.merge(currentChar, 1, Integer::sum);
            }
        }

        for (int i = 1; i < len; i++) {
            String doubleWord = line.substring(i - 1, i + 1);

            if (isChineseCharacter(doubleWord)) {
                doubleWordMap.merge(doubleWord, 1, Integer::sum);
            }
        }
    }

    private static boolean isChineseCharacter(String str) {
        return Pattern.compile("[\u4E00-\u9FA5]*").matcher(str).matches();
    }

    private static void writeToFile(String filePath, Map<String, Integer> map) throws IOException {
        List<Map.Entry<String, Integer>> entryList = new ArrayList<>(map.entrySet());
        Collections.sort(entryList, Comparator.comparing(Map.Entry::getValue, Comparator.reverseOrder()));

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            for (Map.Entry<String, Integer> entry : entryList) {
                writer.write(entry.getKey() + ":" + entry.getValue() + "\r\n");
            }
        }
    }
}


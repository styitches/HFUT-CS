import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Inventory {
    public static void main(String[] args) throws IOException {
        new getInventory();
        System.out.println("File have finished!");
    }
}

class Goods {
    String itemNumber;
    int quantity;
    String supplier;
    String description;

    //重载构造函数使其适配两种不同输入质量的构造函数
    public Goods (String itemNumber, String quantity, String supplier, String description){
        this.description = description;
        this.itemNumber = itemNumber;
        this.supplier = supplier;
        this.quantity = Integer.parseInt(quantity);
    }

    public Goods (String itemNumber, int quantity, String supplier, String description){
        this.description = description;
        this.itemNumber = itemNumber;
        this.supplier = supplier;
        this.quantity = quantity;
    }

    //获取属性
    public String getItemNumber(){
        return itemNumber;
    }

    public int getQuantity(){
        return quantity;
    }

    public String getSupplier(){
        return supplier;
    }

    public String getDescription(){
        return description;
    }

    //修改属性
    public void setItemNumber(String itemNumber){
        this.itemNumber = itemNumber;
    }

    public  void setQuantity(int quantity){
        this.quantity = quantity;
    }

    public void setSupplier(String supplier){
        this.supplier = supplier;
    }

    public void setDescription(String description){
        this.description = description;
    }
}

class getInventory {
    ArrayList<Goods> goodsArrayList = new ArrayList<Goods>();
    BufferedWriter errorWriter = new BufferedWriter(new FileWriter("D:\\Progress\\java_pratice2\\Document\\Error.txt", true));   //使得字节写入文件末尾而非开头

    Goods good = null;

    public getInventory() throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("D:\\Progress\\java_pratice2\\Document\\Inventory.txt"));
        String line = null;

        while ((line = br.readLine()) != null) {
            String[] str = line.split("\\s+");   //正则表达式，使得不同字符直接去掉空格，安装内容存入数组
            good = new Goods(str[0], str[1], str[2], str[3]);
            goodsArrayList.add(good);
        }

        br.close();

        new getTransactions();
    }

    class getTransactions {
        ArrayList<String> transInform = new ArrayList<String>();
        ArrayList<String[]> splitedArrayList = new ArrayList<String[]>();
        ArrayList<String> shippingBuffer = new ArrayList<String>();

        String line = null;


        public getTransactions() throws IOException{
            BufferedReader readTrans = new BufferedReader(new FileReader("D:\\Progress\\java_pratice2\\Document\\Transaction.txt"));
            while ((line = readTrans.readLine()) != null){       //把文件中内容直接按行读入
                transInform.add(line);
            }

            readTrans.close();

            //比较货物操作的优先级
            // D < R < O < A
            Collections.sort(transInform, new Comparator<String>() {
                @Override
                public int compare(String o1, String o2) {
                    if (!(o1.charAt(0) == o2.charAt(0))){
                        if (o1.charAt(0) == 'O'){
                            if (o2.charAt(0) == 'A'){
                                return 1;
                            } else if (o2.charAt(0) == 'R'){
                                return -1;
                            } else if (o2.charAt(0) == 'D'){
                                return -1;
                            }
                        } else if (o1.charAt(0) == 'A'){
                            return -1;
                        } else if (o1.charAt(0) == 'D'){
                            return 2;
                        } else if (o1.charAt(0) == 'R'){
                            if (o2.charAt(0) == 'O'){
                                return 1;
                            } else if (o2.charAt(0) == 'D'){
                                return -1;
                            } else if (o2.charAt(0) == 'A'){
                                return 1;
                            }
                        }
                    } else {
                        return (o1.compareTo(o2));
                    }

                    return 0;
                }
            });

            //foreach 循环temp容纳容器内每个元素直到没有元素
            for (String temp : transInform){
                String[] revtal2 = temp.split("\\s+");
                splitedArrayList.add(revtal2);  //将按行读取的文件去除tab
            }

            errorFileInfo();

            choose();

            WriteFile();
        }

        void errorFileInfo() throws IOException{
            errorWriter.write("库存不足信息以及删除货物信息：");
            errorWriter.newLine();
            errorWriter.write("数字分别代表：客户编号、货物编号、货物数量");
            errorWriter.newLine();
        }

        void choose() throws IOException {
            for (String[] temp1 : splitedArrayList){   //遍历每一个操作
                switch (temp1[0]){
                    case "A" :
                        goodsAdd(temp1);
                        break;
                    case "O" :
                        goodsOutput(temp1);
                        checkShipping();
                        break;
                    case "R" :
                        goodsReset(temp1);
                        break;
                    case "D" :
                        goodsDelete(temp1);
                        break;

                }
            }
        }

        //发货函数
        void goodsOutput(String[] str) throws IOException {
            for (Goods good : goodsArrayList){
                if (str[1].equals(good.getItemNumber())){
                    int num = Integer.parseInt(str[2]);
                    int qual = good.getQuantity();
                    if (qual > num){
                        good.setQuantity(qual - num);
                        String line = good.getSupplier() + "\t" + good.getItemNumber() + "\t" + str[2];
                        shippingBuffer.add(line);
                    } else {
                        String newLine1 = good.getSupplier() + "\t" + good.getItemNumber() + "\t" + str[2];
                        errorWriter.write(newLine1);
                        errorWriter.flush();
                        errorWriter.newLine();
                    }
                }
            }
        }

        //添加货物函数
        void goodsAdd(String[] str){
            Goods newGood = new Goods(str[1], 0, str[2], str[3]);
            goodsArrayList.add(newGood);
        }

        //到货函数
        void goodsReset(String[] str){
            for (Goods good : goodsArrayList){
                if (str[1] == good.getItemNumber()){
                    good.setQuantity(good.getQuantity() + Integer.parseInt(str[2]));
                }
            }
        }

        //删除货物函数
        void goodsDelete(String[] str) throws IOException {
            for (Goods good : goodsArrayList){
                if (str[1] == good.getItemNumber()){
                    goodsArrayList.remove(good);
                    boolean flag = goodsArrayList.remove(good);
                    if (flag && (good.getQuantity() > 0)){
                        String line = good.getSupplier() + "\t" + good.getItemNumber() + "\t" + Integer.toString(good.getQuantity());
                        errorWriter.write(line);
                        errorWriter.flush();
                        errorWriter.newLine();
                    }
                }
            }
        }

        //写入NewInventory
        void WriteFile() throws IOException {
            BufferedWriter bw = new BufferedWriter(new FileWriter("D:\\Progress\\java_pratice2\\Document\\NewInventory.txt"));
            for (Goods newGood : goodsArrayList){
                String line = newGood.getItemNumber() + "\t" + Integer.toString(newGood.getQuantity()) + "\t" + newGood.getSupplier() + "\t" + newGood.getDescription();
                bw.write(line);
                bw.newLine();
                bw.flush();
            }
            bw.close();
        }

        void checkShipping() throws IOException {
            BufferedWriter shippingWriter = new BufferedWriter(new FileWriter("D:\\Progress\\java_pratice2\\Document\\Shipping.txt"));
            for (int i = 0; i < shippingBuffer.size() - 1; i++){
                for (int j = i + 1; j < shippingBuffer.size(); j++){

                    //判断顾客编号和货物编号相同
                    if ((shippingBuffer.get(i).toString().split("\t")[0].equals(shippingBuffer.get(j).toString().split("\t")[0])) &&
                            (shippingBuffer.get(i).toString().split("\t")[2].equals(shippingBuffer.get(j).toString().split("\t")[2]))){
                        int num1 = Integer.parseInt(shippingBuffer.get(i).toString().split("\t")[2]);
                        int num2 = Integer.parseInt(shippingBuffer.get(j).toString().split("\t")[2]);
                        int num = num1 + num2;
                        String line = shippingBuffer.get(i).toString().split("\t")[0] + "\t"
                                + shippingBuffer.get(i).toString().split("\t")[1] + "\t" + Integer.toString(num);
                        shippingBuffer.remove(i);
                        shippingBuffer.remove(j);
                        shippingBuffer.add(i, line);
                        i--;
                    }
                }
            }

            for (String ss: shippingBuffer){
                shippingWriter.write(ss);
                shippingWriter.newLine();
                shippingWriter.flush();
            }

            shippingWriter.close();
        }
    }
}

class shortageException extends Exception{
    public shortageException(){
        super("库存不足");
    }
}

class checkOutput{
    public static void checkOutput(int num) throws shortageException {
        if (num > 0){
            System.out.println("数据无误");
        } else {
            throw new shortageException();
        }
    }
}




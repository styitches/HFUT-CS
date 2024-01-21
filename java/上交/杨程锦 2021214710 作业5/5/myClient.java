import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.Socket;

public class myClient extends Socket {
    static final String IP = "127.0.0.1";
    static final int PORT = 8888;
    Socket client;
    FileInputStream fis;
    DataOutputStream dos;

    public myClient() throws Exception {
        super(IP, PORT);
        this.client = this;
        System.out.println("Cliect[port:" + client.getLocalPort() + "] 成功连接服务端");
    }

    void sendFile() throws IOException {
        try {
            File file = new File("D:\\test.txt");
            if (file.exists()){
                fis = new FileInputStream(file);
                dos = new DataOutputStream(client.getOutputStream());

                dos.writeUTF(file.getName());
                dos.flush();
                dos.writeLong(file.length());
                dos.flush();

                System.out.println("开始传输文件");
                byte[] bytes = new byte[1024];
                int length = 0;
                long progress = 0;
                while((length = fis.read(bytes, 0, bytes.length)) != -1) {
                    dos.write(bytes, 0, length);
                    dos.flush();
                    progress += length;
                    System.out.print("| " + (100*progress/file.length()) + "% |");
                }
                System.out.println();
                System.out.println("文件传输成功");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        finally {
            if (fis != null){
                fis.close();
            }
            if (dos != null){
                dos.close();
            }
            client.close();
        }
    }

    public static void main(String[] args) {
        try {
            myClient client = new myClient();
            client.sendFile();
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}

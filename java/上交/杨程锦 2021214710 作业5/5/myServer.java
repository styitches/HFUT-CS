import java.io.DataInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.math.RoundingMode;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.DecimalFormat;

public class myServer extends ServerSocket {

    static final int PORT = 8888;
    static DecimalFormat df = null;
    static {
        df = new DecimalFormat("#0.0");
        df.setRoundingMode(RoundingMode.HALF_UP);
        df.setMinimumFractionDigits(1);
        df.setMaximumFractionDigits(1);
    }
    public myServer() throws Exception {
        super(PORT);
    }
    public void load() throws Exception {
        while (true) {
            Socket socket = this.accept();
            new Thread(new Task(socket)).start();
        }
    }
    class Task implements Runnable {
        Socket socket;
        DataInputStream dis;
        FileOutputStream fos;
        Task(Socket socket) {
            this.socket = socket;
        }
        @Override
        public void run()
        {
            try {
                dis = new DataInputStream(socket.getInputStream());
                String fileName = dis.readUTF();
                long fileLength = dis.readLong();
                File directory = new File("D:\\FTCache");
                if(!directory.exists()) {
                    directory.mkdir();
                }
                File file = new File(directory.getAbsolutePath() + File.separatorChar + fileName);
                fos = new FileOutputStream(file);

                byte[] bytes = new byte[1024];
                int length = 0;
                while((length = dis.read(bytes, 0, bytes.length)) != -1) {
                    fos.write(bytes, 0, length);
                    fos.flush();
                }
                System.out.println("文件接收成功 [File Name：" + fileName + "] [Size：" + getFormatFileSize(fileLength) + "]");
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                try {
                    if(fos != null)
                        fos.close();
                    if(dis != null)
                        dis.close();
                    socket.close();
                } catch (Exception e) {}
            }
        }
    }

    private String getFormatFileSize(long length) {
        double size = ((double) length) / (1 << 30);
        if(size >= 1) {
            return df.format(size) + "GB";
        }
        size = ((double) length) / (1 << 20);
        if(size >= 1) {
            return df.format(size) + "MB";
        }
        size = ((double) length) / (1 << 10);
        if(size >= 1) {
            return df.format(size) + "KB";
        }
        return length + "B";
    }

    public static void main(String[] args) {
        try {
            myServer server = new myServer(); // 启动服务端
            server.load();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
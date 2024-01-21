package server_package;
import java.io.OutputStream;
public class sockets {
    public static OutputStream[] outStreams=new OutputStream[10];
    public static int index_serverOut;
    public static String[] names = new String[10];

    public sockets(OutputStream outStream,String name){
        names[index_serverOut]=name;
        outStreams[index_serverOut++]=outStream;
    }
}

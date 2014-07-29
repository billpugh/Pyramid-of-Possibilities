import java.io.File;
import java.io.FileReader;
import java.io.IOException;


public class ReadSerial {
    
    public static void main(String args[]) throws IOException, InterruptedException {
        File f = new File("/dev/tty.usbserial-A603IUEO");
        FileReader fr = new FileReader(f);
        while (true) {
            int a = fr.read();
            if (a == -1)
                break;
            System.out.print((char) a);
        }
        fr.close();
    }

}

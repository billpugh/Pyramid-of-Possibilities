import java.io.File;
import java.io.FileWriter;
import java.io.IOException;


public class WriteSerial {
    
    public static void main(String args[]) throws IOException, InterruptedException {
        File f = new File("/dev/tty.usbserial-A603IUEO");
        FileWriter fw = new FileWriter(f);
        for(char a = 'a'; a <= 'z'; a++) {
            fw.write(a);
            fw.flush();
            Thread.sleep(1000);
        }
        fw.close();
    }

}

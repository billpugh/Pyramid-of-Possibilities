import java.io.File;
import java.util.ArrayList;
import java.util.List;


public class DetectPort {
    
    public static String getPortName(String prefix) throws InterruptedException {
        File dev = new File("/dev");
        while (true) {
        for(String s : dev.list()) {
            if (s.startsWith(prefix)) 
                return "/dev/"+s;
        }

        Thread.sleep(500);
        System.out.println();
        }
    }
   
    
    public static List<String> getPorts(String prefix) throws InterruptedException {
        File dev = new File("/dev");
        List<String> result = new ArrayList<String>();
        while (true) {
        for(String s : dev.list()) {
            if (s.startsWith(prefix)) 
                result.add( "/dev/"+s);
        }

       return result;
        }
    }
   
    public static void main(String [] args) throws InterruptedException {
        System.out.println(getPortName("tty.usbmodem"));
        
    }


}

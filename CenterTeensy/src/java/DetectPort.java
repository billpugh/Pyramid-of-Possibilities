import java.io.File;


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
   
    public static void main(String [] args) throws InterruptedException {
        System.out.println(getPortName("tty.usbmodem"));
        
    }

}

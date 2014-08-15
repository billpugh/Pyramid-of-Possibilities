import gnu.io.SerialPort;

import java.io.OutputStreamWriter;


public class WriteSerial {
    
    public static void main(String args[]) throws Exception {
        String p = "/dev/tty.usbserial-A603IUEO";
        SerialPort port = SerialPortFactory.findSerialPortByName(p, 9600);
        OutputStreamWriter fw = new OutputStreamWriter(port.getOutputStream());
        long nextUpdate = System.currentTimeMillis();
        for(char a = 'a'; a <= 'z'; a++) {
            fw.write(a);
            fw.write(a);
             fw.write(a);
              fw.write(a);
            fw.flush();
            System.out.printf("Wrote '%c'%n", a);
            nextUpdate += 1000;
            Thread.sleep(nextUpdate - System.currentTimeMillis());
        }
        fw.close();
    }

}

import gnu.io.SerialPort;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.WritableByteChannel;

public class WaitAndConnect {
    
    

    public static void main(String args[]) throws Exception {

        while (true) {
            String tty = DetectPort.getPortName("tty.usbmodem");
            SerialPort port = SerialPortFactory.findSerialPortByName(tty, 115200);
            System.out.println("Opened " + tty);
            try {
                BufferedReader r = new BufferedReader(new InputStreamReader(
                        port.getInputStream()));
                while (true) {
                    String s = r.readLine();
                    if (s == null)
                        break;
                    System.out.println(s);
                    if (s.equals("PoP board starting")) {
                        String mac = r.readLine();
                        if (mac == null) break;

                        PlatformData platform = Teensies.getPlatform(mac);
                        System.out.println(mac + ":" + platform);
                        ByteBuffer buf = platform.getBytes();
                        OutputStream out = port.getOutputStream();
                        WritableByteChannel channel = Channels.newChannel(out);
                        channel.write(buf);
                        channel.close();
                        System.out.println("Wrote bytebuffer");
                        
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            port.close();

        }

    }

}

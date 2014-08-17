import gnu.io.SerialPort;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.WritableByteChannel;

import javax.speech.synthesis.Synthesizer;

public class AssignPlatforms {
    
    

    public static void main(String args[]) throws Exception {

        Synthesizer synthesizer = SynthesizerFactory. getSynthesizer();
        synthesizer.speakPlainText("Ready to assign platforms", null);
        while (true) {
            try {
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
                    if (s.startsWith("PoP board starting")) {
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
                        String speak = String.format("This is platform T%d dash %d", 
                                platform.identifier / 100, platform.identifier % 100);
                        if (synthesizer != null)
                        	synthesizer.speakPlainText(speak, null);
                        // synthesizer.waitEngineState(Synthesizer.QUEUE_EMPTY);
                  
                        
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            port.close();
            } catch (Exception e) {
                e.printStackTrace();
            }

        }

    }

}

import gnu.io.SerialPort;

import java.io.BufferedReader;
import java.io.InputStreamReader;

import javax.speech.synthesis.Synthesizer;


public class RecordParameters {


    public static void main(String args[]) throws Exception {

        Synthesizer synthesizer = SynthesizerFactory. getSynthesizer();
        if (synthesizer != null) synthesizer.speakPlainText("Ready to assign platforms", null);
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
                    if (!s.equals("OK")) {
                    	if (synthesizer != null) synthesizer.speakPlainText("Got bad response", null);
                    	System.out.println("Got bad response: " + s);
                    	break;
                    }

                    int id = Integer.parseInt(r.readLine());
                    String name = r.readLine();
                    int size = Integer.parseInt(r.readLine());
                    String parameters = r.readLine();
                    AnimationProgram a = AnimationProgram.values()[id];
                    String aName = a.name().substring(2);
                    String speak = String.format("%2d %s %s, %d bytes", id, aName, name, size);
                    System.out.println(speak);
                    if (synthesizer != null) synthesizer.speakPlainText(speak, null);
                    
                    
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

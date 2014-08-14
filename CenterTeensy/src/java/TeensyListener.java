import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;


public class TeensyListener implements Runnable {

    
    InputStream in;
    ReadableByteChannel channel;
    
  
    
    @Override
    public void run() {
        channel = Channels.newChannel(in);
        try {
        while (true) {
            int b = in.read();
            if (b == 't') {
                // have a teensy report
                int l = in.read();
                int crc = in.read();
                ByteBuffer buf = ByteBuffer.allocate(l);
                while (buf.remaining() > 0)
                    channel.read(buf);
                buf.flip();
                PlatformReport report = new PlatformReport(buf);
                System.out.println("Got platform report for platform " + report.identifier);
                System.out.println(report);
                System.out.println();
                
            }
        }
    } catch (IOException e) {
        e.printStackTrace();
    }
        
       
        
    }

}

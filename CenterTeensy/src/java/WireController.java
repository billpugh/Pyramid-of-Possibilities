import gnu.io.SerialPort;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.nio.channels.WritableByteChannel;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.TimeUnit;

public class WireController {

    static final boolean DEBUG = true;

    static class HighPriorityThreadFactory implements ThreadFactory {

        @Override
        public Thread newThread(Runnable r) {
            Thread t = new Thread(r);
            t.setPriority(Thread.MAX_PRIORITY);
            return t;
        }
    }

    static ScheduledThreadPoolExecutor executor = new ScheduledThreadPoolExecutor(
            1000, new HighPriorityThreadFactory());

    volatile long lastSendNanos;

    volatile int lastTweekSent = 0;

    volatile boolean shutdown = false;

    class SendToTeensies implements Runnable {

        Animation lastAnimation;

        @Override
        public void run() {
            try {
                Animation a = CentralControl.currentAnimation;
                if (a == null) {
                    return;
                }
                if (lastAnimation != null
                        && a.sequenceId == lastAnimation.sequenceId && a.tweakStatus.lastTweakAt <= lastTweekSent) {
                	return;
                }
                int now = a.getAnimationMillis();
                Broadcast broadcast = new Broadcast(a);
                ByteBuffer buf = broadcast.getBytes();
                if (false) {
                    System.out.printf("writing to %s bytes %d %d\n", portName,
                            buf.position(), buf.limit());
                    for (int i = buf.position(); i < buf.limit(); i++)
                        System.out.printf("%2x ", buf.get(i));
                    System.out.println();
                }
                outputChannel.write(buf);
                outputStream.flush();
                lastSendNanos = System.nanoTime();
                lastAnimation = a;
                lastTweekSent = now;
            } catch (Throwable e) {
                e.printStackTrace();

            }
        }
    }

    class ReadFromTeensies implements Runnable {

        Animation lastAnimation;

        @Override
        public void run() {
            System.out.println("Reading from teensies on port " + portName);
            while (true) {
                if (shutdown)
                    return;
                try {
                    int b = inputStream.read();
                    if (b != 't')
                        System.out.println("Rejecting byte");
                    else {
                        long delay = System.nanoTime() - lastSendNanos;

                        // have a teensy report
                        int l = inputStream.read();
                        int crc = inputStream.read();
                        ByteBuffer buf = ByteBuffer.allocate(l);
                        while (buf.remaining() > 0)
                            inputChannel.read(buf);

                        buf.flip();

                        PlatformReport report = new PlatformReport(buf);
                        if (DEBUG) {
                            System.out
                                    .printf("Got platform report for platform %3d with delay %,d us\n",
                                            report.identifier, delay / 1000);

                            System.out.println(report);
                            System.out.println();
                        }
                        PlatformStatus status = PlatformStatus.all
                                .get(report.identifier);
                        if (status == null)
                            System.out.printf("Platform %d at %s.%d is unregistered\n",
                                    report.identifier, portName, report.wirePosition);

                        else
                            status.update(portName, report);

                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    SerialPort teensyPort;
    String portName;
    OutputStream outputStream;
    WritableByteChannel outputChannel;
    InputStream inputStream;
    ReadableByteChannel inputChannel;

    WireController(String portName) throws Exception {
        this.portName = portName;
        teensyPort = SerialPortFactory.findSerialPortByName(portName, 38400);
        outputStream = teensyPort.getOutputStream();
        outputChannel = Channels.newChannel(outputStream);
        inputStream = teensyPort.getInputStream();
        inputChannel = Channels.newChannel(inputStream);

        SendToTeensies sendToTeensies = new SendToTeensies();
        sendToTeensies.run();
        executor.scheduleWithFixedDelay(sendToTeensies, 0, 100,
                TimeUnit.MILLISECONDS);
        executor.execute(new ReadFromTeensies());
    }

    public void close() throws IOException {
        inputStream.close();
        System.out.println("Closed input stream " + portName);
        outputStream.close();
        System.out.println("Closed output stream " + portName);
        // teensyPort.close();
        // System.out.println("Closed port " + portName);
    }

}

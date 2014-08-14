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
			20, new HighPriorityThreadFactory());

	class SendToTeensies implements Runnable {

		Animation lastAnimation;

		@Override
		public void run() {
			try {
				Animation a = CentralControl.currentAnimation;
				if (a == lastAnimation || a != null && lastAnimation != null
						&& a.sequenceId == lastAnimation.sequenceId)
					return;
				Broadcast broadcast = new Broadcast(a);
				ByteBuffer buf = broadcast.getBytes();
				if (DEBUG) {
					System.out.printf("writing bytes %d %d\n", buf.position(),
							buf.limit());
					for (int i = buf.position(); i < buf.limit(); i++)
						System.out.printf("%2x ", buf.get(i));
					System.out.println();
				}
				outputChannel.write(buf);
				outputStream.flush();
				lastAnimation = a;
			} catch (IOException e) {
				e.printStackTrace();

			}
		}
	}

	class ReadFromTeensies implements Runnable {

		Animation lastAnimation;

		@Override
		public void run() {
			System.out.println("Reading from teensies");
			while (true) {
				try {
					int b = inputStream.read();
					if (b == 't') {
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
									.println("Got platform report for platform "
											+ report.identifier);
							System.out.println(report);
							System.out.println();
						}

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

		executor.scheduleWithFixedDelay(new SendToTeensies(), 0, 100,
				TimeUnit.MILLISECONDS);
		executor.execute(new ReadFromTeensies());
	}

}

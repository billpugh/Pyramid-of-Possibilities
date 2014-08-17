import java.io.IOException;
import java.io.PrintStream;
import java.io.PushbackInputStream;


public class ReadConsole2 {
    
    public static void main(String args[]) throws IOException, InterruptedException {
        String ttyConfig = ReadConsole.setTerminalToCBreak();
        PushbackInputStream in = new PushbackInputStream(System.in);
        PrintStream out = new PrintStream(System.out, true, "UTF-8");


        try {

                while (true) {
                    int c = CentralControl.getChar(in);
                    if (c < 0) {
                        Thread.sleep(10);
                        continue;
                    }
                    if (c == CentralControl.MUTE)
                        out.print("\uD83D\uDD07");
                    else
                        out.print((char)c);

                } // end while
        }
        catch (IOException e) {
                System.err.println("IOException");
        }
        catch (InterruptedException e) {
                System.err.println("InterruptedException");
        }
        finally {
            try {
                ReadConsole.resetTerminal( ttyConfig );
             }
             catch (Exception e) {
                 System.err.println("Exception restoring tty config");
             }
        }
    }

}

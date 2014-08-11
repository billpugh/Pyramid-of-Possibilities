import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;


public class ReadConsole {
    public static void main2(String args[]) throws IOException, InterruptedException {
        Reader fr = new InputStreamReader(System.in);
        while (true) {
            int a = fr.read();
            if (a == -1)
                break;
            
            System.out.printf("%n%2x", a);
        }
        fr.close();
    }
    
  

    public static void main(String[] args) throws IOException, InterruptedException {
            String ttyConfig = setTerminalToCBreak();
            try {

                    while (true) {

                            if ( System.in.available() != 0 ) {
                                    int c = System.in.read();
                                    if (c >= ' ')
                                    System.out.printf("%n%2x %c", c,c);
                                    else System.out.printf("%n%2x", c);
                                    if ( c == 'q' ) {
                                            break;
                                    } 
                            }
                            Thread.sleep(100);

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
                    resetTerminal( ttyConfig );
                 }
                 catch (Exception e) {
                     System.err.println("Exception restoring tty config");
                 }
            }

    }

    public static String setTerminalToCBreak() throws IOException, InterruptedException {

       String ttyConfig = stty("-g").trim();

        // set the console to be character-buffered instead of line-buffered
        stty("-icanon min 1");

        // disable character echoing
        stty("-echo");
        
        return ttyConfig;
    }
    
    public static void resetTerminal(String ttyConfig) throws IOException, InterruptedException {

        stty(ttyConfig);
       
    }

    /**
     *  Execute the stty command with the specified arguments
     *  against the current active terminal.
     */
    private static String stty(final String args)
                    throws IOException, InterruptedException {
        String cmd = "stty " + args + " < /dev/tty";

        return exec(new String[] {
                    "sh",
                    "-c",
                    cmd
                });
    }

    /**
     *  Execute the specified command and return the output
     *  (both stdout and stderr).
     */
    private static String exec(final String[] cmd)
                    throws IOException, InterruptedException {
        ByteArrayOutputStream bout = new ByteArrayOutputStream();

        Process p = Runtime.getRuntime().exec(cmd);
        int c;
        InputStream in = p.getInputStream();

        while ((c = in.read()) != -1) {
            bout.write(c);
        }

        in = p.getErrorStream();

        while ((c = in.read()) != -1) {
            bout.write(c);
        }

        p.waitFor();

        String result = new String(bout.toByteArray());
        return result;
    }

}


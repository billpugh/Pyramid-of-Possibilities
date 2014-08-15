import java.io.IOException;
import java.io.PushbackInputStream;
import java.util.ArrayList;
import java.util.List;

public class CentralControl {

    static final int LEFT_ARROW = 0x10004;
    static final int RIGHT_ARROW = 0x10003;
    static final int UP_ARROW = 0x10001;
    static final int DOWN_ARROW = 0x10002;

    public static int getChar(PushbackInputStream in) throws IOException {
        if (in.available() == 0)
            return -1;
        int c = in.read();
        if (c == 0x1b) {
            int n = in.read();
            if (n != 0x5b) {
                in.unread(n);
            } else {
                int d = in.read();
                switch (d) {
                case 0x44:
                    return LEFT_ARROW;
                case 0x43:
                    return RIGHT_ARROW;
                case 0x41:
                    return UP_ARROW;
                case 0x42:
                    return DOWN_ARROW;
                default:
                    return d;
                }
            }
        }
        return c;
    }



    static volatile Animation currentAnimation;
    public static void main(String args[]) throws Exception {
        System.out.println("\nWelcome to Central\n");
        String ttyConfig = ReadConsole.setTerminalToCBreak();
        
        List<WireController> controllers = new ArrayList<WireController>();
        List<String> ports = DetectPort.getPorts("tty.usbserial-");
        System.out.printf("Found %d ports%n", ports.size());
        if (ports.isEmpty())
        	return;
        for(String p : ports) {
            System.out.println("Connecting to " + p);
        	controllers.add(new WireController(p));
        }
        
        final int numberAnimations = 5;
        PushbackInputStream in = new PushbackInputStream(System.in);
        int currentAnimation = 0;
        switchToAnimation(currentAnimation);

        try {
            getInput: while (true) {

                int c = getChar(in);
                if (c >= 0) {

//                    System.out.printf("%n%2x: %c%n", c, c);

                    switch (c) {
                    case 'q':
                        break getInput;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        currentAnimation = c - '0';
                        switchToAnimation(currentAnimation);

                        break;
                    case LEFT_ARROW:
                        currentAnimation = (currentAnimation - 1)
                                % numberAnimations;
                        if (currentAnimation < 0)
                            currentAnimation += numberAnimations;
                        switchToAnimation(currentAnimation);

                        break;
                    case RIGHT_ARROW:
                        currentAnimation = (currentAnimation + 1)
                                % numberAnimations;
                        switchToAnimation(currentAnimation);

                        break;
                    }

                }
                Thread.sleep(100);

            } // end while
        } catch (IOException e) {
            System.err.println("IOException");
        } catch (InterruptedException e) {
            System.err.println("InterruptedException");
        } finally {
            try {
                ReadConsole.resetTerminal(ttyConfig);
            } catch (Exception e) {
                System.err.println("Exception restoring tty config");
            }
        }

    }

    
    /**
     * @param currentAnimation
     * @param fw
     * @throws IOException
     */
    public static void switchToAnimation(int programId) throws IOException {
        AnimationProgram program = AnimationProgram.values()[programId];
        currentAnimation = new Animation(program);
       
    }

}

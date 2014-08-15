import java.io.IOException;
import java.io.PushbackInputStream;
import java.util.ArrayList;
import java.util.List;

public class CentralControl {

    static final int LEFT_ARROW = 0x2190;
    static final int RIGHT_ARROW = 0x2192;
    static final int UP_ARROW = 0x2191;
    static final int DOWN_ARROW = 0x2193;
    static final int HOME ='b';
    static final int MUTE = 0x1F507;
    static final int ENTER = 0x0a;

    public static int getChar(PushbackInputStream in) throws IOException {
        if (in.available() == 0)
            return -1;
        int c = in.read();
        if (c == 0x1b) {
            if (in.available() == 0)
                return MUTE;
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
    static  Animation pausedAnimation;
    static long muteUntil = 0;
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
        
        PushbackInputStream in = new PushbackInputStream(System.in);
        int currentAnimationNumber = 0;
        switchToAnimation(currentAnimationNumber);
        StringBuilder numbers = new StringBuilder();

        try {
            getInput: while (true) {

                int c = getChar(in);
                if (c >= 0) {

                    System.out.printf("%n%2x: %c%n", c, c);

                    switch (c) {
                    case 'q':
                        System.out.println("quiting");
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
                        System.out.println("Got number " + c);
                        numbers.append((char)c);
                        break;
                    case HOME:
                        currentAnimationNumber = 0;
                        switchToAnimation(currentAnimationNumber);
                        break;
                    case ENTER:
                        System.out.println("Got enter");
                        if (numbers.length() == 0) {
                            // pulse
                            break;
                        }
                        int number = Integer.parseInt(numbers.toString());
                        System.out.println("Selecting animation " + number);
                        numbers.setLength(0);
                        if (number < AnimationProgram.SIZE) {
                            currentAnimationNumber = number;
                            switchToAnimation(currentAnimationNumber);
                            
                        }
                        break;
                    case MUTE:
                        if (currentAnimation.program == AnimationProgram.e_Mute) {
                            if (System.currentTimeMillis() < muteUntil) {
                                System.out.println("Muted, not switching");
             
                            } else {
                            currentAnimation = pausedAnimation;
                            pausedAnimation = null;
                            System.out.println("Canceling mute");
                            }
                        } else {
                            pausedAnimation = currentAnimation;
                            muteUntil = System.currentTimeMillis() + 15000;
                            currentAnimation = new Animation(AnimationProgram.e_Mute);
                            System.out.println("Muting");
                        }
                        break;
                    case LEFT_ARROW:
                        currentAnimationNumber = (currentAnimationNumber - 1)
                                % AnimationProgram.SIZE;
                        if (currentAnimationNumber < 0)
                            currentAnimationNumber += AnimationProgram.SIZE;
                        switchToAnimation(currentAnimationNumber);

                        break;
                    case RIGHT_ARROW:
                        currentAnimationNumber = (currentAnimationNumber + 1)
                                % AnimationProgram.SIZE;
                        switchToAnimation(currentAnimationNumber);

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
                for(WireController w : controllers)
                    w.close();
                WireController.executor.shutdownNow();
            } catch (Exception e) {
                System.err.println("Exception restoring tty config");
            }
        }
        Thread.sleep(1000);
        System.exit(0);

    }

    
    /**
     * @param currentAnimation
     * @param fw
     * @throws IOException
     */
    public static void switchToAnimation(int programId) throws IOException {
        if (System.currentTimeMillis() < muteUntil) {
            System.out.println("Muted, not switching");
            return;
        }
        AnimationProgram program = AnimationProgram.values()[programId];
        System.out.println("Switching to " + program.name());
        currentAnimation = new Animation(program);
       
    }

}

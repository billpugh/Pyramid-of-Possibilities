
public class ScaleBrightness {
    
    static final int chunk = 16;
    static int scaleBrightness(int value) {
        int result = 0;
        while (value > chunk) {
            result += chunk;
            value -= chunk;
            value/=2;
        }
        return result + value;
        
    }
    
    public static void main(String args[]) {
        for(int i = 0; i < 256; i++)
            System.out.printf("%3d %3d%n", i, scaleBrightness(i));
    }

}

import java.nio.ByteBuffer;


public class Util {
    
     static String toString(ByteBuffer buf, int size) {
        StringBuilder builder = new StringBuilder();
        for(int i = 0; i < size; i++) {
            int v = 0xff & buf.get();
            builder.append(String.format("%02x", v));
        }
        return builder.toString();
    }
     static void putBytes(ByteBuffer buf, String hexString) {
         hexString = hexString.trim();
         int length = hexString.length();
         if (length % 2 != 0) throw new IllegalArgumentException(hexString);
         length /= 2;

         for(int i = 0; i < length; i++) {
             int v = Integer.parseInt(hexString.substring(i*2, i*2+2));
             if (v < 0 || v > 255) throw new IllegalArgumentException(hexString);
             buf.put((byte)v);
         }
        
     }

}

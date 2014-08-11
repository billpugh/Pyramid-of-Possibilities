import java.nio.ByteBuffer;
import java.nio.ByteOrder;


public class Broadcast {
    
    public Broadcast(Animation animation) {
        this.animation = animation;
    }

    final byte kind = (byte) 'p';
    float medianActivityLevel;
    Animation animation;
    
    
    public void write(ByteBuffer buf ) {
        buf.put(kind);
        buf.put((byte)0);
        buf.put((byte)0);
        buf.putFloat(medianActivityLevel);
        animation.write(buf);
        
        buf.put((byte) 0); // no animations yet
        
        buf.flip();
        int size = buf.limit();
        if (size > 255)
            throw new IllegalStateException("Broadcast is " + size + " bytes");
        buf.put(1, (byte) size);
        
    }
    
    ByteBuffer buf = ByteBuffer.allocate(200);
    public ByteBuffer getBytes() {
        buf.clear();
        buf.order(ByteOrder.LITTLE_ENDIAN);
        
        write(buf);
        buf.flip();

        return buf;
    }
    
    public static void main(String args[] ) {
        ByteBuffer buf = ByteBuffer.allocate(100);
        buf.order(ByteOrder.LITTLE_ENDIAN);
        Broadcast b = new Broadcast(new Animation(AnimationProgram.e_Beacon));
        b.write(buf);
        
        System.out.println(buf.position());
        System.out.println(buf.limit());
        
       
    }
    
}

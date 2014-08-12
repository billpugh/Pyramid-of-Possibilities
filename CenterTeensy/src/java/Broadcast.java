import java.nio.ByteBuffer;
import java.nio.ByteOrder;


public class Broadcast {
    
    public Broadcast(Animation animation) {
        this.animation = animation;
    }

    final byte kind = (byte) 'p';
    float medianActivityLevel;
    Animation animation;
    byte status = 0;
    
    
    public void write(ByteBuffer buf ) {
        int position = buf.position();
        buf.put(kind);
        buf.put((byte)0);
        buf.put((byte)0);
        buf.put(status);
        buf.putLong(BurnerTime.getGlobalTime());
        buf.putFloat(medianActivityLevel);
       
        animation.write(buf);
        
        buf.put((byte) 0); // no animations yet
        
        int size = buf.position() - position - 3;
        if (size > 255)
            throw new IllegalStateException("Broadcast is " + size + " bytes");
        buf.put(position+1, (byte) size);
        
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

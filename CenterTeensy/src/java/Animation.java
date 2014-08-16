import java.nio.ByteBuffer;
import java.nio.ByteOrder;


public class Animation {
    
    enum TweakKind { SIGNED, UNSIGNED, CYCLIC;
     byte add(int currentValue, int offset) {
         switch (this) {
         case SIGNED:
             currentValue += offset;
             if (currentValue < -128) return -128;
             else if (currentValue > 127)
                 return 127;
             return (byte) currentValue;
         case UNSIGNED:
             currentValue = currentValue & 0xff;
             currentValue += offset;
             if (currentValue < 0) return 0;
             else if (currentValue > 255)
                 return (byte)255;
             return (byte) currentValue;
         }
         return (byte)(currentValue + offset);
     }
    };

	  class CycleStatus {
		    final byte cpm;
	    	final  double cycles;
	    	 final  int computedAt;
	    	 public CycleStatus(int computedAt) {
	    		 this((byte)30, 0, computedAt);
	    	 }
			private CycleStatus(byte cpm, double cycles, int computedAt) {
				this.cpm = cpm;
				this.cycles = cycles;
				this.computedAt = computedAt;
			}
			
			CycleStatus tweakUp() {
				int at = BurnerTime.getGlobalTime();
				if (at < computedAt) throw new IllegalArgumentException();
				double newCycleCount = cycles + cpm * (at-computedAt)/60000.0;
				int increment = 1;
				if (computedAt + 500 > at)
				    increment = 4;

				return new CycleStatus(program.tweakKind.add(cpm, increment), newCycleCount, at);
			}
			CycleStatus tweakDown() {
				int at = BurnerTime.getGlobalTime();
				if (at < computedAt) throw new IllegalArgumentException();
				double newCycleCount = cycles + cpm * (at-computedAt)/60000.0;
				int decrement = -1;
                if (computedAt + 500 > at)
                    decrement = -4;

				int newValue = cpm;
				
			    return new CycleStatus(program.tweakKind.add(cpm, decrement), newCycleCount, at);
	            
			}
			
	    }
	 
    final AnimationProgram program;
    final byte sequenceId;
    
    
   
    public void tweakUp() {
    	cycleStatus = cycleStatus.tweakUp();
    }
    public void tweakDown() {
    	cycleStatus = cycleStatus.tweakDown();
    }
    final int startTime = BurnerTime.getGlobalTime();
    volatile CycleStatus cycleStatus = new CycleStatus(startTime);
    byte [] parameters;
    
    static byte nextSequenceId = 0;

    public Animation(AnimationProgram program, byte[] parameters) {
        this.program = program;
        this.sequenceId = nextSequenceId++;
        this.parameters = parameters;
    }

    public Animation(AnimationProgram program) {
       this(program, new byte[0]);
    }

    public  CycleStatus getCycles() {
    	return cycleStatus;
    }

    public short byteLength() {
        int length = 17+parameters.length;
        if (length > Short.MAX_VALUE)
            throw new AssertionError();
        return (short) length;
        
    }

    public void write(ByteBuffer buf ) {
        buf.put((byte)program.ordinal());
        buf.put(sequenceId);
        buf.putInt(startTime);
        CycleStatus cycles = getCycles();
        buf.putFloat((float)cycles.cycles);
        buf.putInt(cycles.computedAt);
        buf.put(cycles.cpm);
        buf.putShort(byteLength());
        if (parameters.length > 0)
            buf.put(parameters);
    }
    

    public ByteBuffer getBytes() {
        ByteBuffer buf = ByteBuffer.allocate(byteLength()+20);
        buf.order(ByteOrder.LITTLE_ENDIAN);
        
        write(buf);
        buf.flip();

        if (buf.limit() != byteLength())
            throw new AssertionError(
                    String.format("limit is %d, bytelength is %d", 
                            buf.limit(), byteLength()));

        return buf;
    }
    
    public static void main(String args[]) {
        Animation a = new Animation(AnimationProgram.e_ActivityLevelAnimation);
        ByteBuffer buf = a.getBytes();
        System.out.println(a.byteLength());
        System.out.println(buf.limit());
        
    }
}

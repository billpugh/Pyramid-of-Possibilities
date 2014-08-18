import java.nio.ByteBuffer;
import java.nio.ByteOrder;


public class Animation {
    
    enum TweakKind { SIGNED, UNSIGNED, CYCLIC, CYCLIC_UNARY;
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
         case CYCLIC:
         case CYCLIC_UNARY:
        	 return (byte)(currentValue + offset);
         }
         return (byte)(currentValue + offset);
     }
    };

	  class TweakStatus {
		    final byte tweakValue;
	    	final  double cycles;
	    	final double tweakCount;
	    	// Relative to animationStartTime
	    	 final  int lastTweakAt;
	    	 public TweakStatus() {
	    		 this((byte)30, 0, 0, 0);
	    	 }
	    	 
	    	 public int getIntValue() {
	    		 if (program.tweakKind == TweakKind.SIGNED)
	    			 return tweakValue;
	    		 return 0xff & tweakValue;
	    	 }

			private TweakStatus(byte cpm, double cycles, double tweakCount, int computedAt) {
				this.tweakValue = cpm;
				this.cycles = cycles;
				this.tweakCount = tweakCount;
				this.lastTweakAt = computedAt;
			}
			
			TweakStatus tweakUp() {
				int at = getAnimationMillis();
				if (at < lastTweakAt) throw new IllegalArgumentException();
				double newTweakCount = tweakCount+ 1 - (at-lastTweakAt)/500.0;
				if (newTweakCount < 0)
					newTweakCount = 0;
				else if (newTweakCount > 8)
					newTweakCount = 8;
				double newCycleCount = cycles + tweakValue * (at-lastTweakAt)/120000.0;
				int increment = 1;
				if (program.tweakKind !=TweakKind.CYCLIC_UNARY && newTweakCount > 5)
				    increment = 4;

				return new TweakStatus(program.tweakKind.add(tweakValue, increment), newCycleCount, newTweakCount, at);
			}
			TweakStatus tweakDown() {
				int at =  getAnimationMillis();
				if (at < lastTweakAt) throw new IllegalArgumentException();
				double newTweakCount = tweakCount+ 1 - (at-lastTweakAt)/500.0;
				if (newTweakCount < 0)
					newTweakCount = 0;
				else if (newTweakCount > 8)
					newTweakCount = 8;
				double newCycleCount = cycles + tweakValue * (at-lastTweakAt)/120000.0;
				int decrement = -1;
                if (program.tweakKind !=TweakKind.CYCLIC_UNARY && newTweakCount > 5)
                    decrement = -4;
				
			    return new TweakStatus(program.tweakKind.add(tweakValue, decrement), newCycleCount, newTweakCount, at);
	            
			}
			
	    }
	 
    final AnimationProgram program;
    final byte sequenceId;
   
    final int startTime = BurnerTime.getGlobalTime();
    volatile TweakStatus cycleStatus = new TweakStatus();
    byte [] parameters;
    
    
    public void write(ByteBuffer buf ) {
        buf.put((byte)program.ordinal());
        buf.put(sequenceId);
        buf.putInt(startTime);
        TweakStatus cycles = getCycles();
        buf.putFloat((float)cycles.cycles);
        buf.putInt(cycles.lastTweakAt);
        buf.put(cycles.tweakValue);
        buf.putShort(byteLength());
        if (parameters.length > 0)
            buf.put(parameters);
    }
    
    
    static byte nextSequenceId = 0;

    public void tweakUp() {
    	cycleStatus = cycleStatus.tweakUp();
    }
    public void tweakDown() {
    	cycleStatus = cycleStatus.tweakDown();
    }
    
    public int getAnimationMillis() {
    	 return BurnerTime.getGlobalTime() - startTime;
    }
    
    public Animation(AnimationProgram program, byte[] parameters) {
        this.program = program;
        this.sequenceId = nextSequenceId++;
        this.parameters = parameters;
    }

    public Animation(AnimationProgram program) {
       this(program, new byte[0]);
    }

    public  TweakStatus getCycles() {
    	return cycleStatus;
    }

    public short byteLength() {
        int length = 17+parameters.length;
        if (length > Short.MAX_VALUE)
            throw new AssertionError();
        return (short) length;
        
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

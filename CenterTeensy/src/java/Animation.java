import java.nio.ByteBuffer;
import java.nio.ByteOrder;


public class Animation {

	 static class CycleStatus {
	    	final  double cycles;
	    	 final  long computedAt;
			public CycleStatus(double cycles, long computedAt) {
				this.cycles = cycles;
				this.computedAt = computedAt;
			}
			
			CycleStatus asOf(int cpm, long t) {
				if (t < computedAt) throw new IllegalArgumentException();
				return new CycleStatus(cycles + cpm * (t-computedAt)/60000.0, t);
			}
	    }
	 
    final AnimationProgram program;
    final byte sequenceId;
    
    
   
    int cpm;
    final long startTime = BurnerTime.getGlobalTime();
    volatile CycleStatus cycleStatus = new CycleStatus(0, startTime);
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

    public synchronized void updateCycles() {
    	cycleStatus = cycleStatus.asOf(cpm, BurnerTime.getGlobalTime() );
    	
    }
    public  CycleStatus getCycles() {
    	return cycleStatus;
    }

    public short byteLength() {
        int length = 1+1+2+8+parameters.length;
        if (length > Short.MAX_VALUE)
            throw new AssertionError();
        return (short) length;
        
    }

    public void write(ByteBuffer buf ) {
        buf.put((byte)program.ordinal());
        buf.put(sequenceId);
        buf.putLong(startTime);
        CycleStatus cycles = getCycles();
        buf.putFloat((float)cycles.cycles);
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

import java.nio.ByteBuffer;
import java.util.Arrays;


public class PlatformReport {

    byte status;
    short identifier;
    byte wirePosition;
    byte taps;
    float[] localActivity = new float[3];
    
    
    public PlatformReport(ByteBuffer buf) {
        get(buf);
    }
    

    public void get(ByteBuffer buf ) {
        status = buf.get();
        identifier = buf.getShort();
        wirePosition = buf.get();
        taps = buf.get();
        for(int i = 0; i < 3; i++)
            localActivity[i] = buf.getFloat();
    }

    @Override
    public String toString() {
        return "PlatformReport [status=" + status + ", identifier="
                + identifier + ", wirePosition=" + wirePosition + ", taps="
                + taps + ", localActivity=" + Arrays.toString(localActivity)
                + "]";
    }
    
}

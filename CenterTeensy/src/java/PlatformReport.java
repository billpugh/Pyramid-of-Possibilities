import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;


public class PlatformReport {

    byte status;
    Short identifier;
    byte wirePosition;
    byte taps;
    float[] localActivity = new float[3];
    
    
    public PlatformReport(ByteBuffer buf) {
        get(buf);
    }
    

    public void get(ByteBuffer buf ) {
        buf.order(ByteOrder.LITTLE_ENDIAN);
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
                + Integer.toString(0xff&taps,16) + ", localActivity=" + Arrays.toString(localActivity)
                + "]";
    }
    
}

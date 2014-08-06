import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.charset.Charset;
import java.util.Map;
import java.util.TreeMap;

import org.apache.commons.csv.CSVFormat;
import org.apache.commons.csv.CSVParser;
import org.apache.commons.csv.CSVRecord;


public class PlatformData {
    
    static Map<Short, PlatformData> allPlatforms = new TreeMap<Short, PlatformData>();
    static File data = new File("data/triadRings.csv");
    

    
    @Override
    public String toString() {
        return "PlatformData [identifier=" + identifier + ", x=" + x + ", y="
                + y + ", z=" + z + ", direction=" + direction + "]";
    }


    // What is the identify of the platform (unique)
    short identifier;

    public PlatformData(short identifier, short x, short y, short z,
            byte direction) {
        this.identifier = identifier;
        this.x = x;
        this.y = y;
        this.z = z;
        this.direction = direction;
    }

    public ByteBuffer getBytes() {
        ByteBuffer buf = ByteBuffer.allocate(12);
        buf.order(ByteOrder.LITTLE_ENDIAN);
        buf.putShort(identifier);
        buf.putShort(x);
        buf.putShort(y);
        buf.putShort(z);
        buf.put(direction);
        buf.flip();
        
        return buf;
    }

    // What is the x,y,z displacement of the center of the platform
    // from the center base of the Pyramid
    short x,y,z;

    // base rotation direction for interlocking gears
    byte direction;

    
    
    private static short getNumber(CSVRecord record, String field) {
        String s = record.get(field);
        return Short.parseShort(s);
    }
    public static PlatformData parse(CSVRecord record) {
        return new PlatformData(
                getNumber(record,"identifier"),
                getNumber(record,"x"),
                getNumber(record,"y"),
                getNumber(record,"z"),
                (byte) getNumber(record,"direction"));   
    }
    
    
    static private void initialize() throws IOException {
        
        CSVParser parser = CSVParser.parse(data, Charset.defaultCharset(),
                CSVFormat.EXCEL.withHeader());
        for (CSVRecord csvRecord : parser) {

//            System.out.println(csvRecord);
            PlatformData p = parse(csvRecord);
            allPlatforms.put(p.identifier, p);
           
        }

    }
    
    static {
        try {
        initialize();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    
    
    
    public static void main(String args[]) throws IOException {
        PlatformData p = allPlatforms.get((short)1);
        System.out.println(p);
        ByteBuffer buf = p.getBytes();
        System.out.println(buf.limit());
        
        
    }
       
}

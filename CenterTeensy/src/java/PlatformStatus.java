import java.util.TreeMap;


public class PlatformStatus {
    
    static TreeMap<Short, PlatformStatus> all = new TreeMap<Short, PlatformStatus>();
    
    
    static {
        for(Short s : PlatformData.allPlatforms.keySet()) 
            all.put(s,  new PlatformStatus(s));
    }
    
    final short id;
    int status;
    final float accelerometerData[] = new float[3];
    long lastUpdate;
    int wirePosition;
    public PlatformStatus(short id) {
        this.id = id;
    }
    
    
    
    
    

}

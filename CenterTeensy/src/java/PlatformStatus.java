import java.util.TreeMap;


public class PlatformStatus {
    
    static TreeMap<Short, PlatformStatus> all = new TreeMap<Short, PlatformStatus>();
    
    
    static {
        for(Short s : PlatformData.allPlatforms.keySet()) 
            all.put(s,  new PlatformStatus(s));
    }
    
    final Short id;
    int status;
    final float accelerometerData[] = new float[3];
    
    // milli time
    long lastUpdate;
    int wirePosition;
    String port;
    public PlatformStatus(short id) {
        this.id = id;
    }
    
  synchronized  void update(String port, PlatformReport report) {
      
      lastUpdate = System.currentTimeMillis();
      this.status = report.status;
      this.port = port;
      this.wirePosition = report.wirePosition;
      System.arraycopy(report.localActivity, 0, accelerometerData, 0, 3);
  }
    
    

}

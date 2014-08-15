import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;
import java.util.TreeSet;

import org.apache.commons.csv.CSVFormat;
import org.apache.commons.csv.CSVParser;
import org.apache.commons.csv.CSVPrinter;
import org.apache.commons.csv.CSVRecord;


public class Teensies {
    
  static Map<String, Short > assignments = new HashMap<String,Short>();
  static Map<Short, String > teensies = new TreeMap<Short, String>();
  
    static final File stored = new File("data/assignments.csv");
  
    
    public static void main(String args[]) throws IOException {

        System.out.printf("Have assigned %d platforms %s", assignments.size(), assignments.values());
        PlatformData test = getPlatform("test");
        System.out.println(test);
        
    }
    
    static {
        try {
        initialize();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    static private void initialize() throws IOException {
        
        
        CSVParser parser = CSVParser.parse(stored, Charset.defaultCharset(),
                CSVFormat.RFC4180.withHeader());
        for (CSVRecord csvRecord : parser) {
            String mac = csvRecord.get("mac");
            Short identifier = Short.parseShort(csvRecord.get("identifier"));
            assignments.put(mac, identifier);
            teensies.put(identifier, mac);
        }
        parser.close();
        

    }
    
    
    
    static PlatformData getPlatform(String mac) throws IOException {
        Short identifier = assignments.get(mac);
        if (identifier == null) {
            TreeSet<Short> available = new TreeSet<Short>(PlatformData.allPlatforms.keySet());
            available.removeAll(assignments.values());
            if (available.isEmpty()) 
                throw new RuntimeException("All platforms assigned: " + assignments.values());

            identifier = available.first();
            assignments.put(mac, identifier);
            teensies.put(identifier, mac);
            writeAssignments();
        }
        return PlatformData.allPlatforms.get(identifier);
            
    }

    private static void writeAssignments() throws IOException {
        PrintWriter out = new PrintWriter(stored);
        CSVPrinter printer = new CSVPrinter(out, CSVFormat.RFC4180.withHeader("mac", "identifier"));
        for(Map.Entry<Short, String> e : teensies.entrySet()) {
            printer.printRecord(e.getValue(), e.getKey());
        }
        printer.close();
    }
    

}

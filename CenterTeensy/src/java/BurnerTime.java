import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.TimeZone;


public class BurnerTime {
    
    
    static final TimeZone BURNER_ZONE = TimeZone.getTimeZone("America/Los_Angeles");
    static final GregorianCalendar START = new GregorianCalendar(BURNER_ZONE);
  
        static {
        START.set(Calendar.HOUR_OF_DAY, 0);
        START.set(Calendar.MINUTE, 0);
        START.set(Calendar.SECOND, 0);
    }

static int getGlobalTime() {
    long value = System.currentTimeMillis() - START.getTimeInMillis();
    if (value > Integer.MAX_VALUE)
    	throw new IllegalArgumentException("Can't represent burning time with 32 bits");
    return (int) value;
}
    public static void main(String args[]) {
        
        SimpleDateFormat df = new SimpleDateFormat( "yyyy.MM.dd G 'at' hh:mm:ss a z");
       
        System.out.println(START);
        
        System.out.println((System.currentTimeMillis() - START.getTimeInMillis())/1000/60/60);
        System.out.println(df.format(START.getTime()));
        
        
        
    }
}

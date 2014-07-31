import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.CountDownLatch;


public class TimerTest extends TimerTask {

    
    static Date start;
    TimerTest(int num) {
        this.num = num;
    }
    static CountDownLatch warmup = new CountDownLatch(1);
    static int offset[] = new int[100];
    public static void main(String args[]) throws InterruptedException {
        Timer timer = new Timer("Communications timer");
        TimerTest task = new TimerTest(100);
        start = new Date(System.currentTimeMillis() + 100);
        timer.scheduleAtFixedRate(task, start, 100);
        warmup.await();
        warmup = new CountDownLatch(1);
        start = new Date(System.currentTimeMillis() + 100);
        
        timer.scheduleAtFixedRate(new TimerTest(1000), start, 100);
        warmup.await();
        warmup = new CountDownLatch(1);
        start = new Date(System.currentTimeMillis() + 100);
        
        timer.scheduleAtFixedRate(new TimerTest(1000), start, 100);
        
    }

    int count = 0;
    final int num;
    
    @Override
    public void run() {
        int diff = (int)(System.currentTimeMillis() - start.getTime() - 100*count);
        count++;
        diff = diff+10;
        if (diff < 0) diff = 0;
        else if (diff >= offset.length)
            diff = offset.length-1;
        offset[diff]++;
         if (count >= num) {
             for(int i = 0; i < offset.length; i++)
                 if (offset[i] > 0) 
                     System.out.printf("%3d %5d\n", i-10, offset[i]);
             System.out.println();
             cancel();
             warmup.countDown();
         }
        
    }
}

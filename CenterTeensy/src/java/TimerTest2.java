import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.TimeUnit;


public class TimerTest2 implements Runnable {

    static class MyThreadFactoory implements ThreadFactory {

        @Override
        public Thread newThread(Runnable r) {
           Thread t = new Thread(r);
           t.setPriority(Thread.MAX_PRIORITY);
           return t;
        }}
    
    TimerTest2(int num) {
        this.num = num;
    }
    static CountDownLatch warmup = new CountDownLatch(1);
    int offset[] = new int[1000];
    static final int base = 500;
    public static void main(String args[]) throws InterruptedException {
        ScheduledThreadPoolExecutor executor 
        = new ScheduledThreadPoolExecutor(5, new MyThreadFactoory());
        TimerTest2 task = new TimerTest2(100);
        executor.scheduleWithFixedDelay(task, 0, 100, TimeUnit.MILLISECONDS);
        warmup.await();
        warmup = new CountDownLatch(1);
        
        executor.scheduleWithFixedDelay(new TimerTest2(1000), 0, 100, TimeUnit.MILLISECONDS);
        warmup.await();
        warmup = new CountDownLatch(1);
        
        executor.scheduleWithFixedDelay(new TimerTest2(1000), 0, 100, TimeUnit.MILLISECONDS);
        
        
    }

    int count = 0;
    long last = -1;
    final int num;
    
    @Override
    public void run() {
        long now = System.nanoTime();
        if (last == -1) {
            last = now;
            return;
        }
        int diff = (int)((now-last-100000000)/100000);
        last = now;
        count++;
        diff = diff+base;
        if (diff < 0) {
            diff = 0;
        }
        else if (diff >= offset.length) {
            diff = offset.length-1;
        }

        offset[diff]++;

         if (count >= num) {
             for(int i = 0; i < offset.length; i++)
                 if (offset[i] > 0) 
                     System.out.printf("%3d %5d\n", i-base, offset[i]);
             System.out.println();

             warmup.countDown();
             throw new RuntimeException("Expired");
         }
        
    }
}

import java.util.Random;
import java.util.concurrent.BlockingQueue;

public class producer implements Runnable {
	
	// The blocking queue that will be used
	BlockingQueue<String> linkedQueue;
	// This integer, i, is the amount of objects that the producer has created; it is incremented each
	// time the produce method is called so I will use it when printing the summary
	public static int i = 0;
	// The shared boolean that will tell the consumers if this method is still running
	public boolean running;
	
	// The constructor that will pass in the BlockingQueue being used, as well
	// as the shared boolean to check if the producer is still running
	public producer(BlockingQueue<String> queue, Boolean completed) {
		linkedQueue = queue;
		running = completed;
	}
	
	@Override
	public void run() {

		// This loop will ensure that the produce continues to run while there are less than
		// one thousand strings produced
		while (running) {
			try {
				produce(i++); // Increment i each time a producer creates a string
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			// This statement will check if there are one thousand strings produced and stop
			// the while loop if so
			if (i==1000) {
				running = false;
			}
		}
	}
	
	
	public void produce(int givenint) throws InterruptedException {
		Random random = new Random();
		
		// Putting a string form of some random double into the queue using 'put' to
		// ensure that it waits if the queue is full
		linkedQueue.put(String.valueOf(random.nextDouble()));
		
		
		// This will check to see if the current amount of strings produced is a divisor
		// of 100, if so then it will print out how many it has produced so far
		if (i % 100 == 0) {
			System.out.println(Thread.currentThread().getName() + ": " + i + " events produced." + "\n" + "------------------");
		}
	}


}

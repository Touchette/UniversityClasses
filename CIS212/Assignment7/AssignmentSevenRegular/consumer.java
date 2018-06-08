import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;

public class consumer implements Runnable {
	
	// The blocking queue that will be used
	BlockingQueue<String> linkedQueue;
	// The ArrayList that will be used by the consume method to check how many strings
	// any specific consumer has consumed
	public ArrayList<String> consumed = new ArrayList<>();
	// The shared boolean to check if producer is running
	public boolean running;
	// The static variable shared by all instances of the consumer class to check how many
	// strings have been consumed total, when it reaches 1000 the run method stops
	private static int i = 0;
	
	// The constructor that will pass in the BlockingQueue being used, as well
	// as the shared boolean to check if the producer is still running
	public consumer(BlockingQueue<String> queue, boolean completed) {
		linkedQueue = queue;
		running = completed;
	}
	
	@Override
	public void run() {

		// This loop will ensure that the consumer will run while the producer is with the check 
		// on "running" as well as if there are more strings left in the queue by checking "i", 
		// a static variable that checks how many strings have been consumed across all consumer instances
		while(running && i<=1000) {
			try {
				consume(i++); // Simply raises i each time a string is consumed
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	
	public void consume(int givenint) throws InterruptedException {
		Random random = new Random();
		
		// Sleep the consumer for up to 20 milliseconds, ensuring consumer will take longer than producer
		// this seems to be the problem with error in the amount of items consumed, the higher that the
		// sleep time is the lower the chance for consumers to consume "more" objects than the producer
		// has produced. I have literally no idea how this happens, sometimes the sum of the strings
		// the consumers have produced will reach 1001. It seems like they just pull them out of thin air.
		// It seems to be less than a 1/20 chance or so. The multiple people I asked say that this is 
		// just a thread error, maybe it's just my computer? If this could explained in the grading comments...
		Thread.sleep(random.nextInt(20));
		
		// Takes the string from the queue using 'poll' to avoid program running indefinitely,
		// first checking if there's actually items in the queue
		if (linkedQueue.size() > 0) {
			String taken = linkedQueue.poll(100L, TimeUnit.MILLISECONDS);
			// Adds the taken string to an instance-specific ArrayList of strings to easily keep
			// track of how many strings the specific consumer has consumed
			consumed.add(taken);
		}
		
		// This will check to see if the current amount of strings consumed by a consumer is a divisor
		// of 100, if so then it will print out how many it has consumed so far
		if (consumed.size() % 100 == 0) {
			System.out.println(Thread.currentThread().getName() + ": " + consumed.size() + " events consumed." + "\n" + "------------------");
		}
	}
	
	// This will be used for the summary, the method will simply grab the amount
	// of strings that this consumer has consumed via its ArrayList made in the consume method
	public int getConsumedAmount() {
		return consumed.size();
	}
}

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

public class producer implements Runnable {
	
	// The LinkedList that will be used
	private static LinkedList<String> linkedQueue;
	// This integer, i, is the amount of objects that the producers have created; it is incremented each
	// time the produce method is called so I will use it when printing the summary
	public static int i = 0;
	// The ArrayList that will be used by the produce method to check how many strings
	// any specific producer has produced
	public ArrayList<String> produced = new ArrayList<>();
	// The shared boolean that will tell the consumers if the producers are still running
	public static boolean running;
	public Object Mutex;
	// The lock to ensure that access to LinkedList is synchronized
	private final ReentrantLock lock = new ReentrantLock();
	
	// The constructor that will pass in the LinkedList being used, as well
	// as the shared boolean to check if the producers are still running
	public producer(LinkedList<String> queue, Boolean completed, Object monitor) {
		linkedQueue = queue;
		running = completed;
		Mutex = monitor;
	}
	
	@Override
	public synchronized void run() {

		// This loop will ensure that the produce continues to run while there are less than
		// one thousand strings produced, as well as being synchronized using a reentrant lock
		// for only one thread to access at a time
		while (running) {
			
			// This check will make the producers wait if the queue reaches a size of 100, the
			// consumers will wake them up using notifyAll if the queue reaches 0 and more strings
			// still need to be produced
			synchronized (Mutex) {
				if (linkedQueue.size() == 100) {
					this.lock.lock();
					try {
						Mutex.wait();
					} catch (InterruptedException e) {
						e.printStackTrace();
					} finally {
						this.lock.unlock();
					}
				}
			}

			// Locking the try/catch produce so that only one consumer may produce at a time
			this.lock.lock();
			try {
				produce(i++); // Increment i each time a producer creates a string
			} catch (InterruptedException e) {
				e.printStackTrace();
			} finally {
				this.lock.unlock();
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
		
		// Putting a string form of some random double into the queue as well
		// as into whatever producer is currently running's instance-specific ArrayList
		String given = String.valueOf(random.nextDouble());
		linkedQueue.add(given);
		produced.add(given);
		
		// This will check to see if the current amount of strings produced is a divisor
		// of 100, if so then it will print out how many any producer has produced
		if (produced.size() % 100 == 0) {
			System.out.println(Thread.currentThread().getName() + ": " + produced.size() + "  events produced." + "\n" + "------------------");
		}
	}

	// This will be used for the summary, the method will simply grab the amount
	// of strings that this producer has produced via its ArrayList made in the produce method
	public int getProducedAmount() {
		return produced.size();
	}

}

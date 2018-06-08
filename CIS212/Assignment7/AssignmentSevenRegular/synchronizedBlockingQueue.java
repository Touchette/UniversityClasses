import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class synchronizedBlockingQueue {
	
	// The LinkedBlockingQueue with a limit of 100 strings to ensure the producer has to wait
	private static BlockingQueue<String> linkedQueue = new LinkedBlockingQueue<String>(100);
	// The shared boolean to check if producer is running
	private static boolean running = true;
	// Create the consumers beforehand so I may call their respective "getConsumedAmount" methods
	static consumer consumer1 = new consumer(linkedQueue, running);
	static consumer consumer2 = new consumer(linkedQueue, running);
	static consumer consumer3 = new consumer(linkedQueue, running);
	static consumer consumer4 = new consumer(linkedQueue, running);

	
	public static void main (String[] args) throws InterruptedException {
		
		// Creating all the threads, only one producer is used so it doesn't need to be made beforehand
		Thread t1 = new Thread(new producer(linkedQueue, running), "Producer 1");
		Thread t2 = new Thread(consumer1, "Consumer 1");
		Thread t3 = new Thread(consumer2, "Consumer 2");
		Thread t4 = new Thread(consumer3, "Consumer 3");
		Thread t5 = new Thread(consumer4, "Consumer 4");
		
		t1.start();
		t2.start();
		t3.start();
		t4.start();
		t5.start();
		
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		
		// Printing the summary of how many strings each consumer consumed respectively, as well as the amount
		// of strings created by the producer ... sorry in advance about the number of comments, I made them so 
		// I could ask people for help easier.
		System.out.println("Summary:" + "\n");
		System.out.println("Producer 1 produces: " + producer.i + " events." + "\n");
		System.out.println("Consumer 1 consumes: " + consumer1.getConsumedAmount() + " events." + "\n");
		System.out.println("Consumer 2 consumes: " + consumer2.getConsumedAmount() + " events." + "\n");
		System.out.println("Consumer 3 consumes: " + consumer3.getConsumedAmount() + " events." + "\n");
		System.out.println("Consumer 4 consumes: " + consumer4.getConsumedAmount() + " events." + "\n");
	}
	
}

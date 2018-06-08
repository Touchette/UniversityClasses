import java.util.LinkedList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class synchronizedBlockingQueue {
	
	// The LinkedBlockingQueue with a limit of 100 strings to ensure the producer has to wait
	private static LinkedList<String> linkedQueue = new LinkedList<String>();
	// The shared boolean to check if producer is running
	private static boolean running = true;
	public static Object Mutex = new Object();
	// Create the consumers beforehand so I may call their respective "getConsumedAmount" methods
	static consumer consumer1 = new consumer(linkedQueue, running, Mutex);
	static consumer consumer2 = new consumer(linkedQueue, running, Mutex);
	static consumer consumer3 = new consumer(linkedQueue, running, Mutex);
	static consumer consumer4 = new consumer(linkedQueue, running, Mutex);
	// Creating the producers beforehand so I may call their respective "getProducedAmount" methods
	static producer producer1 = new producer(linkedQueue, running, Mutex);
	static producer producer2 = new producer(linkedQueue, running, Mutex);
	static producer producer3 = new producer(linkedQueue, running, Mutex);
	
	static ExecutorService executor = Executors.newCachedThreadPool();

	
	public static void main (String[] args) throws InterruptedException {
		
		executor.execute(producer1);
		executor.execute(producer2);
		executor.execute(producer3);
		
		executor.execute(consumer1);
		executor.execute(consumer2);
		executor.execute(consumer3);
		executor.execute(consumer4);
		
		executor.shutdown();
		executor.awaitTermination(10, TimeUnit.SECONDS);
		
		
		// Printing the summary of how many strings each consumer consumed respectively, as well as the amount
		// of strings created by the producers respectively ... sorry in advance about the number of comments, 
		// I made them so I could ask people for help easier.
		System.out.println("Summary:\n");
		System.out.println("Producer 1 produces: " + producer1.getProducedAmount() + " events.\n");
		System.out.println("Producer 2 produces: " + producer2.getProducedAmount() + " events.\n");
		System.out.println("Producer 3 produces: " + producer3.getProducedAmount() + " events.\n");
		System.out.println("Consumer 1 consumes: " + consumer1.getConsumedAmount() + " events.\n");
		System.out.println("Consumer 2 consumes: " + consumer2.getConsumedAmount() + " events.\n");
		System.out.println("Consumer 3 consumes: " + consumer3.getConsumedAmount() + " events.\n");
		System.out.println("Consumer 4 consumes: " + consumer4.getConsumedAmount() + " events.\n");
		System.exit(0); // Automatically quit after printing the summary
	}
	
}

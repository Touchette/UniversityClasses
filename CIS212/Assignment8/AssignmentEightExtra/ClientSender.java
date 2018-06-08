import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.concurrent.ThreadLocalRandom;

public class ClientSender implements Runnable {
	
	private Socket socket;
	private ArrayList<Integer> receivedList;
	private static ArrayList<Integer> generatedList = new ArrayList<Integer>();
    private final Object pauseLock = new Object();
    public volatile static boolean running = true;
    public volatile static boolean paused = true;

	
	ClientSender(Socket givenSocket) {
		this.socket = givenSocket;
	}
	
	@SuppressWarnings("unchecked")
	@Override
	public void run () {
		try {
			// Create the objects that will push the list to the server
			ObjectOutputStream objectOutput = new ObjectOutputStream(socket.getOutputStream());
	        while (running){
	            synchronized (pauseLock) {
	                if (!running) { 
	                    break;
	                }
	                if (paused) {
	                    try {
	                        pauseLock.wait();
	                    } catch (InterruptedException ex) {
	                        System.out.println("Interrupted Exception");
	                    	break;
	                    }
	                    if (!running) {
	                        break;
	                    }
	                }
	            }
	    			// Check if running, and if paused
					while (running & !paused) {
						
						// Write the generated list to the server
						generateList();
						objectOutput.writeObject(generatedList);
						objectOutput.flush();
						objectOutput.reset();
						System.out.println("Sent: " + generatedList);
						generatedList.clear();
						
						// Grab the list that the server gives back and print out its content, then sleep
						ObjectInputStream objectInput = new ObjectInputStream(socket.getInputStream());
						Object givenObject = objectInput.readObject();
						receivedList = (ArrayList<Integer>) givenObject;
						System.out.println("Received: " + receivedList);
						Thread.sleep(3000);
					}
	    		}
        } catch (Exception e) {
        	e.printStackTrace();
        }
	}

	// Stops the thread from running at all
    public void stop() {
        running = false;
        resume();
    }

    // Used to pause the function
    public void pause() {
        paused = true;
    }
    
    // Used to unpause the function
    public void resume() {
        synchronized (pauseLock) {
            paused = false;
            pauseLock.notify(); 
        }
    }
   
	// Generates the random list of integers to be sent to the server
	public static void generateList() {
		for (int i=0;i<5;i++) {
			generatedList.add(ThreadLocalRandom.current().nextInt(2, 100));
		}
	}
}

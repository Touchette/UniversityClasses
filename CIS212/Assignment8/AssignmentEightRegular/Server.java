import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;


public class Server {
	
	// ArrayLists that will store what the client passes to this server as well
	// as what will be sent back out to the client
	static ArrayList<Integer> givenInts = new ArrayList<Integer>();
	static ArrayList<Integer> primes = new ArrayList<Integer>();

	@SuppressWarnings("unchecked")
	public static void main (String args[]) throws IOException, ClassNotFoundException {
		
		// Start the server on port 10001
		ServerSocket serverSocket = new ServerSocket(10001);
		
		System.out.println("Waiting on input from client.");
		// Wait for a client to be found
		Socket socket = serverSocket.accept();
		
		// Get the list of integers from the client and store them in an ArrayList
		ObjectInputStream objectInput = new ObjectInputStream(socket.getInputStream());
		Object givenObject = objectInput.readObject();
		givenInts = (ArrayList<Integer>) givenObject;
		
		
		// Check the given integers for primes using the isPrime function
		for (int i=0;i<givenInts.size();i++) {
			if (isPrime(givenInts.get(i))) {
				primes.add(givenInts.get(i));
			}
		}
		
		// Output the list of primes and close the socket
		ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());
		output.writeObject(primes);
		
		// Close the server
		serverSocket.close();
	}
	
	static boolean isPrime(int givenInt) {
		// Checking 2 separately because 2 is the only even prime number
		if (givenInt == 2) {
			return true;
		}
		
	    // Check if the given integer is a multiple of 2, not a prime if so.
		// Can also check if the given integer is 1, because 1 isn't a prime
	    if (givenInt % 2 == 0 || givenInt == 1) {
	    	return false;
	    }

	    // If not a multiple of 2, then just check the odd numbers up to sqrt(givenInt)
	    for(int i=3;i*i<=givenInt;i+=2) {
	        if(givenInt % i == 0)
	            return false;
	    }
	    return true;
	}
	
}

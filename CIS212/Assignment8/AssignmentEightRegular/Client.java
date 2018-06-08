import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Scanner;


public class Client {
	// ArrayLists that will be used to store the ints the user inputs as well as what is returned
	// by the server
	static ArrayList<Integer> givenInts = new ArrayList<Integer>();
	static ArrayList<Integer> receivedList = new ArrayList<Integer>();

	@SuppressWarnings("unchecked")
	public static void main (String args[]) throws UnknownHostException, IOException, ClassNotFoundException {

		// Boolean to check if the scanner is still accepting integers
		boolean acceptingints = true;
		
		// Scanner that will read user input to form the list of integers that will be passed to the server
		Scanner scanner = new Scanner(System.in);
		// Create the client object on the same port as the server, 10001
		Socket socket = new Socket("localhost", 10001);
		
		System.out.println("Enter an integer ('!' to send):");
		// The loop that will take user inputed integers and pass them into the ArrayList,
		// will exit upon typing "!"
		do{
		    if(scanner.hasNextInt()){
		    	//  Add the integer to the ArrayList that will be sent to the server
		    	givenInts.add(scanner.nextInt());
		    	System.out.println("Enter an integer ('!' to send):");
		    	} else if (scanner.hasNextLine()) {
		    		// Quit the scanner if the user inputs "!"
		    		if (scanner.nextLine().startsWith("!")) {
		    			acceptingints = false;
		    			scanner.close();
		    	    }
		        }
		   } while(acceptingints);

		System.out.println("Sent: " + givenInts);

		
		// Create the object output that will push the list to the port that is connected to,
		// in this case it is pushing the ArrayList of user-inputed integers to the sever on port 10001
		ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());
		output.writeObject(givenInts);

		// Create the object input that will read the object that the server outputs, in this case
		// it will simply grab the list that the server creates which contains only the primes
		// from the list sent to the server
		ObjectInputStream objectInput = new ObjectInputStream(socket.getInputStream());
		Object givenObject = objectInput.readObject();
		receivedList = (ArrayList<Integer>) givenObject;
		
		// Print that list that the client received
		System.out.println("Received: " + receivedList);
		
		// Close the client
		socket.close();
	}

}

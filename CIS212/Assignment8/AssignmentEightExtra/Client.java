import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;


public class Client {

	private static boolean acceptingInput = true;
	
	public static void main (String args[]) throws UnknownHostException, IOException {
		
		// Scanner that will read user input to form the list of integers that will be passed to the server
		Scanner scanner = new Scanner(System.in);
		// Create the client object on the same port as the server, 10001
		Socket clientSocket = new Socket("localhost", 10001);
		// Sender object that actually sends and receives objects
		ClientSender sender = new ClientSender(clientSocket);
		new Thread(sender).start();
		
		System.out.println("Enter '!' to start and stop, '#' to quit:");
		/* The loop that will take user inputed integers and pass them into the ArrayList,
		   will exit upon typing "!" */
		while(acceptingInput) {
			if (scanner.hasNext()) {
				String input = scanner.nextLine();
				
				if(input.startsWith("!")) {
					if (ClientSender.paused) {
						sender.resume();
					}
					else {
						sender.pause();
						System.out.println("Enter '!' to start and stop, '#' to quit:");
					}
				}
				else if(input.startsWith("#")) {
					scanner.close();
					clientSocket.close();
					System.exit(0);
					}
				}
			}
		}
}
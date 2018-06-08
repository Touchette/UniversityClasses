import java.util.Scanner;

public class IntegerScanner {
	public static void main(String[] args) {
        int sum = 0;
        int num;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a positive integer (-3 to print, -2 to reset, -1 to quit):");
        
        while ((num = scanner.nextInt()) != -1) {
            if (num == -3) {
        	System.out.println("Sum: " + sum);
            }
            if (num == -2) {
        	sum = 0;
        	System.out.println("Enter a positive integer (-3 to print, -2 to reset, -1 to quit):");
            }
            if (num == -1) {
        	System.out.println("Sum: " + sum);
        	Scanner.close();
        	System.exit(0);
            }
            if (num < 0) {
        	sum += 0;
            }
            else {
        		sum += num;
            }
        }
    }
}

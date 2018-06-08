import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.*;

public class fileReader {
	
	public static void main(String[] args) throws Exception {
		
		FileReader file = new FileReader((System.getProperty("user.dir") + "/phonebook_test.txt")); // This will get the working directory where the program is started
		BufferedReader reader = new BufferedReader(file);
		
		ArrayList<phonebookEntry> entries = new ArrayList<>();
		
		String line = reader.readLine();

		while (line != null) {
			String[] splitLine = line.split(" ");
			phonebookEntry newEntry = new phonebookEntry(splitLine[0], splitLine[1], splitLine[2]);
			entries.add(newEntry);
			line = reader.readLine();
		}
		reader.close();
		// This method call will output the file containing names with the keyword "new" in them, change the second parameter to change keyword.
		entryContainsString(entries, "new");
		/* 
		 * These three calls will check if the lists are sorted. The first call will return false and print "Not sorted." as it is checking the unsorted list,
		 * the next two will return true and print "Sorted." as they run with the respective sort methods.
		 */
		testIfSorted(entries);
		testIfSorted(selectionSortEntries(entries));
		testIfSorted(mergeSortEntries(entries));
		/* 
		 * This method call will test the time it takes for each version of the sort method to complete. As the previous two method calls also
		 * called for the sort methods, this main method ends up taking a long time to run. Patience is key... can comment them out
		 * at user discretion to reduce run time of main method.
		 */
		testSortTimes(entries);
	}

	public static void entryContainsString(ArrayList<phonebookEntry> entrylist, String string) throws FileNotFoundException, UnsupportedEncodingException {
		
		PrintWriter writer = new PrintWriter((System.getProperty("user.dir") + "/contains_string_output.txt"), "UTF-8"); // This will get the working directory where the program is started

		for (int i=0; i<entrylist.size(); i++) {
			if (entrylist.get(i).getName().contains(string)) {
				writer.println(entrylist.get(i).getInfo());
			}
		}
		writer.close();
	}
	
	public static ArrayList<phonebookEntry> selectionSortEntries(ArrayList<phonebookEntry> a) {
		int smallestIndex;
		String smallest;
		
		for (int curIndex=0; curIndex<a.size()-1; curIndex++) {
	
			smallest = a.get(curIndex).getLastName();
			smallestIndex = curIndex;
	
			for (int i=curIndex+1; i<a.size(); i++) {
				if (smallest.compareTo(a.get(i).getLastName()) > 0) {
					smallest = a.get(i).getLastName();
					smallestIndex = i;
				}
			}
			if (smallestIndex == curIndex) {;}
			else {
				phonebookEntry temp = a.get(curIndex);
				a.set(curIndex, a.get(smallestIndex));
				a.set(smallestIndex, temp);
			}
		}
		return a;
	}
	
	public static ArrayList<phonebookEntry> mergeSortEntries(ArrayList<phonebookEntry> a) {
		int arraySize = a.size();
		
		if (arraySize<=1) {
			return a;
		} 
		else {
			ArrayList<phonebookEntry> leftArray = new ArrayList<phonebookEntry>();
			ArrayList<phonebookEntry> rightArray = new ArrayList<phonebookEntry>();
			int arrayMiddle = arraySize/2;
			
			for (int i=0; i<arrayMiddle; i++) {
				leftArray.add(a.get(i));
			}
			for (int i=arrayMiddle; i<arraySize; i++) {
				rightArray.add(a.get(i));			
			}
			return mergeSort(mergeSortEntries(leftArray), mergeSortEntries(rightArray));
		}
	}

	// method used by mergeSortEntries to actually do the sorting
	public static ArrayList<phonebookEntry> mergeSort(ArrayList<phonebookEntry> leftArray, ArrayList<phonebookEntry> rightArray) { 
		ArrayList<phonebookEntry> returnedArray = new ArrayList<phonebookEntry>();
		int leftIndex = 0, rightIndex = 0;
		
		while(leftIndex+1 <= leftArray.size() || rightIndex+1 <= rightArray.size()) { 
			
			if(leftIndex+1 <= leftArray.size() && rightIndex+1 <= rightArray.size()) {
				if(leftArray.get(leftIndex).getLastName().compareTo(rightArray.get(rightIndex).getLastName()) <= 0.0) { 
					returnedArray.add(leftArray.get(leftIndex));
					leftIndex++;
				} else { 
					returnedArray.add(rightArray.get(rightIndex));
					rightIndex++;
				}
				
			} else if(leftIndex+1 <= leftArray.size()) { 
				returnedArray.add(leftArray.get(leftIndex));
				leftIndex++;
				
			} else if(rightIndex+1 <= rightArray.size()) { 
				returnedArray.add(rightArray.get(rightIndex));
				rightIndex++;
			}
		}
		return returnedArray;	
	}
	
	public static boolean testIfSorted(ArrayList<phonebookEntry> a) {
		for (int i=1; i<a.size(); i++) {
			if (a.get(i-1).getLastName().compareTo(a.get(i).getLastName()) > 0) {
				System.out.println("Not sorted.");
				return false;
			}
		}
		System.out.println("Sorted.");
		return true;
	}
	
	public static void testSortTimes(ArrayList<phonebookEntry> a) throws FileNotFoundException, UnsupportedEncodingException {
		long selectionStart = System.currentTimeMillis();
		selectionSortEntries(a);
		long selectionTimeMillis = System.currentTimeMillis()-selectionStart;
		System.out.println("Selection Sort: " + selectionTimeMillis/1000F);
		
		long mergeStart = System.currentTimeMillis();
		mergeSortEntries(a);
		long mergeTimeMillis = System.currentTimeMillis()-mergeStart;
		System.out.println("Merge Sort: " + mergeTimeMillis/1000F);
	}
}
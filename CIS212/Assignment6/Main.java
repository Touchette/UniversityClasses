import java.util.*;

public class Main {

	public static void main(String args[]) {
		OccurrenceSet<Integer> intSet = new OccurrenceSet<Integer>();
		intSet.add(1);intSet.add(3);intSet.add(5);intSet.add(5);intSet.add(3);intSet.add(3);intSet.add(3);
		System.out.println("Sorted Integer Set: " + "\n" + intSet + "\n");
		
		OccurrenceSet<String> stringSet = new OccurrenceSet<String>();
		stringSet.add("hello");stringSet.add("hello");stringSet.add("world");stringSet.add("world");stringSet.add("world");stringSet.add("here");
		System.out.println("Sorted String Set: " + "\n" + stringSet + "\n");
		
		System.out.println("Does String Set Contain 'hello'?: " + "\n");
		System.out.println((stringSet.contains("hello") ? "Yes" : "No") + ". \n");
		System.out.println("Does String Set Contain 'goodbye'?: " + "\n");
		System.out.println((stringSet.contains("goodbye") ? "Yes" : "No") + ". \n");
		
		stringSet.clear();
		System.out.println("String Set After Being Cleared: " + "\n" + stringSet + "\n");
		
		stringSet.add("hello");stringSet.add("hello");stringSet.add("world");stringSet.add("world");stringSet.add("world");stringSet.add("here");
		stringSet.remove("hello");
		System.out.println("String Set After Removing Hello: " + "\n" + stringSet + "\n");
		stringSet.clear();
		
		stringSet.add("hello");stringSet.add("hello");stringSet.add("world");stringSet.add("world");stringSet.add("world");stringSet.add("here");
		Collection<String> t = new ArrayList<String>(2);
		t.add("world");
		stringSet.retainAll(t);
		System.out.println("String Set Retaining Only World: " + "\n" + stringSet + "\n");
		stringSet.clear();
		
		stringSet.add("hello");stringSet.add("hello");stringSet.add("world");stringSet.add("world");stringSet.add("world");stringSet.add("here");
		System.out.println("String Set Iterator: " + "\n" + stringSet.iterator() + "\n");
		System.out.println("String Set Array: " + "\n" + stringSet.toArray() + "\n");
	}
	
}
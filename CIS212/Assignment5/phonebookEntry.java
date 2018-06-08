
public class phonebookEntry implements Comparable<phonebookEntry> {
	private String phoneNumber = "";
	private String fullName = "";
	private String lastName = "";
	
	public phonebookEntry(String number, String last, String first) {
		phoneNumber = number;
		// String lastNoComma = last.substring(0, last.length() - 1);
		lastName = last;
		fullName = last + " " + first;
	}
	
	public String getName() {
		return fullName;
	}
	
	public String getNumber() {
		return phoneNumber;
	}
	
	public String getLastName() {
		return lastName;
	}
	
	public String getInfo() {
		return (phoneNumber + " " + fullName);
	}
	
	@Override
	public int compareTo(phonebookEntry other) {
		return lastName.compareTo(other.lastName);
	}
}

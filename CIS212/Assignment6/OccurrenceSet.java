import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class OccurrenceSet<T> implements Set<T> {

	private HashMap<T, Integer> hashmap = new HashMap<T, Integer>();
	
	@Override
	public boolean add(T t) {
		hashmap.put(t, hashmap.getOrDefault(t, 0) + 1);
		return true;
	}

	@Override
	public boolean addAll(Collection<? extends T> t) {
		Iterator<? extends T> collectionIt = t.iterator();
		while (collectionIt.hasNext()) {
			T obj = collectionIt.next();
			hashmap.put(obj, hashmap.getOrDefault(obj, 0) + 1);
		}
		return true;
	}

	@Override
	public void clear() {
		hashmap.clear();
	}

	@Override
	public boolean contains(Object t) {
		if (hashmap.containsKey(t)) {
			return true;
		}
		return false;
	}

	@Override
	public boolean containsAll(Collection<?> t) {
		Iterator<?> collectionIt = t.iterator();
		while (collectionIt.hasNext()) {
			Object obj = collectionIt.next();
			if (!hashmap.containsKey(obj)) {
				return false;
			}
		}
		return true;
	}

	@Override
	public boolean isEmpty() {
		if (hashmap.isEmpty()) {
			return true;
		}
		return false;
	}

	@Override
	public boolean remove(Object t) {
		if (hashmap.containsKey(t)) {
			hashmap.remove(t);
			return true;
		}
		return false;
	}

	@Override
	public boolean removeAll(Collection<?> t) {
		Iterator<?> collectionIt = t.iterator();
		while (collectionIt.hasNext()) {
			Object obj = collectionIt.next();
			if (hashmap.containsKey(obj)) {
				hashmap.remove(obj);
			}
		}
		return true;
	}

	@Override
	public boolean retainAll(Collection<?> t) {
		hashmap.keySet().retainAll(t);
		return true;
	}

	@Override
	public int size() {
		return hashmap.size();
	}
	
	@Override
	public <T> T[] toArray(T[] t) {
		return sortByValue(hashmap).keySet().toArray(t);
	}
	
	@Override
	public Object[] toArray() {
		return sortByValue(hashmap).keySet().toArray();
	}
	
	@Override
	public Iterator<T> iterator() {
		return sortByValue(hashmap).keySet().iterator();
	}
	
	@Override
	public String toString() {
		return sortByValue(hashmap).keySet().toString();
	}

	public <T, Integer extends Comparable<? super Integer>> Map<T, Integer> sortByValue(Map<T, Integer> passedMap) {
		// List that will be sorted
		List<Map.Entry<T, Integer>> list = new LinkedList<Map.Entry<T, Integer>>(passedMap.entrySet());
		
		// Comparator for sorting the list
    	Collections.sort(list, new Comparator<Map.Entry<T, Integer>>() {
    		public int compare(Map.Entry<T, Integer> o1, Map.Entry<T, Integer> o2) {
            	return (o1.getValue()).compareTo(o2.getValue());
        	}
    	});
    	
    	// Recreate the map as a sorted one
    	Map<T, Integer> sortedMap = new HashMap<T, Integer>();
    	for (Map.Entry<T, Integer> entry : list) {
        	sortedMap.put(entry.getKey(), entry.getValue());
    	}
    	return sortedMap;
	}

}

import java.util.Scanner;
import java.util.ArrayList;
import java.util.Random;

public class ArrayTesting {
	
	public static void main(String[] args) {
	    System.out.println("Please input the array length:");
	    Scanner scan = new Scanner(System.in);
	    int arrayLength = scan.nextInt();

	    System.out.println("Please input the array density:");
	    Scanner scann = new Scanner(System.in);
	    boolean withinRange = false;
	    double arrayDensity = 0;
	    while (!withinRange) {
			double next = scann.nextDouble();
			if (next > 0.0 && next < 1.0) {
				withinRange = true;
				scann.close();
			}
			else {
				withinRange = false;
				System.out.println("Please enter a density value between 0.0 and 1.0");
			}
			arrayDensity = next;
		}
	    createDenseArray(arrayLength, arrayDensity);
	    createSparseArray(arrayLength, arrayDensity);
	    convertDenseArray(createDenseArray(arrayLength, arrayDensity));
	    convertSparseArray(createSparseArray(arrayLength, arrayDensity), arrayLength);
	    denseArrayMaximum(createDenseArray(arrayLength, arrayDensity));
	    sparseArrayMaximum(createSparseArray(arrayLength, arrayDensity));
		}

		public static int[] createDenseArray(int arrayLength, double arrayDensity) {
			double cdaStartTime = System.nanoTime();
			int[] denseArray = new int[arrayLength];
			Random rng = new Random();
			for (int i=0; i<arrayLength; i++) {
				double randomD = rng.nextDouble();
				int randomI = rng.nextInt(1000000);
				if (randomD > arrayDensity) {
					denseArray[i] = 0;
				}
				else {
					denseArray[i] = randomI;
				}
			}
			double cdaEndTime = System.nanoTime();
			double cdaTotalTime = cdaEndTime - cdaStartTime;
			System.out.println("Create dense array length: " + arrayLength + " Time: " + (cdaTotalTime / 1000));
			return denseArray;
		}

		public static ArrayList<Integer[]> createSparseArray(int arrayLength, double arrayDensity) {
			double csaStartTime = System.nanoTime();
			ArrayList<Integer[]> sparseArray = new ArrayList<Integer[]>();
			Random rngesus = new Random();
			for (int i=0; i<arrayLength; i++) {
				double randomDD = rngesus.nextDouble();
				int randomII = rngesus.nextInt(1000000);
				if (randomDD > arrayDensity) {}
				else {
					Integer[] array = new Integer[2];
					array[0] = i; array[1] = randomII;
					sparseArray.add(array);
				}
			}
			double csaEndTime = System.nanoTime();
			double csaTotalTime = csaEndTime - csaStartTime;
			System.out.println("Create sparse array length: " + arrayLength + " Time: " + (csaTotalTime / 1000));
			return sparseArray;
		}

		public static ArrayList<Integer[]> convertDenseArray(int[] denseArray){
			double condaStartTime = System.nanoTime();
			ArrayList<Integer[]> convertedSparseArray = new ArrayList<Integer[]>();
			int length = denseArray.length;
			for (int i=0; i<length; i++) {
				if (denseArray[i] != 0) {
					Integer[] aux = new Integer[2];
					aux[0] = i; aux[1] = denseArray[i];
					convertedSparseArray.add(aux);
				}
				else {}
			}
			double condaEndTime = System.nanoTime();
			double condaTotalTime = condaEndTime - condaStartTime;
			System.out.println("Convert to sparse length: " + convertedSparseArray.size() + " Time: " + (condaTotalTime / 1000));
			return convertedSparseArray;
		}

		public static int[] convertSparseArray(ArrayList<Integer[]> sparseArray, int convertedArrayLength) {
			double consaStartTime = System.nanoTime();
			int[] convertedDenseArray = new int[convertedArrayLength];
			for (int i=0; i<sparseArray.size(); i++) {
				int tempIndex = sparseArray.get(i)[0];
				convertedDenseArray[tempIndex] = sparseArray.get(i)[1];
			}
			double consaEndTime = System.nanoTime();
			double consaTotalTime = consaEndTime - consaStartTime;
			System.out.println("Convert to dense array length: " + convertedDenseArray.length + " Time: " + (consaTotalTime / 1000));
			return convertedDenseArray;
		}

		public static void denseArrayMaximum(int[] denseArray) {
			double damStartTime = System.nanoTime();
			int denseCurrentMax = 0;
			int denseCurrentMaxIndex = 0;
			for (int i=0; i<denseArray.length; i++) {
				if (denseArray[i] > denseCurrentMax) {
					denseCurrentMax = denseArray[i];
					denseCurrentMaxIndex = i;
				}
			}
			double damEndTime = System.nanoTime();
			double damTotalTime = damEndTime - damStartTime;
			System.out.println("The current max is " + denseCurrentMax + ", its index is " + denseCurrentMaxIndex + ". Time for dense max: " + (damTotalTime / 1000));
		}

		public static void sparseArrayMaximum(ArrayList<Integer[]> sparseArray) {
			double samStartTime = System.nanoTime();
			int sparseCurrentMax = 0;
			int sparseCurrentMaxIndex = 0;
			for (int i=0; i<sparseArray.size(); i++) {
				if (sparseArray.get(i)[1] > sparseCurrentMax) {
					sparseCurrentMax = sparseArray.get(i)[1];
					sparseCurrentMaxIndex = sparseArray.get(i)[0];
				}
			}
			double samEndTime = System.nanoTime();
			double samTotalTime = samEndTime - samStartTime;
			System.out.println("The current max is " + sparseCurrentMax + ", its index is " + sparseCurrentMaxIndex + ". Time for sparse max: " + (samTotalTime / 1000));
		}	
	}
}

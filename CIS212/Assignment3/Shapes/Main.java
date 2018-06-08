import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;

public class Main {
	private static double nextDouble() {
		double random = ThreadLocalRandom.current().nextDouble(Double.MIN_VALUE, 1.0);
		return random;
	}

	private static double calculateSum(ArrayList<Measurable> arrayList) {
		double sum = 0;
		for(int i=0; i<arrayList.size(); i++) {
			Measurable currentItem = arrayList.get(i);
			sum += currentItem.getArea();
		}
		return sum;
	}

	public static void main(String[] args) {
		Random rng = new Random();
		
		int rectCounter = 0;
		int boxCounter = 0;
		int circleCounter = 0;
		int sphereCounter = 0;
		
		ArrayList<Measurable> areaArrayList = new ArrayList<Measurable>();
		for (int i=0; i<1000; i++) {
			double rngesus = rng.nextDouble();

			if (rngesus < .25) {
				Rectangle rectangle = new Rectangle(nextDouble(), nextDouble());
				areaArrayList.add(rectangle);
				rectCounter += 1;
			}
			if (rngesus > .25 && rngesus < .50) {
				Box box = new Box(nextDouble(), nextDouble(), nextDouble());
				areaArrayList.add(box);
				boxCounter += 1;
			}
			if (rngesus > .50 && rngesus < .75) {
				Circle circle = new Circle(nextDouble());
				areaArrayList.add(circle);
				circleCounter += 1;
			}
			if (rngesus > .75) {
				Sphere sphere = new Sphere(nextDouble());
				areaArrayList.add(sphere);
				sphereCounter += 1;
			}
		}
		System.out.println("rects: "+rectCounter+" boxes: "+boxCounter+ " circles: "+circleCounter+" spheres: "+sphereCounter+System.lineSeparator()+"sum: "+calculateSum(areaArrayList));
	}
}

public class Circle implements Measurable {
	static double radius = 0;
	
	public Circle(double startRadius) {
		radius = startRadius;
	}
	public double getArea() {
		return Math.PI * Math.pow(radius, 2);
	}
}


public class Sphere extends Circle{
	static double radius = 0;
	
	public Sphere(double startRadius) {
		super(startRadius);
	}
	
	public double getArea() {
		return (4 * Math.PI * Math.pow(radius, 2));
	}
}

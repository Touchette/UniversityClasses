
public class Rectangle implements Measurable {
	static double width = 0;
	static double height = 0;

	public Rectangle(double startWidth, double startHeight) {
		width = startWidth;
		height = startHeight;
	}

	public double getArea() {
		return width * height;
	}
}

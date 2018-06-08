
public class Box extends Rectangle {
	static double width = 0;
	static double height = 0;
	static double length = 0;
	
	public Box(double startWidth, double startHeight, double startLength) {
		super(startWidth, startHeight);
		width = startWidth;
		height = startHeight;
		length = startLength;
	}
	
	public double getArea() {
		return (2*(height * width) + 2*(height * length) + 2*(width * length));
	}
}

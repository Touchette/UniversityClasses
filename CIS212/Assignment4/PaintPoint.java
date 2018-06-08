import java.awt.Graphics;
import java.awt.Color;

public class PaintPoint {
	public static final int smallCursorSize = 10;
	public static final int mediumCursorSize = 20;
	public static final int largeCursorSize = 30;
	public Color cursorColor;
	
	private final int cursorx;
	private final int cursory;
	private final int cursorSize;
	
	public PaintPoint(int x, int y, int size, Color color) {
		cursorx = x;
		cursory = y;
		cursorSize = size;
		cursorColor = color;
	}
	
	public int getX() {
		return cursorx;
	}

	public int getY() {
		return cursory;
	}

	public int getSize() {
		return cursorSize;
	}

	public Color getColor() {
		return cursorColor;
	}

	public void draw(Graphics template) {
		template.setColor(cursorColor);
		template.fillOval(cursorx, cursory, cursorSize, cursorSize);
	}
}
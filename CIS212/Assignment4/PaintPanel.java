import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import javax.swing.JPanel;

public class PaintPanel extends JPanel {
	public ArrayList<PaintPoint> drawnPoints;
	
	private Color brushColor;
	private int cursorSize;
	
	public PaintPanel() {
		drawnPoints = new ArrayList<>();
		brushColor = Color.BLACK;
		cursorSize = PaintPoint.smallCursorSize;
		
		MouseAdapter adapter = new MouseAdapter() {
			@Override
		    public void mouseDragged(MouseEvent e) {
				PaintPoint point = new PaintPoint(e.getX(), e.getY(), cursorSize, brushColor);
				drawnPoints.add(point);
				repaint();
			}
		};
		
		addMouseListener(adapter);
		addMouseMotionListener(adapter);
	}

	@Override
	public void paintComponent(Graphics template) {
		super.paintComponent(template);
		template.setColor(brushColor);
		for (PaintPoint point : drawnPoints) {
			point.draw(template);
		}
	}
	
	public void setBrushColor(Color color) {
		brushColor = color;
		repaint();
	}
	public void setSize(int size) {
		cursorSize = size;
	}
}
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class MainFrame extends JFrame {
	private final PaintPanel paintTemplate;
	
	public MainFrame() {
		super("Paint");
		setLayout(new BorderLayout());
		
		paintTemplate = new PaintPanel();
		paintTemplate.setPreferredSize(new Dimension(650, 450));
		add(paintTemplate, BorderLayout.CENTER);
		
		JButton largeSizeButton = new JButton("Large");
		largeSizeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paintTemplate.setSize(PaintPoint.largeCursorSize);			
			}			
		});
		
		JButton mediumSizeButton = new JButton("Medium");
		mediumSizeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paintTemplate.setSize(PaintPoint.mediumCursorSize);			
			}			
		});
		
		JButton smallSizeButton = new JButton("Small");
		smallSizeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paintTemplate.setSize(PaintPoint.smallCursorSize);
			}
		});
		JButton clearButton = new JButton("Clear");
		clearButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paintTemplate.drawnPoints.clear();
				repaint();
			}
		});
		
		JButton blackButton = new JButton("Black");
		blackButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paintTemplate.setBrushColor(Color.BLACK);
			}
		});
		JButton greenButton = new JButton("Green");
		greenButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paintTemplate.setBrushColor(Color.GREEN);
			}
		});
		JButton yellowButton = new JButton("Yellow");
		yellowButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paintTemplate.setBrushColor(Color.YELLOW);
			}
		});
		JButton grayButton = new JButton("Gray");
		grayButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paintTemplate.setBrushColor(Color.GRAY);
			}
		});
		
		JPanel colorsPanel = new JPanel(new GridLayout(4, 1));
		colorsPanel.add(blackButton);
		colorsPanel.add(greenButton);
		colorsPanel.add(yellowButton);
		colorsPanel.add(grayButton);
		
		JPanel sizesPanel = new JPanel(new GridLayout(4, 1));
		sizesPanel.add(smallSizeButton);
		sizesPanel.add(mediumSizeButton);
		sizesPanel.add(largeSizeButton);
		sizesPanel.add(clearButton);
		
		add(colorsPanel, BorderLayout.WEST);
		add(sizesPanel, BorderLayout.EAST);
	}
}
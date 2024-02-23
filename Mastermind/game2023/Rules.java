import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;

import javax.swing.JFrame;

public class Rules  extends JFrame
{
    private Font header = new Font("Courier", Font.PLAIN, 50);
    private Font paragraph = new Font("Courier", Font.PLAIN, 24);
    public static void main (String[] args)
    {
        System.out.println("Opening rules window");
        Rules guiWindow = new Rules();
        guiWindow.setVisible(true);
    }
    
    public Rules()
    {
        setSize(1000, 1000);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setBackground(new Color( 192, 192, 192 ));
    }

    public void paint(Graphics canvas)
    {
        canvas.setFont(header);
        canvas.drawString("Mastermind Rules",30,100);
        canvas.setFont(paragraph);
        canvas.drawString("Mastermind Rules",30,150);
    }
}

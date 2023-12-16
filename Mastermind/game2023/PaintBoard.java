import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import java.util.HashMap;

import javax.swing.JFrame;

public class PaintBoard extends JFrame implements MouseListener
{
  public HashMap<String, Color> color = new HashMap<String, Color>();
  private int length = 0; //The length of the pattern
  private int[][] guess; //Saves the guesses from each of the rounds
  private int[][] clue; //Saves the clues given each round
  private int x = 50;
  private int y = 100;
  
  public static void main (String[] args)//for testing purposes
  {
    PaintBoard guiWindow = new PaintBoard(4);
    guiWindow.setVisible(true);
  }
  /* ******************************************************************************************
   * @description: The constructor initializes the boards to store the guesses given and clues 
   *               recived as well as storing the length of the pattern that needs to be guessed.
   *     
   * @parameter: Len is an integer containing the length of the pattern to be guessed.  
   *     
   * @return: none
   ***************************************************************************************** */
  public PaintBoard(int len)
  {
    addMouseListener(this);
    initializeColors(3);
    //sets up the frame
    setSize(len*len*40,len*100);
    setDefaultCloseOperation(EXIT_ON_CLOSE);
    setBackground(new Color( 192, 192, 192 ));
    //initilizes other variables that are needed for the program
    guess = new int[len*len][len];
    clue = new int[len*len][len];
    length = len;
    System.out.println(guess.toString());
    System.out.println(clue.toString());
    System.out.println(length);
  }//end constructor

  private void initializeColors(int mode)
  {
    color.put("aqua", new Color( 0, 255, 255 ));
    color.put("aqua", new Color( 0, 255, 255 ));
    color.put("chartreuse", new Color( 127, 255, 0 ));
    color.put("crimson", new Color( 220, 20, 60 ));
    color.put("deepskyblue", new Color( 0, 191, 255 ));
    color.put("indigo", new Color( 75, 0, 130 ));
    color.put("mediumorchid", new Color( 186, 85, 211 ));
    color.put("mediumseagreen", new Color( 60, 179, 113 ));
    color.put("orange", new Color( 255, 165, 0 ));
    color.put("orangered", new Color( 255, 69, 0 ));
    color.put("silver", new Color( 192, 192, 192 ));
    color.put("teal", new Color( 0, 128, 128 ));
    color.put("gray", new Color (150,150,150));
    System.out.println(color.keySet());
    
  }
 
    @Override
    public void mouseClicked(MouseEvent e) {
        int x = e.getX();
        int y = e.getY();
        System.out.println("Mouse Clicked at X: " + x + " - Y: " + y);
    }
 
    @Override
    public void mouseEntered(MouseEvent e) {
        System.out.println("Resume Game");
    }
 
    @Override
    public void mouseExited(MouseEvent e) {
        System.out.println("Pause Game");
    }
 
    @Override
    public void mousePressed(MouseEvent e) {
        int x = e.getX();
        int y = e.getY();
        System.out.println("Mouse Pressed at X: " + x + " - Y: " + y);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        int x = e.getX();
        int y = e.getY();
        System.out.println("Mouse Released at X: " + x + " - Y: " + y);
    }

  public void paint(Graphics canvas)
  {
    canvas.drawString("guesses",length*30,50);
    canvas.drawString("clues",length*100,50);
    //set-up boards
    canvas.setColor(color.get("gray"));
    for(int col = 0; col < length*length; col++)
    {
      for (int row = 0; row < length; row++)
      {
        canvas.fillOval(x,y,40,40);
        x = x + 50;
      }
      x = length*80;
      for (int row = 0; row < length; row++)
      {
        canvas.fillOval(x,y,40,40);
        x = x + 50;
      }
      x = 50;
      y = y + 50;
    }
    // canvas.setColor(color.get("aqua"));
    // canvas.fillOval(0, 50, 50, 50);
    // canvas.setColor(color.get("deepskyblue"));
    // canvas.fillOval(50, 50, 50, 50);
    // canvas.setColor(color.get("chartreuse"));
    // canvas.fillOval(100, 50, 50, 50);
    // canvas.setColor(color.get("mediumorchid"));
    // canvas.fillOval(0, 100, 50, 50);
    // canvas.setColor(color.get("orange"));
    // canvas.fillOval(50, 100, 50, 50);
    // canvas.setColor(color.get("orangered"));
    // canvas.fillOval(100, 100, 50, 50);
    // canvas.setColor(color.get("mediumseagreen"));
    // canvas.fillOval(0, 150, 50, 50);
    // canvas.setColor(color.get("crimson"));
    // canvas.fillOval(50, 150, 50, 50);
    // canvas.setColor(color.get("indigo"));
    // canvas.fillOval(100, 150, 50, 50);
    // canvas.setColor(color.get("silver"));
    // canvas.fillOval(0, 200, 50, 50);
    // canvas.setColor(color.get("teal"));
    // canvas.fillOval(50, 200, 50, 50);
    // canvas.setColor(color.get("gray"));
    // canvas.fillOval(100, 200, 50, 50);
    }
}

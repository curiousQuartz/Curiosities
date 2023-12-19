import javax.swing.JFrame;
import java.awt.Graphics;
import java.awt.Color;

public class PaintBoard extends JFrame
{
  private Color aqua = new Color( 0, 255, 255 );
  private Color chartreuse = new Color( 127, 255, 0 );
  private Color crimson = new Color( 220, 20, 60 );
  private Color deepskyblue = new Color( 0, 191, 255 );
  private Color indigo = new Color( 75, 0, 130 );
  private Color mediumorchid = new Color( 186, 85, 211 );
  private Color mediumseagreen = new Color( 60, 179, 113 );
  private Color orange = new Color( 255, 165, 0 );
  private Color orangered = new Color( 255, 69, 0 );
  private Color silver = new Color( 192, 192, 192 );
  private Color teal = new Color( 0, 128, 128 );
  private Color gray = new Color (150,150,150);
  private int length = 0; //The length of the pattern
  private String[] colors; //The color options the user has inputed to guess from
  private int[][] guess; //Saves the guesses from each of the rounds
  private int[][] clue; //Saves the clues given each round
  private int x = 50;
  private int y = 100;
  
  public static void main (String[] args)//for testing purposes
  {
    PaintBoard guiWindow = new PaintBoard(4, 9, new String[] {"aqua","chartreuse","crimson","deepskyblue","indigo","mediumorchid","orange","orangered","teal"});
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
  public PaintBoard(int len, int colorLength, String[] colors)
  {
    //sets up the frame
    setSize(len*len*40,len*100);
    setDefaultCloseOperation(EXIT_ON_CLOSE);
    setBackground(new Color( 192, 192, 192 ));
    //initialize the colors array usuing the array of colors sent in
    colors = new String[colors.length];
    for(int i = 0; i < colorLength; i++)
    {
      colors[i] = colors[i];
    }
    //initilizes other variables that are needed for the program
    guess = new int[len*len][len];
    clue = new int[len*len][len];
    length = len;
    
  }//end constructor
  
  public void paint(Graphics canvas)
  {
    canvas.drawString("guesses",length*30,50);
    canvas.drawString("clues",length*100,50);
    //set-up boards
    canvas.setColor(gray);
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
    
    
    
    /*
    canvas.setColor(aqua);
    canvas.fillOval(0, 50, 50, 50);
    canvas.setColor(deepskyblue);
    canvas.fillOval(50, 50, 50, 50);
    canvas.setColor(chartreuse);
    canvas.fillOval(100, 50, 50, 50);
    canvas.setColor(mediumorchid);
    canvas.fillOval(0, 100, 50, 50);
    canvas.setColor(orange);
    canvas.fillOval(50, 100, 50, 50);
    canvas.setColor(orangered);
    canvas.fillOval(100, 100, 50, 50);
    canvas.setColor(mediumseagreen);
    canvas.fillOval(0, 150, 50, 50);
    canvas.setColor(crimson);
    canvas.fillOval(50, 150, 50, 50);
    canvas.setColor(indigo);
    canvas.fillOval(100, 150, 50, 50);
    canvas.setColor(silver);
    canvas.fillOval(50, 200, 50, 50);
    */
    }
}
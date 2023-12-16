import java.awt.Color;
import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

/* ****************************************************************
 * Adira Lindzon
 * 21 April 2016
 * 
 * The Board class for Mastermind initiallizes,
 * updates, and outputs the board for Mastermind.
 * ************************************************************** */
class Board
{
  private int length = 0; //The length of the pattern
  private String[] colors; //The color options the user has inputed to guess from
  private int[][] guess; //Saves the guesses from each of the rounds
  private int[][] clue; //Saves the clues given each round
  
  private final JFrame frame =  new JFrame("Mastermind:");//the JFrame
  private final JPanel panel = new JPanel();//the JPanel
  
  /* *****************************************************************
   * @description: The constructor initializes the boards to store the
   *               guesses given and clues recived as well as storing
   *               the length of the pattern that needs to be guessed.
   * 
   * @param: Len contains the length of the pattern to be guessed.  
   *     
   * @return: none
   **************************************************************** */
  public Board(int len, String[] newColors)
  {
    //initialize the colors array usuing the array of colors sent in
    colors = new String[newColors.length];
    for(int i = 0; i < newColors.length; i++)
    {
      colors[i] = newColors[i];
    }
    //initilizes other variables that are needed for the program
    guess = new int[len*len][len];
    clue = new int[len*len][len];
    length = len;
    //sets up the frame and panel
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setVisible(true);
    frame.setSize(len*len*50,len*100);
    panel.setLayout(new GridLayout((len*len+2),(len*2+1)));
    for(int i = 0; i < len/2; i++)
    {
      panel.add(new JLabel(""));
    }
    panel.add(new JLabel("Guess"));
    if(len % 2 == 0)
    {
      for(int i = 0; i < len-1; i++)
      {
        panel.add(new JLabel(""));
      }
    }
    else
    {
      for(int i = 0; i < len; i++)
      {
        panel.add(new JLabel(""));
      }
    }
    panel.add(new JLabel("Clue"));
    for(int i = 0; i < len/2; i++)
    {
      panel.add(new JLabel(""));
    }
    for(int i = 0; i < (len*2+1); i++)
    {
      panel.add(new JLabel(""));
    }
    
    
    //add the panel to the frame
    frame.add(panel);
    //set background color
    frame.setBackground(new Color( 192, 192, 192 ));
    
  }//end constructor
  
  /* ******************************************************************************************
   * @description: Stores the guess for the current turn in the array with the other guesses.
   *     
   * @parameter: newGuess is an integer array containing the pattern guessed by the player.
   *             turn is an interger for the round number. 
   * 
   * @return: none
   ***************************************************************************************** */
  public void updateGuess(int[] newGuess, int turn)
  {
    for(int i = 0; i < guess[0].length; i++)
    {
      guess[turn][i] = newGuess[i];
      panel.add(new JLabel(colors[newGuess[i]]));
    }//end for
    panel.add(new JLabel("guess"));
    
  }//end updateGuess
  
  /* ******************************************************************************************
   * @description: Determines and stores the clues for the current round as well as determining 
   *               and returning whether or not the guess is correct.
   *     
   * @parameter: newGuess is an integer array containing the pattern guessed by the player.
   *             code is an integer array containing the pattern that is being guessed.
   *             turn is an integer for the round number. 
   *     
   * @return: A boolean value representing the extent to which the code is guessed 
   *          correctly. Returns true when the guess is fully correct and false if any part 
   *          of the pattern is off.
   ***************************************************************************************** */
  public boolean updateClue(int[] newGuess, int[] code, int turn)
  {
    boolean[] taken = new boolean[code.length]; //if a part of the code has been found in the guess
    
    for(int i = 0; i < clue[0].length; i++) //checks if the guess is correct
    {
      if (newGuess[i] == code[i] && !taken[i])
      {
        taken[i] = true;
        int num = 0;
        do
        {
          num = randomLocation();
        }while(clue[turn][num] > 0);
        clue[turn][num] = 2;
        panel.add(new JLabel("white"));
      }//end if
    }//end for
    
    for(int i = 0; i < clue[0].length; i++) //checks to see if the same value is in another spot
    {
      for(int j = 0; j < clue[0].length; j++)
      {
        if(newGuess[i] == code[j] && !taken[j])
        {
          taken[j] = true;
          int num = 0;
          do
          {
            num = randomLocation();
          }while(clue[turn][num] > 0);
          clue[turn][num] = 1;
          panel.add(new JLabel("black"));
        }//end if
      }//end for
    }//end for
    boolean win = true;
    for(int i = 0; i < clue[turn].length; i++)
    {
      if (clue[turn][i] != 2)
      {
        win = false;
        if(clue[turn][i] != 1)
        {
          panel.add(new JLabel(""));
        }
      }
    }
    return win;
  }//end updateClue
  
  /* ******************************************************************************************
   * @description: Returns a random number between 0 and the length of the pattern.
   * 
   * @parameter: none
   * 
   * @return: An integer containing a random number between 0 and the length of the pattern.
   ***************************************************************************************** */
  private int randomLocation()
  {
    return (int)((length*Math.random()));
  }//end randomLocation
}//end Board
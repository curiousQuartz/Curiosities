import javax.swing.JOptionPane;

/* *****************************************************************
 * Adira Lindzon                                                   *
 * 3 December 2023                                                 *
 *                                                                 *
 * The program runs through an entire cycle of Mastermind          *
 * calling the Board class when necessary.                         *
 * *************************************************************** */
class Mastermind
{
  private int turn = 0; //a counter for the turn number
  private int length; //The length of the pattern
  private int numOfColors; //how many colors are being played with
  private String colorList = " | "; //list of color options as inputed by the user for the purpose of JOptionPane outputs only
  private int[] hiddenCode; //An array to store the arrangment of numbers(colors) that need to be discovered to win the game
  private int[] guess; //An array to store the guess from the current round in numbers
  private String[] pattern; //An array to read in and store the guess from the current round in words
  private String[] colors = {"aqua","chartreuse","crimson","deepskyblue","indigo","mediumorchid","orange","orangered","teal"}; //An array containing the ten color options 
  private boolean win = false; //A boolean to store whether the game has been won
  
  /* ******************************************************************************************
   * @description: The constructor calls the setupGame method to initialize the variables with 
   *               user inputes then initializes the Board for the game. This method then runs 
   *               through each turn using methods in the board class and updates the turn 
   *               counter. When the printBoard method from the Board class returns true or the 
   *               counter reaches the end of the board defined by length times length which 
   *               means the game is over then the class end.
   *     
   * @parameter: none
   *     
   * @return: none
   ***************************************************************************************** */
  public Mastermind()
  {
    setupGame();
    Board board = new Board(length, colors);
    
    do
    {
      boolean updated = false;//To make sure colors inputed are valid options
      turn++;//update turn counter
      
      for (int i = 0; i < length; i++)
      {
        do
        {
          try
          {
            pattern[i] = JOptionPane.showInputDialog(null, "Guess a combination of " + length + " colors: " + colorList + ": press enter after each color:", "Round : " + turn,JOptionPane.PLAIN_MESSAGE);
          }
          catch (Exception e)
          {
            quit();
          }
          if (pattern[i] == null)
          {
            pattern[i] = "";
            quit();
          }
        }while(pattern[i].length() < 1);
        for (int j = 0; j < colors.length; j++)
        {
          if (pattern[i].equals(colors[j]))
          {
            guess[i] = j;
            updated = true;
          }//end if
        }//end for
        if (!updated)
        {
          JOptionPane.showMessageDialog(
            null,
            "That color is not one of the option, please enter a different one.", 
            "Error:",JOptionPane.PLAIN_MESSAGE
          );
          i--;
        }
      }
      board.updateGuess(guess, turn-1);
      win = board.updateClue(guess, hiddenCode, turn-1);
      
    }while(!win && turn < length*length);
    
    if (win)
    {
      JOptionPane.showMessageDialog(null, "You Win!!!", "Game Over:",JOptionPane.PLAIN_MESSAGE);
    }
    else
    {
      JOptionPane.showMessageDialog(null, "Better Luck Next Time!", "Game Over:",JOptionPane.PLAIN_MESSAGE);
    }
    
  }//end constructor
  
  /* ******************************************************************************************
   * @description: Initializes the key variables and arrays for the Mastermind game. deals 
   *               with all the parts usually done during the set up of the game.
   *     
   * @parameter: none
   *     
   * @return: none
   ***************************************************************************************** */
  private void setupGame()
  {
    do
    {
      //update numOfColors
      try
      {
        numOfColors = Integer.parseInt(JOptionPane.showInputDialog(null, "How many colors would you like to play with (between 3 & 9)?", "Set Up:",JOptionPane.PLAIN_MESSAGE));
        if (numOfColors < 3 || numOfColors > 9)
        {
          JOptionPane.showMessageDialog(null, "That was not a valid number", "Error:",JOptionPane.PLAIN_MESSAGE);
        }
      }//end try
      catch(Exception e)
      {
        quit();
      }//end catch
    }while(numOfColors < 3 || numOfColors > 9);
    //update colorList
    for(int i = 0; i < numOfColors; i++)
    {
      colorList = colorList + colors[i] + " | ";
    }//end for
    JOptionPane.showMessageDialog(null, "Here are your colors:" + colorList, "Set Up:",JOptionPane.PLAIN_MESSAGE);
    //asks for size of the game
    do
    { 
      try
      {
        length = Integer.parseInt(JOptionPane.showInputDialog(null, "How long would you like the pattern to be (between 2 & 4)?", "Set Up:",JOptionPane.PLAIN_MESSAGE));
        if (length < 2 || length > 4)
        {
          JOptionPane.showMessageDialog(null, "That was not a valid number", "Error:",JOptionPane.PLAIN_MESSAGE);
        }
      }//end try
      catch(Exception e)
      {
        quit();
      }//end catch
    }while(length < 2 || length > 10);
    //initializes arrays
    pattern = new String[length];
    guess = new int[length];
    hiddenCode = new int[length];
    hiddenCode = randomCode(hiddenCode);
    
  }//end setupGame
  
  /* ******************************************************************************************
   * @description: takes an integer array and provides a random value for each posistion in 
   *               the array from a set range of numbers.
   *     
   * @parameter: newCode is an integer array holding all 0's
   *     
   * @return: an integer array with a random set of numbers in a certain range.
   ***************************************************************************************** */
  private int[] randomCode(int[] newCode)
  {
    //generates a random number for each posistion in the array
    for(int i = 0; i < this.length; i++)
    {
      newCode[i] = (int)((colors.length*Math.random()));
    }
    return newCode;
  }//end randomCode
  
  /* ******************************************************************************************
   * @description: Asks the user if they want to end the game and cuts the program short if 
   *               they do. This avoids a game that cannot be quit.
   *     
   * @parameter: none
   *     
   * @return: none
   ***************************************************************************************** */
  private void quit()
  {
    int quitValue = JOptionPane.showConfirmDialog(null, "Are you sure you want to quit?", "Thanks for playing!!!", JOptionPane.YES_NO_OPTION);
    if(quitValue == 0 || quitValue == -1)
    {
      System.exit(0);
    }
  }
  
}//end 
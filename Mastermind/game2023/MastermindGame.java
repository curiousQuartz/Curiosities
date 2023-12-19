import javax.swing.JOptionPane;

/* ********************************************************************************************
 * Adira Lindzon  
 * 3 June 2016  
 * 
 * The main class to initilize the game as many times as the player wishes.
 * ***************************************************************************************** */
class MastermindGame
{
  public static void main (String[] args)
  {
    boolean playAgain = false; //if player wishes to play again
    do
    {
      //run through the game once
      new Mastermind();
      //asks the user if they wish to play again with yes and no buttons (yes returns 0)
      int playAgainValue = JOptionPane.showConfirmDialog(null, "Would you like to play again?", "Thanks for playing!!!", JOptionPane.YES_NO_OPTION); 
      if (playAgainValue == 0)
      {
        playAgain = true;
      }
      else
      {
        playAgain = false;
      }//end if else
    }while(playAgain);//end do-while loop
    
  }//end main
}//end Mastermind_Game
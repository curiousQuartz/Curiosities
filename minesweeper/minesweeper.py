""" Minesweeper """
from random import randint


DEFAULT_ROW = 5
DEFAULT_COLUMN = 5
DEFAULT_MINE = 10
MINE = "#"

GAME_OVER = """
                                ██████████▒▒                  
                            ░░████████████████                
                          ██████████████████████              
                        ██████████████████████████            
                        ████████████████████████████          
                      ██████████████████████████████          
                      ██████████████████████████████          
                      ██████████████████████████████          
                      ██████████████████████████████          
                      ██████    ░░██████▒▒      ████          
                      ██▒▒        ██████        ░░██          
                      ██          ██████          ██          
                      ██        ░░██████▒▒        ██          
                        ██████████    ████████████            
            ░░████        ▓▓██████      ████████        ████  
            ██████▒▒        ██████      ██████░░      ░░████  
          ░░████████          ████████████████        ██████▒▒
              ████████        ██████████████        ██████████
            ████████████                          ████████████
          ██████████████████                ░░████████████████
            ████████████████████░░      ▓▓████████████        
                    ▓▓████████████▓▓████████████████          
                        ████████████████████████▒▒            
                            ████████████████▒▒                
                        ████████████████████████░░            
              ██▓▓████████████████    ██████████████          
          ░░██████████████████            ████████████████████
          ░░████████████▒▒                      ██████████████
              ████████                              ██████████
            ████████                                  ████████
          ▒▒████████                                  ██████  

 ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ 
██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗
██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝
██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗
╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║
 ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝
                                                                          

"""



class Minesweeper(object):
    def __init__(self, rows=None, columns=None, mines=None):
        """Initialization function

        Args:
            rows (int, optional): Grid rows. Defaults to None.
            columns (int, optional): Grid columns. Defaults to None.
            mines (int, optional): Number of mines in grid. Defaults to None.
        """
        self.rows = rows or DEFAULT_ROW
        self.columns = columns or DEFAULT_COLUMN
        self.mines = mines or DEFAULT_MINE
        
        self.record_cache = {
            "win": 0,
            "loss": 0,
        }
        
        self.grid = self.generate_grid()

    def generate_grid(self):
        grid = [[0 for _ in range(self.columns)] for _ in range(self.rows)]
        grid = self.__place_mines(grid)
        return grid

    def __place_mines(self, grid):
        mines_placed = 0
        while mines_placed < self.mines:
            row = randint(0, self.rows - 1)
            column = randint(0, self.columns - 1)
            if grid[row][column] != MINE:
                grid[row][column] = MINE
                grid = self.__add_clues(grid, row, column)
                mines_placed += 1
        return grid

    def __add_clues(self, grid, mine_row, mine_col):
        # Minimums should not go less than 0
        # so only subtract when it's not in the first (0) row/column
        min_row = 0 if mine_row == 0 else mine_row - 1
        min_column = 0 if mine_col == 0 else mine_col - 1
        # Maximums should never exceed the index of the final row/column
        max_row = self.rows - 1
        if mine_row < max_row:
            max_row = mine_row + 1

        max_column = self.columns - 1
        if mine_col < max_column:
            max_column = mine_col + 1
        # increase the hint for any spot not containing another mine.
        for row in range(min_row, max_row + 1):
            for column in range(min_column, max_column + 1):
                if grid[row][column] != MINE:
                    grid[row][column] += 1
        return grid


class MinesweeperShell(Minesweeper):
    blank_space = "-"
    def __init__(self):
        super(MinesweeperShell, self).__init__()
        self.board = [
            [self.blank_space for _ in range(self.columns)]
            for _ in range(self.rows)
        ]
        self.play_game()
    
    def display_grid(self):
        print("-" * (4 * (len(self.board[0])) - 1))
        for row in self.board:
            row = [str(i) for i in row]
            print(" " + " | ".join(row))
            print("-" * (4 * (len(row)) - 1))
        print("-" * (4 * (len(self.grid[0])) - 1))
        for row in self.grid:
            row = [str(i) for i in row]
            print(" " + " | ".join(row))
            print("-" * (4 * (len(row)) - 1))
    
    def play_game(self):
        while True:
            self.display_grid()
            print("Time to guess!")
            row = int(get_input(
                f"Select the row (0-{self.rows - 1}): ",
                options=[str(x) for x in range(self.rows)]
            ))
            column = int(get_input(
                f"Select the column (0-{self.columns - 1}): ",
                options=[str(x) for x in range(self.columns)]
            ))
            if self.grid[row][column] == MINE:
                print(GAME_OVER)
                break
            self.board[row][column] = self.grid[row][column]


def get_input(prompt, options=None, valid_type=None, not_in=None):
    """Taken from https://gist.github.com/curiousQuartz/12580dda3fc7b0d3ec1e1c8ce42f04b3

    Get a user input matching one of the options given to validate the input.

    Args:
        prompt (str): Prompt the user for an input
        options (str): List of valid options for user input. 
        valid_type (object): Check if input can be type converted to this type. 
        not_in (str): Either a list which the input should not be in
            or a string which the input should not be a substring in. 
    Returns:
        str: The valid user input
    """
    print(options)
    user_input = input(prompt).lower()
    if options and user_input not in options:
        # Ask again when the answer is not valid.
        print(f"{user_input} is not a valid input.\n")
        return get_input(prompt, options, valid_type, not_in)
    if valid_type:
        try:
            valid_type(user_input)
        except ValueError:
            print(f"{user_input} is not a valid input.\n")
            return get_input(prompt, options, valid_type, not_in)
    if not_in and user_input in not_in:
        print(f"{user_input} is not a valid input.\n")
        return get_input(prompt, options, valid_type, not_in)
    return user_input


def main():
    MinesweeperShell()


if __name__ == "__main__":
    main()

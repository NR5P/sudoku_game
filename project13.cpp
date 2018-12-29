/***********************************************************************
* Program:
*    Project 12, Sudoku          (e.g. Assignment 10, Hello World)
*    Brother Ridges, CS124
* Author:
*    Nathan Rigg
* Summary: 
*    Enter a brief description of your program here!  Please note that if
*    you do not take the time to fill out this block, YOU WILL LOSE POINTS.
*    Before you begin working, estimate the time you think it will
*    take you to do the assignment and include it in this header block.
*    Before you submit the assignment include the actual time it took.
*
*    Estimated:  2.0 hrs
*    Actual:     2.0 hrs
*      Took me a while to figure out what it wanted after the coordinates
*      was full. I didn't realize at first it wanted to go back to the
*      menu.
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

void showInstructions();
void displayBoard(int sudokuBoard[][9]);
void saveToFile(int sudokuBoard[][9]);
void readFile(char fileName[256], int sudokuBoard[][9]);
int interact(int sudokuBoard[][9]);
void editOneSquare(int sudokuBoard[][9]);
bool computeValues(int value, int row, int col, int sudokuBoard[][9]);
void computeValues(char location[2], int sudokuBoard[][9]);
bool checkIfLetterThere(char location[2], int sudokuBoard[][9]);


/**********************************************************************
 * Add text here to describe what the function "main" does. Also don't forget
 * to fill this out with meaningful text or YOU WILL LOSE POINTS.
 ***********************************************************************/
int main()
{
   int sudokuBoard[9][9];

   char fileName[256] = {};
   cout << "Where is your board located? ";
   cin >> fileName;
   readFile(fileName, sudokuBoard);
   showInstructions();
   displayBoard(sudokuBoard);
   interact(sudokuBoard);

   return 0;
}

/**********************************************************************
 * display the meunu of options
 ***********************************************************************/
 void showInstructions()
 {
   cout << "Options:\n";
   cout << "   ?  Show these instructions\n";
   cout << "   D  Display the board\n";
   cout << "   E  Edit one square\n";
   cout << "   S  Show the possible values for a square\n";
   cout << "   Q  Save and Quit\n\n";
 }

/**********************************************************************
 * display the board
 ***********************************************************************/
void displayBoard(int sudokuBoard[][9])
{
    int count = 1;
    // display the boar header
    cout << "   A B C D E F G H I\n";
    for (int i = 0; i < 9; i++)
    {
        count = 1;
        cout << i + 1 << "  ";
        for (int j = 0; j < 9; j++)
        {
            if (sudokuBoard[i][j] == 0)
                cout << " ";
            else
                cout << sudokuBoard[i][j];

            if (!(count % 3) && count < 9)
                cout << "|";
            else if (count == 9)
            {
                cout << endl;
            }
            else
                cout << " ";
            count++;
        }

        if (i != 8 && i%3 == 2)
            cout << "   -----+-----+-----\n";
    }

    cout << endl;

}

/**********************************************************************
 * display the board
 ***********************************************************************/
 void saveToFile(int sudokuBoard[][9])
 {
   char fileName[256] = {};
   cout << "What file would you like to write your board to: ";
   cin >> fileName;

   ofstream fout(fileName);
   if (fout.fail())
       cerr << "unable to write file" << fileName << endl;

   for (int i = 0; i < 9; i++)
   {
       for (int j = 0; j < 9; j++)
       {
           fout << sudokuBoard[i][j] << " ";
       }
   }

   cout << "Board written successfully\n";
 }

/**********************************************************************
 * display the board
 ***********************************************************************/
void readFile(char fileName[256], int sudokuBoard[][9])
{
   // declare fin and open one step
   ifstream fin(fileName);

   // check for failure
   if (fin.fail())
   {
      cerr << "unable to open file" << fileName << endl;
   }

   for (int i = 0; i < 9; i++)
   {
       for (int j = 0; j < 9; j++)
       {
          fin >> sudokuBoard[i][j];
       }
   }

   fin.close();
}

/**********************************************************************
 * prompt user and check input to see what instruction is requested
 ***********************************************************************/
int interact(int sudokuBoard[][9])
{
    while (true)
    {
        char answer = '\0';
        cout << "> ";
        cin >> answer;
        switch (answer) {
            case '?' : {
                showInstructions();
                cout << endl;
                break;
            }
            case 'D' : {
                displayBoard(sudokuBoard);
                break;
            }
            case 'E' : {
                editOneSquare(sudokuBoard);
                break;
            }
            case 'S' : {
                char location[2];
                cout << "What are the coordinates of the square: ";
                cin >> location;
                computeValues(location, sudokuBoard);
                break;
            }
            case 'Q' : {
                saveToFile(sudokuBoard);
                return 0;
            }
            default :
                cout << "ERROR: INVALID COMMAND";
        }
    }
}

/**********************************************************************
 * check all numbers across and up and down in sudoku puzzle. return 
 * a bool of false if the number is already there and a bool true if not
 ***********************************************************************/
void editOneSquare(int sudokuBoard[][9])
{
    char location[2] = {};
    int value = 0;
    cout << "What are the coordinates of the square: ";
    cin >> location;

    // make letter uppercase
    location[0] = toupper(location[0]);
    if (checkIfLetterThere(location, sudokuBoard))
    {
        cout << "ERROR: Square '" << location << "' is filled\n";
        cout << endl;
    }
    else
    {
        cout << "What is the value at '" << location << "': ";
        cin >> value;
        int column = location[0] - 'A';
        int row = location[1] - '1';

        // check to make sure move is legal
        if (computeValues(value, row, column, sudokuBoard))
        {
            cout << "ERROR: Value '" << value << "' in square '" << location
                 << "' is invalid\n\n";
        } else {
            sudokuBoard[row][column] = value;
            cout << endl;
        }

    }
}

/**********************************************************************
 * check all numbers across and up and down in sudoku puzzle. return 
 * a bool of false if the number is already there and a bool true if not
 ***********************************************************************/
bool computeValues(int value, int row, int col, int sudokuBoard[][9])
{
   // array to record if a number is already in vert or horz of grid
   int possibleNums[10] = {0};

   for (int i = 0; i < 9; i++)
   {
      if (sudokuBoard[row][i] == value || sudokuBoard[i][col] == value)
      {
          return true;
      }
   }
   return false;
}

/**********************************************************************
 * check all numbers across and up and down in sudoku puzzle. return
 * a bool of false if the number is already there and a bool true if not
 ***********************************************************************/
void computeValues(char location[2], int sudokuBoard[][9])
{
    int column = location[0] - 'A';
    int row = location[1] - '1';

    // array to record if a number is already in vert or horz of grid
    int possibleNums[10] = {0};

    int rowLow = 0;
    int rowHigh = 0;

    int colLow = 0;
    int colHigh = 0;

    // find row low and high
    if (row < 3)
    {
        rowLow = 0;
        rowHigh = 2;
    }
    else if (row < 6)
    {
        rowLow = 3;
        rowHigh = 5;
    }
    else
    {
        rowLow = 6;
        rowHigh = 8;
    }

    // find column low and high
    if (column < 3)
    {
        colLow = 0;
        colHigh = 2;
    }
    else if (column < 6)
    {
        colLow = 3;
        colHigh = 5;
    }
    else
    {
        colLow = 6;
        colHigh = 8;
    }

    for (int i = rowLow; i <= rowHigh; i++)
    {
        for (int j = colLow; j <= colHigh; j++)
        {
            if (sudokuBoard[i][j])
                possibleNums[sudokuBoard[i][j]] += 1;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        if (sudokuBoard[row][i])
            possibleNums[sudokuBoard[row][i]] += 1;
        if (sudokuBoard[i][column])
            possibleNums[sudokuBoard[i][column]] += 1;
    }

    cout << "The possible values for '" << location << "' are: ";

    //TODO working on this
    for (int i = 1; i < 10; i++)
    {
        int count = 0;

        if (!possibleNums[i])
        {
            if (count > 0)
            {
                cout << ", ";
            }
            cout << i;
            count++;
        }
    }
    cout << endl << endl;
}

/**********************************************************************
 * check to see if theres a letter there already
 ***********************************************************************/
bool checkIfLetterThere(char location[2], int sudokuBoard[][9])
{
    // turn column letter to number
    int column = location[0] - 'A';
    int row = location[1] - '1';
    if (sudokuBoard[row][column])
        return true;
    else
        return false;
}













































































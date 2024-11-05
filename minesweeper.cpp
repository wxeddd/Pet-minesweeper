#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <unordered_map>
#include <ctime>

using namespace std;

unordered_map<string, string> setColor = {                          // unordered map for easier and more intuitive use of ANSI Escape Codes to manage output color
    {"DEFAULT", "\033[0m"},
    {"BLACK", "\033[30m"},
    {"RED", "\033[31m"},
    {"GREEN", "\033[32m"},
    {"YELLOW", "\033[33m"},
    {"BLUE", "\033[34m"},
    {"MAGENTA", "\033[35m"},
    {"CYAN", "\033[36m"},
    {"WHITE", "\033[37m"},
    {"GRAY", "\033[90m"},
    {"RED_BRIGHT", "\033[91m"},
    {"GREEN_BRIGHT", "\033[92m"},
    {"YELLOW_BRIGHT", "\033[93m"},
    {"BLUE_BRIGHT", "\033[94m"},
    {"MAGENTA_BRIGHT", "\033[95m"},
    {"CYAN_BRIGHT", "\033[96m"},
    {"WHITE_BRIGHT", "\033[97m"},
    {"BLACK_BG", "\033[40m"},
    {"RED_BG", "\033[41m"},
    {"GREEN_BG", "\033[42m"},
    {"YELLOW_BG", "\033[43m"},
    {"BLUE_BG", "\033[44m"},
    {"MAGENTA_BG", "\033[45m"},
    {"CYAN_BG", "\033[46m"},
    {"WHITE_BG", "\033[47m"},
    {"GRAY_BRIGHT_BG", "\033[100m"},
    {"RED_BRIGHT_BG", "\033[101m"},
    {"GREEN_BRIGHT_BG", "\033[102m"},
    {"YELLOW_BRIGHT_BG", "\033[103m"},
    {"BLUE_BRIGHT_BG", "\033[104m"},
    {"MAGENTA_BRIGHT_BG", "\033[105m"},
    {"CYAN_BRIGHT_BG", "\033[106m"},
    {"WHITE_BRIGHT_BG", "\033[107m"}
};
void printGrid(char **arr, size_t length);
char **createArray(size_t length);
void placeMines(char **arr, size_t length, int numMines);
void deleteArray(char **arr, size_t length);

int main()
{
    size_t lengthLite = 0;
    cout<<"Enter length of grid: ";
    cin >> lengthLite;
    const size_t length = lengthLite;
    unsigned int numMinesLite = 0;
    cout << "Enter number of mines: ";
    cin >> numMinesLite;
    const unsigned int numMines = numMinesLite;
    auto a = createArray(length);
    placeMines(a, length, numMines);
    printGrid(a, length);
    system("pause");
    deleteArray(a, length);
}

void printGrid(char **arr, size_t length)                           //  function to print grid
{
    char ROWS = 'A';
    int COLS = 1;
    cout << endl
         << "   ";
    for (size_t i = 0; i < length; i++)                             //  Print COLUMN numbers for better orientation in the grid
    {
        int width = 4;                                              //added pudding so COLUMN numbers wouldn`t shift when their lenght is longer than 1 symbol
        string numStr = to_string(COLS);                            
        int leftPadding = (width - numStr.size()) / 2;
        int rightPadding = width - numStr.size() - leftPadding;
        cout << setColor["YELLOW_BRIGHT"] << setw(leftPadding + numStr.size()) << COLS++ << setw(rightPadding) << " " << setColor["DEFAULT"]; //output COLUMN number
    }
    string horizontalMesh = "  +";                                  
    for (int i = 0; i < length; i++)                                //  added horizontalMesh for easier grid output and optimize number of cout calls
    {
        horizontalMesh += "---+";                                   // making horizontalMesh string as long, as the grid
    }
    
    cout << endl;                       
    for (size_t i = 0; i < length; i++)                             //  printing grid`s row
    {
        cout << setColor["RED_BRIGHT"] << horizontalMesh << endl;   //  printing horizontal barrier
        cout << setColor["YELLOW_BRIGHT"] << ROWS++;                //  printing ROW`s number for better orientation in the grid                
        cout <<setColor["RED_BRIGHT"]<< " |";                       //  printing side border between ROW number and first cell
        for (size_t j = 0; j < length; j++)                         //  printing row
        {
            cout << setColor["DEFAULT"]<< " " << arr[i][j];                               //  printing cell`s content
            cout << setColor["RED_BRIGHT"]<< " |";                //  printing border between cells
        }
        cout << endl;                                               //  new line 
    }

    cout << setColor["RED_BRIGHT"] << horizontalMesh << setColor["DEFAULT"] << endl;       //  printing bottom horizontal border
}
char **createArray(size_t length)                                   //  function to return matrix
{
    char **arr = new char *[length];                                //  create an array
    for (size_t i = 0; i < length; i++)
    {
        arr[i] = new char[length];
        for (size_t j = 0; j < length; j++)
        {
            arr[i][j] = ' ';
        }
    }
    return arr;
}
void deleteArray(char **arr, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}
void placeMines(char **arr, size_t length, int numMines)
{
    srand(time(0));
    for(int n = 0; n<numMines; n++){
        size_t i = rand()%length;
        size_t j = rand()%length;
        arr[i][j] = 'X';
    }    
}
    // add progress board:  Time: 00:45 | Flags left: 3 | Moves: 10.
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <unordered_map>
#include <ctime>
#include <vector>

using namespace std;
vector<int> minesArray={};
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
struct Cell {
    string content = " ";
    string visibleContent = "#"; 
    unsigned int surroundingMines = 0;
    bool isMine = false;
    bool isNearMine = false;
    bool isFlagged = false;
    bool isOpened = false;
    bool isDetonated = false;
    

    void updateCellInformation(){
        if(isMine){
            content = 'X';
        } else if(isNearMine && !isMine){
            content = to_string(surroundingMines);
        }else {
            content = ' ';
        }
    }
    void updateCellStatus(){
         visibleContent = isOpened ? content : visibleContent;
        //visibleContent = isFlagged ? "F" : visibleContent;
    }
    void printCell(){
        cout << /*visibleC*/content;
    }

};
void printGrid(Cell **arr, size_t length);
Cell **createArray(size_t length);
void placeMines(Cell **arr, size_t length, unsigned int numOfMines);
void deleteArray(Cell **arr, size_t length);
void updateCellInformation(Cell** arr, size_t length);
void cellsNearMines(Cell** arr, vector<int>& minesArray, unsigned int numOfMines, size_t lenght);
void calculateSurroundingMines(Cell** arr, size_t length);

int main()
{

    size_t lengthLite = 0;
    cout<<"Enter length of grid: ";
    cin >> lengthLite;
    const size_t length = lengthLite;
    unsigned int numOfMinesLite = 0;
    cout << "Enter number of mines: ";
    cin >> numOfMinesLite;
    const unsigned int numOfMines = numOfMinesLite;
    auto a = createArray(length);
    placeMines(a, length, numOfMines);
    cellsNearMines(a, minesArray, numOfMines, length );
    updateCellInformation(a,length);
    printGrid(a,length);
    system("pause");
    deleteArray(a, length);
}

void printGrid(Cell **arr, size_t length)                           //  function to print grid
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
            cout << setColor["DEFAULT"]<< " ";
            arr[i][j].printCell();                             //  printing cell`s content
            cout << setColor["RED_BRIGHT"]<< " |";                  //  printing border between cells
        }
        cout << endl;                                               //  new line 
    }

    cout << setColor["RED_BRIGHT"] << horizontalMesh << setColor["DEFAULT"] << endl;       //  printing bottom horizontal border
}
Cell **createArray(size_t length)                                   //  function to return matrix
{
    Cell **arr = new Cell *[length];                                //  create a matrix
    for (size_t i = 0; i < length; i++)
    {
        arr[i] = new Cell [length];                                 //  create an array of Cells
    }
    return arr;
}
void deleteArray(Cell **arr, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}
void placeMines(Cell **arr, size_t length, unsigned int numOfMines)
{
    srand(time(0));
    for(int n = 0; n<numOfMines;){
        size_t i = rand()%length;
        size_t j = rand()%length;
        if(!arr[i][j].isMine){
            arr[i][j].isMine = true;
            minesArray.push_back(i);
            minesArray.push_back(j);
            n++;
        }

    }    
}
void cellsNearMines(Cell** arr, vector<int>& minesArray, unsigned int numOfMines, size_t length)
{
    const int directions[8][2]=             //an array for easier calculations if the neighbouring cell is in the grid bounds
    {
        { -1, -1 },{ -1, 0 },{ -1, 1 },
        { 0, -1 },/*cell-mine*/{ 0, 1 },
        { 1, -1 },{ 1, 0 },{ 1, 1 }
    };
    
    for(unsigned int i = 0 ; i< numOfMines*2 ;i+=2)       
    {
        int mineROW = minesArray[i];                    // every [2n-th] element is the ROW coordinate of a mine, n>=0 , n is Natural number
        int mineCOL = minesArray[i+1];                  // every [2n+1-th] element is the COL coordinate of a mine, n>=0 , n is Natural number
        for (const auto& direction : directions) {
        int neighborROW = mineROW + direction[0]; // Calculate neighbor's row
        int neighborCOL = mineCOL + direction[1]; // Calculate neighbor's column

            // Check if neighbor is within bounds
            if (neighborROW >= 0 && neighborROW < length &&
                neighborCOL >= 0 && neighborCOL < length) {
                arr[neighborROW][neighborCOL].surroundingMines++;
                arr[neighborROW][neighborCOL].isNearMine= true;
                }
            }
            
    }
}
void updateCellInformation(Cell** arr, size_t length){
    for(size_t i = 0; i < length; i++){
        for(size_t j = 0; j< length; j++){
            arr[i][j].updateCellInformation();
        }
    }
}
   // add progress board:  Time: 00:45 | Flags left: 3 | Moves: 10.
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <unordered_map>
#include <ctime>
#include <vector>
#include <utility>
#include <cctype>
using namespace std;


vector<int> minesArray={};
void clearScreen() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux or macOS
    #endif
}
static const int directions[8][2]=             //an array for easier calculations if the neighbouring cell is in the grid bounds
    {
        { -1, -1 },{ -1, 0 },{ -1, 1 },
        { 0, -1 },/*cell-mine*/{ 0, 1 },
        { 1, -1 },{ 1, 0 },{ 1, 1 }
    };
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
    bool detonated = false;
    bool isBlank = true;
    

    void setCellContent(){
        if(isMine){
            content = 'X';
        } else if(isNearMine && !isMine){
            content = to_string(surroundingMines);
        }else {
            content = ' ';
        }
    }
    void updateCellVisualContent(){
        visibleContent = isOpened ? content : isFlagged ? "F": "#";
    }
    void printCell(){
        cout << visibleContent;
    }
    bool checkIfDetonated(){
        if(isMine && isOpened  ){
            detonated = true;
        }
        return detonated;
    }

};
void printGrid(Cell **arr, size_t length);
Cell **createArray(size_t length);
void placeMines(Cell **arr, size_t length, unsigned int numOfMines);
void deleteArray(Cell **arr, size_t length);
void setCellContent(Cell** arr, size_t length);
void cellsNearMines(Cell** arr, vector<int>& minesArray, unsigned int numOfMines, size_t length);
void updateCellStatus(Cell** arr, size_t length);
void move(Cell** arr, bool& end, size_t length);
void blankCellExpansion(Cell** arr, vector<int>& openedBlankCell, size_t length);
size_t getLength();
unsigned int getNumOfMines();
int main()
{

    bool end = false;
    const size_t length = getLength();
    const unsigned int numOfMines = getNumOfMines();
    auto a = createArray(length);
    placeMines(a, length, numOfMines);
    cellsNearMines(a, minesArray, numOfMines, length );
    setCellContent(a,length);
    printGrid(a,length);
    while( !end){
    move(a, end,length);
    clearScreen();
    printGrid(a,length);
    }
    system("pause");
    deleteArray(a, length);
}

size_t getLength(){
    size_t lengthLite;
    cout<<"Enter length of grid: ";
    cin >> lengthLite;
    return lengthLite;
}
unsigned int getNumOfMines(){
    unsigned int numOfMinesLite = 0;
    cout << "Enter number of mines: ";
    cin >> numOfMinesLite;
    return numOfMinesLite;
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
            arr[i][j].isBlank = false;
            minesArray.push_back(i);
            minesArray.push_back(j);
            n++;
        }

    }    
}
void cellsNearMines(Cell** arr, vector<int>& minesArray, unsigned int numOfMines, size_t length)
{
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
                arr[neighborROW][neighborCOL].isBlank = false;
                }
            }
            
    }
}
void setCellContent(Cell** arr, size_t length){
    for(size_t i = 0; i < length; i++){
        for(size_t j = 0; j< length; j++){
            arr[i][j].setCellContent();
        }
    }
}
void blankCellExpansion(Cell **arr, vector<int>& openedBlankCell, size_t length)
{
    vector<int> neighbouringBlankClosedCells = {};
    for (int i = 0; i < openedBlankCell.size(); i += 2)
    {
        for (const auto &direction : directions)
        {
            int neighborROW = openedBlankCell[i + 0] + direction[0];
            int neighborCOL = openedBlankCell[i + 1] + direction[1];
            if (neighborROW >= 0 && neighborROW < length &&
                neighborCOL >= 0 && neighborCOL < length &&
                arr[neighborROW][neighborCOL].isBlank && !arr[neighborROW][neighborCOL].isOpened)
            {

                arr[neighborROW][neighborCOL].isOpened = true;
                neighbouringBlankClosedCells.push_back(neighborROW);
                neighbouringBlankClosedCells.push_back(neighborCOL);
                arr[neighborROW][neighborCOL].updateCellVisualContent();
            }
        }
    }
    if (neighbouringBlankClosedCells.size() != 0)
    {
        blankCellExpansion(arr, neighbouringBlankClosedCells, length);
    }
}
void move(Cell** arr, bool& end, size_t length){
    string move, moveROW, moveAction, moveCOL;
    cout << "Enter a move ROW:COL-Action(F/O): ";
    getline(cin, move);
    istringstream input(move);
    getline(input, moveROW, ':'); // Read the ROW part before ':'
    getline(input, moveCOL, ' '); // Read the COL part before the space
    getline(input, moveAction, ' ');
    int indexROW = toupper(moveROW[0]) - 'A';
    int indexCOL = stoi(moveCOL) -1;
    for(size_t i = 0; i < moveAction.length(); i++){
    moveAction[i] = toupper(moveAction[i]);
    }
    if (moveAction == "F")
    {
        arr[indexROW][indexCOL].isFlagged = true;
    }
    else if (moveAction == "O")
    {
        if(!arr[indexROW][indexCOL].isFlagged){
        arr[indexROW][indexCOL].isOpened = true;
        }
    }
    else if (moveAction == "UF")
    {
        arr[indexROW][indexCOL].isFlagged = false;
    }else {
        cout<< " Invalid input";
    }
    if( arr[indexROW][indexCOL].isBlank){
    vector<int> openedBlankCell = {indexROW, indexCOL}; 
    blankCellExpansion(arr, openedBlankCell, length);
    }

    end = arr[indexROW][indexCOL].checkIfDetonated();
    arr[indexROW][indexCOL].updateCellVisualContent();
}


//    move: ROW:COL action[Flag/Open]
// add progress board:  Time: 00:45 | Flags left: 3 | Moves: 10.
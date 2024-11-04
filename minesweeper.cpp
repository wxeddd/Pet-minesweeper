#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>

using namespace std;

enum Color
{
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_AQUA,
    COLOR_RED,
    COLOR_PURPLE,
    COLOR_YELLOW,
    COLOR_DEFAULT,
    COLOR_GRAY,
    COLOR_LIGHTBLUE,
    COLOR_LIGHTGREEN,
    COLOR_LIGHTAQUA,
    COLOR_LIGHTRED,
    COLOR_LIGHTPURPLE,
    COLOR_LIGHTYELLOW,
    COLOR_LIGHTWHITE
};

void setColor(int textColor);
void printGrid(char **arr, size_t length);
char **createArray(size_t length);
void deleteArray(char **arr, size_t length);
int main()
{
    size_t lengthlite = 0;
    cin >> lengthlite;
    const size_t length = lengthlite;
    auto a = createArray(length);
    printGrid(a, length);
    deleteArray(a, length);
    system("pause");
}

void printGrid(char **arr, size_t length)
{
    char ROWS = 'A';
    int COLS = 1;
    cout << endl << "   ";

    setColor(COLOR_LIGHTYELLOW); 
    for (size_t i = 0; i < length; i++)
    {
        int width = 4;
        string numStr = to_string(COLS);
        int leftPadding = (width - numStr.size()) / 2;
        int rightPadding = width - numStr.size() - leftPadding;
        cout << setw(leftPadding + numStr.size()) << COLS++
             << setw(rightPadding) << " "; 
    }
    setColor(COLOR_DEFAULT);

    for (size_t i = 0; i < length; i++)
    {
        setColor(COLOR_LIGHTRED);
        cout << endl
             << "  +";
        for (size_t k = 0; k < length; k++)
        {
            cout << "---+";
        }
        cout << endl;
        setColor(COLOR_LIGHTYELLOW);
        cout << ROWS++;
        setColor(COLOR_RED);
        cout << " |";
        setColor(COLOR_DEFAULT);
        for (size_t j = 0; j < length; j++)
        {
            cout << " " << arr[i][j]; 
            setColor(COLOR_LIGHTRED);
            cout<<" |";
        }
    }

    setColor(COLOR_LIGHTRED);
    cout << endl << "  +";
    
    for (size_t k = 0; k < length; k++)
    {
        cout << "---+";
    }
    setColor(COLOR_DEFAULT);
}
char **createArray(size_t length)
{
    char **arr = new char *[length];
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
void setColor(int textColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}
/*
    0 = Black
    1 = Blue
    2 = Green
    3 = Aqua
    4 = Red
    5 = Purple
    6 = Yellow
    7 = White
    8 = Gray
    9 = Light Blue
    10 = Light Green
    11 = Light Aqua
    12 = Light Red
    13 = Light Purple
    14 = Light Yellow
    15 = Bright White
*/
// add progress board:  Time: 00:45 | Flags left: 3 | Moves: 10.

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;
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

    for (size_t i = 0; i < length; i++)
    {
        int width = 4;
        string numStr = to_string(COLS);
        int leftPadding = (width - numStr.size()) / 2;
        int rightPadding = width - numStr.size() - leftPadding;
        cout << setw(leftPadding + numStr.size()) << COLS++
             << setw(rightPadding) << " ";
    }

    for (size_t i = 0; i < length; i++)
    {
        cout << endl
             << "  +";
        for (size_t k = 0; k < length; k++)
        {
            cout << "---+";
        }
        cout << endl;
        cout << ROWS++ << " |";
        for (size_t j = 0; j < length; j++)
        {
            cout << " " << arr[i][j] << " |";
        }
    }

    cout << endl << "  +";
    
    for (size_t k = 0; k < length; k++)
    {
        cout << "---+";
    }
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
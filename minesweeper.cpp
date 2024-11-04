#include <iostream>
#include <string>

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

}

void printGrid(char **arr, size_t length)
{
    char ROWS = 'A';
    int COLS = 1;
    cout<<endl<<"    ";
    for(size_t i = 0; i<length;i++)
    {
        cout<<COLS++<<"   ";
        
    }
    for (size_t i = 0; i < length ; i++)
    {
        cout<<endl<<"  +";
        for(size_t k = 0; k< length ;k++)
        {
            cout<<"---+";
        }
        cout<<endl;
        cout<< ROWS++<<" |";
        for (size_t j = 0; j <length ; j++)
        {
            cout<<" "<<arr[i][j]<<" |"; 
        }
    }
    cout<<endl<<"  +";
    for(size_t k = 0; k< length ;k++)
        {
            cout<<"---+";
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
    for(size_t i = 0; i < length; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}
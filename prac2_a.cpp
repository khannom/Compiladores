#include <iostream>
#include <string>
using namespace std;

bool isLetter (char letter)
{
    return (letter>='a'&&letter<='z')|(letter>='A'&&letter<='Z');
}

bool isDigit (char digit)
{
    return digit>='0'&&digit<='9';
}

int id_AFDdiagram(string word)
{
    short state = 1;
    char symbol = word[0];
    int i=0;
    while (symbol)
    {
        switch (state)
        {
        case 1:
            if(isLetter(symbol))
                state = 3;
            else if(isDigit(symbol))
                state = 2;
            else
            {
                cout<<"error"<<endl; return 1;
            }
            break;
        case 2:
            cout<<"error"<<endl;
            return 1;
            break;
        case 3:
            if(isDigit(symbol))
                state = 3;
            else if(isLetter(symbol))
                state = 3;
            else
            {
                cout<<"error"<<endl;
                return 1;
            }
            break;
        }
        ++i;
        symbol = word[i];
    }
    if(state != 3)
    {
        cout<<"error"<<endl;
        return 1;
    }
    cout<<"Identificador aceptado."<<endl;
    return 0;
}

int main ()
{
    string word;
    cout<<"Ingrese una palabra: ";
    cin>>word;
    id_AFDdiagram(word);
    return 0;
}
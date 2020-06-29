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

int num_AFDdiagram(string word)
{
    int state = 0;
    char symbol = word[0];
    int i=0;
    while (symbol)
    {
        switch (state)
        {
        case 0:
            if(isDigit(symbol))
                state = 1;
            else if(symbol=='-')
                state = 2;
            else if (symbol=='.')
            {
                state = 3;
            }
            else
            {
                cout<<"error"<<endl; return 1;
            }
            break;
        case 1:
            if(isDigit(symbol))
                state = 1;
            else if(symbol=='.')
                state = 3;
            else if(symbol=='-')
                state = 5;
            else
            {
                cout<<"error"<<endl; return 1;
            }
            break;
        case 2:
            if(isDigit(symbol))
                state = 1;
            else if(symbol=='.')
                state = 3;
            else if (symbol=='-')
                state = 5;
            else
            {
                cout<<"error"<<endl;
                return 1;
            }
            break;
        case 3:
            if(isDigit(symbol))
                state = 4;
            else if(symbol=='-')
                state = 5;
            else if(symbol=='-')
                state = 5;
            else
            {
                cout<<"error"<<endl; return 1;
            }
            break;
        case 4:
            if(isDigit(symbol))
                state = 4;
            else if(symbol=='-')
                state = 5;
            else if(symbol=='-')
                state = 5;
            else
            {
                cout<<"error"<<endl; return 1;
            }
            break;
        case 5:
            cout<<"error"<<endl;
            return 1;
            break;
        }
        ++i;
        symbol = word[i];
    }
    if(state != 1 && state != 4)
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
    num_AFDdiagram(word);

    return 0;
}
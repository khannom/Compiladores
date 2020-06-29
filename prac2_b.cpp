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


int id_AFDtable(string word)
{
    int tabla[3][3] = {{1,2,-1},{-1,-1,-1},{2,2,0}};
    
    int state = 0;
    int input = 0;
    char symbol;
    int i = -1;
    do
    {
        ++i;
        symbol = word[i];
        if (isDigit(symbol))
            input = 0;
        else if (isLetter(symbol))
            input = 1;
        else if (!symbol)
            input = 2;
        else
        {
            cout<<"error"<<endl;
            return 1;
        }
        state = tabla[state][input];
        if(state==-1)
        {
            cout<<"error"<<endl;
            return 1;
        }
    } while (state!=0);
    cout<<"Identificador aceptado"<<endl;
    return 0;
}


int main ()
{
    string word;
    cout<<"Ingrese una palabra: ";
    cin>>word;
    id_AFDtable(word);
    return 0;
}



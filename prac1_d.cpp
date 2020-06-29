#include <fstream>
#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main ()
{
    ifstream readFile("fuente.txt");
    string word;
    while (readFile>>word)
    {
        regex palabra       ("[a-zA-Z]+[0-9a-zA-Z]*");
        regex entero        ("[0-9]+");
        regex char_especial ("[\\*\\+\\-/]");
        if(regex_match(word,palabra))
        {
            cout<<word<<" es una palabra."<<endl;
        }
        else if(regex_match(word,entero))
        {
            cout<<word<<" es un entero."<<endl;
        }
        else if(regex_match(word,char_especial))
        {
            cout<<word<<" es un caracter especial."<<endl;
        }
        else
        {
            cout<<word<<" no esta definido."<<endl;
        }        
    }
    readFile.close();
    return 0;
}
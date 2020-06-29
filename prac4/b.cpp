#include <stdio.h>
#include <iostream>

using namespace std;

char preanalisis;
void resto();
void term();
void parea(char);
void error();
bool flag = true;

bool isDigit(char a)
{
    return (a>='0' && a<='9');
}

void exp()
{
    if(isDigit(preanalisis))
    {
        cout<<preanalisis;
        parea(preanalisis);
        resto();
    }
    else
        error();
    
}

void resto()
{
    if(preanalisis=='+')
    {
        parea('+');
        term();
        cout<<'+';
        resto();
    }
    else if (preanalisis == '-')
    {
        parea('-');
        term();
        cout<<'-';
        resto();
    }
    else if(preanalisis == '\n')
    {
        
    }
    else
    {
        error();
    }
    
    
}

void term()
{
    if(isDigit(preanalisis))
    {
        cout<<preanalisis;
        parea(preanalisis);
    }
    else
        error();
}

void error()
{
    flag = false;
}

void parea(char t)
{
    if (preanalisis==t)
        preanalisis=getchar();
    else
        error();
}

int main()
{
    cout<<"Forma infija: ";
    preanalisis=getchar(); //lee un carácter de la entrada
    cout<<"Forma postfija: ";
    exp();
    
    if(flag)
        printf("\nCadena reconocida\n");
    else
        printf("\nError de sintaxis\n");
    return 0;
}


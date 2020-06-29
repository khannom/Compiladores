#include <stdio.h>
#include <ctype.h>
#include <iostream>

#define MAS '+'
#define MENOS '-'
#define NUM 256
#define FIN -1

using namespace std;

char lexema[80];
int tok;
void parea(int);
void error();
void Resto();
void Term();
int scanner();

void Exp()
{
    if (tok==NUM)
    {
        Term();
        Resto();
    }
    else
        error();
}

void Resto()
{
    if (tok == MAS)
    { 
        parea(MAS);
        Term();
        printf("+");
        Resto();
    }
    else if (tok == MENOS)
    { 
        parea(MENOS);
        Term();
        printf("-");
        Resto();
    }
    else //cadena vacia
        ;
}

void Term()
{
    if (tok==NUM)
    {
        printf("%s",lexema);
        parea(NUM);
    }
    else
        error();
}

void error()
{
    printf("Error de sintaxis\n");
}

void parea(int t)
{
    if (tok==t)
        tok=scanner();
    else
        error();
}

int scanner()
{
    int c,i;
    do c=getchar(); while(c==' ');
    if (c=='\n')
        return FIN;
    if (c==MAS || c==MENOS)
        return c;
    if(isdigit(c))
    {
        i=0;
        do {
            lexema[i++]=c;
            c=getchar();
        } while(isdigit(c));
        lexema[i]=0;
        ungetc(c,stdin);
        return NUM;
    }
}

int main()
{
    cout<<"Ingrese en forma infija: ";
    tok=scanner();
    cout<<"Forma postfija: ";
    Exp();
    cout<<endl;
}
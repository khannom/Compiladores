#include <stdio.h>


int preanalisis;

void parea(int);
void A();
void B();
void error();
bool flag = true;

void S()
{
    if (preanalisis == 'x')
        { parea('x'); S(); }
    else if (preanalisis == 'a'){
        A(); 
        B();
        parea('c');
        if(preanalisis!='\n')
            error();
    }
    else
        error();
}

void A()
{
    if (preanalisis == 'a')
        parea('a');
    else
        error();
}

void B()
{
    if (preanalisis == 'b')
        parea('b');
    else
        error();
}

void error()
{
    printf("Error de sintaxis\n");
    flag = false;
}

void parea(int t)
{
    if (preanalisis==t)
        preanalisis=getchar();
    else
        error();
}

int main()
{
    preanalisis=getchar(); //lee un carácter de la entrada
    S();
    
    if(flag)
        printf("Cadena reconocida\n");
    return 0;
}






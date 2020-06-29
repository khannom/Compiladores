#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string.h>

int main ()
{
    char c;
    FILE* f;
    f=fopen("fuente.txt","rt");
    while (1)
    {
        c=fgetc(f);
        if(c==EOF)
            break;
        std::cout<<c;
    }
    
    fclose(f);
    return 0;
}
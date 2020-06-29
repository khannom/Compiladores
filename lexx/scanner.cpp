#include <iostream>
#include "tokens.h"

using namespace std;

extern int yylex();
extern char* yytext;

int main()
{
    int ntoken;

    while (ntoken = yylex())
    {
        cout <<"token: "<< ntoken <<" lexema: "<<yytext<<endl;;
    }

    return 0;
}

// A function to implement bubble sort 
void bubbleSort(int arr[], int n) 
{ 
   int i, j;                        // 1
   for (i = 0; i < n-1; i++)        // n-1
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
}


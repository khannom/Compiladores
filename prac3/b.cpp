#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAYOR '>'
#define MENOR '<'
#define PUNTOYCOMA ';'
#define PARI '('
#define PARD ')'
#define CORCHETEI '['
#define CORCHETED ']'
#define LLAVEI '{'
#define LLAVED '}'
#define ASIGNACION '='
#define COMA ','
#define HASHTAG '#'
#define ID 256
#define NUM 257
#define MAYORIGUAL 258
#define WHILE 259
#define IF 260
#define OPERADOR 261
#define MENORIGUAL 262
#define IGUAL 263
#define DIFERENTE 264
#define FOR 265
#define INCLUDE 266
#define DO 267
#define STRING 268
#define LEFTSHIFT 269
#define RIGHTSHIFT 270
#define TYPE 271
#define USING 272
#define NAMESPACE 273
#define RETURN 274

int scaner();
void mostrar(int);
int espalres();
FILE *f;
char lexema[80];
int main(int n, char *pal[])
{
    int token;
    f=stdin; //entrada estandar del teclado
    if(n==2) //si se especifico un archivo de lectura
    {
        f=fopen(pal[1],"rt"); //lectura modo texto
        if(f==NULL)
        f=stdin;
    }
    if(f==stdin) //la lectura sera desde la entrada estandar
    printf("Ingrese texto ........ termine con Ctrl z \n");
    while(1)
    {
        token=scaner();
        if(token==EOF) break;
        mostrar(token);
    }
    if(f !=stdin) // si la entrada fue de un archivo
    fclose(f); // entonces cerrar el archivo.
    return 0;
}//fin del main
int scaner()
{
    int c;
    int i;
    do c=fgetc(f); while(isspace(c)); //ignora blancos
    if(c==EOF) return EOF;
    if(isalpha(c)) //regla del ID
    {
        i=0;
        do{
            lexema[i++]=c;
            c=fgetc(f);
        } while(isalnum(c)||c=='_');
        lexema[i]=0;
        ungetc(c,f); //se devuelve c al flujo de entrada
        i=espalres(); // verifica si es palabra reservada
        // WHILE , IF
        if(i>=0)
            return i;
        return ID; // se trata de un ID
    }
    if(isdigit(c)) //regla del NUM
    {
        i=0;
        do{
            lexema[i++]=c;
            c=fgetc(f);
        }while(isdigit(c));
        lexema[i]=0;
        ungetc(c,f);
        return NUM;
    }
    
    if((c==';')||(c==',')||(c=='#')||(c=='(')||(c==')')||(c=='[')||(c==']')||(c=='{')||(c=='}')) return c;

    if(c=='=')
    {
        c=fgetc(f);
        if (c=='=')
        {
            lexema[0]='=';lexema[1]='='; lexema[2]=0;
            return IGUAL;
        }
        ungetc(c,f);
        return ASIGNACION;
    }

    if(c=='>') //regla de ">" o ">="
    {
        c=fgetc(f);
        if(c=='=') //return MAYORIGUAL
        { 
            lexema[0]='>'; lexema[1]='='; lexema[2]=0;
            return MAYORIGUAL;
        }
        else if (c=='>')
        {
            lexema[0]='>'; lexema[1]='>'; lexema[2]=0;
            return RIGHTSHIFT;
        }
        ungetc(c,f);
        return MAYOR; //return MAYOR
    }

    if(c=='<')
    {
        c=fgetc(f);
        if(c=='=')
        { 
            lexema[0]='<'; lexema[1]='='; lexema[2]=0;
            return MENORIGUAL;
        }
        else if(c=='<')
        { 
            lexema[0]='<'; lexema[1]='<'; lexema[2]=0;
            return LEFTSHIFT;
        }
        ungetc(c,f);
        return MENOR; 
    }

    if(c=='!')
    {
        c=fgetc(f);
        if(c=='=') 
        { 
            lexema[0]='!'; lexema[1]='='; lexema[2]=0;
            return DIFERENTE;
        }
        ungetc(c,f);
    }
    
    if((c=='*'))
    {
        lexema[0]='*'; lexema[1]=0;
        return OPERADOR;
    }

    if(c=='+')
    {
        c=fgetc(f);
        if (c=='+')
        {
            lexema[0]='+';lexema[1]='+'; lexema[2]=0;
            return OPERADOR;
        }
        ungetc(c,f);
        lexema[0]='+';lexema[1]=0;
        return OPERADOR;
    }

    if(c=='-')
    {
        c=fgetc(f);
        if (c=='-')
        {
            lexema[0]='-';lexema[1]='-'; lexema[2]=0;
            return OPERADOR;
        }
        ungetc(c,f);
        lexema[0]='-';lexema[1]=0;
        return OPERADOR;
    }

    if(c=='/')
    {
        c=fgetc(f);
        if (c=='/')
        {
            while (1)
            {
                c=fgetc(f);
                if (c=='\n') break;
                if (c==EOF) break;
            }
        }
        else if(c=='*')
        {
            while (1)
            {
                c=fgetc(f);
                if (c=='*'){
                    c=fgetc(f);
                    if (c=='/') break;
                }
                if(c==EOF) break;
            }
        }
        else
        {
            ungetc(c,f);
            lexema[0] = '/';lexema[2] = 0;
            return OPERADOR;
        }
    }
    if (c=='"')
    {
        i = 0;
        c=fgetc(f);
        while (c!='"')
        {
            lexema[i++] = c;
            c = fgetc(f);
            if(c==EOF) break;
        }
        lexema[i] = 0;
        return STRING;
    }
}//fin de scaner
int espalres()
{
    if(strcmp(lexema,"while")==0) return WHILE;
    if(strcmp(lexema,"if")==0) return IF;
    if(strcmp(lexema,"for")==0) return FOR;
    if(strcmp(lexema,"include")==0) return INCLUDE;
    if(strcmp(lexema,"do")==0) return DO;
    if(strcmp(lexema,"using")==0) return USING;
    if(strcmp(lexema,"namespace")==0) return NAMESPACE;
    if(strcmp(lexema,"return")==0) return RETURN;
    if(strcmp(lexema,"int")==0) return TYPE;
    if(strcmp(lexema,"float")==0) return TYPE;
    if(strcmp(lexema,"long")==0) return TYPE;
    if(strcmp(lexema,"double")==0) return TYPE;
    if(strcmp(lexema,"bool")==0) return TYPE;
    return -1;
}

void mostrar(int token)
{
    switch(token)
    {
        case ID: printf("token = ID [%s] \n",lexema); break;
        case NUM: printf("token = NUM [%s] \n",lexema); break;
        case MAYORIGUAL: printf("token = MAYORIGUAL [%s]\n",lexema); break;
        case MENORIGUAL: printf("token = MENORIGUAL [%s]\n",lexema); break;
        case WHILE: printf("token = WHILE [%s] \n",lexema); break;
        case IF: printf("token = IF [%s] \n",lexema); break;
        case FOR: printf("token = FOR [%s] \n",lexema); break;
        case USING: printf("token = USING [%s] \n",lexema); break;
        case NAMESPACE: printf("token = NAMESPACE [%s] \n",lexema); break;
        case RETURN: printf("token = RETURN [%s] \n",lexema); break;
        case INCLUDE: printf("token = INCLUDE [%s] \n",lexema); break;
        case DO: printf("token = DO [%s] \n",lexema); break;
        case PARI: printf("token = PARI [%c] \n",token); break;
        case PARD: printf("token = PARD [%c]\n",token); break;
        case CORCHETEI: printf("token = CORCHETEI [%c]\n",token); break;
        case CORCHETED: printf("token = CORCHETED [%c]\n",token); break;
        case LLAVEI: printf("token = LLAVEI [%c]\n",token); break;
        case LLAVED: printf("token = LLAVED [%c]\n",token); break;
        case MAYOR: printf("token = MAYOR [%c] \n",token); break;
        case MENOR: printf("token = MENOR [%c] \n",token); break;
        case PUNTOYCOMA: printf("token = PUNTOYCOMA [%c]\n",token); break;
        case COMA: printf("token = COMA [%c]\n",token); break;
        case ASIGNACION: printf("token = ASIGNACION [%c]\n",token); break;
        case OPERADOR: printf("token = OPERADOR [%s]\n",lexema); break;
        case IGUAL: printf("token = IGUAL [%s]\n",lexema); break;
        case DIFERENTE: printf("token = DIFERENTE [%s]\n",lexema); break;
        case STRING: printf("token = STRING [%s] \n",lexema); break;
        case TYPE: printf("token = TYPE [%s] \n",lexema); break;
        case HASHTAG: printf("token = HASHTAG [%c] \n",token); break;
    }
}

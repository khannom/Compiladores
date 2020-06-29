#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <vector>

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
#define MAS '+'
#define MENOS '-'
#define PRODUCTO '*'
#define DIVISION '/'
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
#define BEGIN 275
#define END 276

using namespace std;

bool isOperand(const char& a)
{
    return a>='0' && a<='9';
}

bool isOperator(const char& a)
{
	if(a=='+'||a=='*'||a=='-'||a=='/')
        return true;

	return false;
}

int getOperatorWeight(const char& op)
{
	int weight = -1; 
	switch(op)
	{
        case '+':
        case '-':
            weight = 1;
            break;
        case '*':
        case '/':
            weight = 2;
            break;
	}
	return weight;
}

int hasHigherPrec(const char& op1, const char& op2)
{
	int op1Weight = getOperatorWeight(op1);
	int op2Weight = getOperatorWeight(op2);

	// If operators have equal precedence, return true if they are left associative. 
	// return false, if right associative. 
	// if operator is left-associative, left one should be given priority. 
	
	return op1Weight > op2Weight ?  true: false;
}

int token;
void parea(int);
void error();
int scanner();
void mostrar(int);
int espalres();
FILE *f;
char lexema[80];
vector<string> expresionInfija;
double evaluar();
bool guardar = false;
bool syntaxError = false;

//producciones
void Program();
void Programx();
void Expr();
void Exprx();
void Term();
void Termx();
void Factor();

void Program()
{
    if(token == BEGIN)
    {
        parea(BEGIN);
        guardar = true;
        Expr();
        guardar = false;
        if(!syntaxError) evaluar();
        parea(PUNTOYCOMA);
        Programx();
        parea(END);
    }
    else
    {
        error();
    }
}

void Programx()
{
    if(token == NUM || token == PARI || token == MAS || token == MENOS)
    {
        guardar = true;
        Expr();
        guardar = false;
        if(!syntaxError) evaluar();
        parea(PUNTOYCOMA);
        Programx();
    }
    else
    {
        //vacio
    }
}

void Expr()
{
    if(token == NUM || token == PARI)
    {
        Term();
        Exprx();
    }
    else
    {
        error();
    }
}

void Exprx()
{
    if (token == MAS)
    {
        parea(MAS);
        Term();
        Exprx();
    }
    else if (token == MENOS)
    {
        parea(MENOS);
        Term();
        Exprx();
    }
    else
    {
        //vacio
    }
}

void Term()
{
    if (token == NUM || token == PARI)
    {
        Factor();
        Termx();
    }
    else
    {
        error();
    }
}

void Termx()
{
    if (token == PRODUCTO)
    {
        parea(PRODUCTO);
        Factor();
        Termx();
    }
    else if (token == DIVISION)
    {
        parea(DIVISION);
        Factor();
        Termx();
    }
    else
    {
        //vacio
    }
}

void Factor()
{
    if (token == NUM)
    {
        parea(NUM);
    }
    else if (token == PARI)
    {
        parea(PARI);
        Expr();
        parea(PARD);
    }
    else
    {
        error();
    }
}



void error()
{
    syntaxError = true;
}

void parea(int t)
{
    if (token==t)
    {
        if (guardar)
        {
            expresionInfija.push_back(lexema);
        }
        token=scanner();
    }
    else
        error();
}

double evaluar()
{
    vector<string> pila;
    vector<string> expresionPostfija;
    
    for (auto &&i : expresionInfija)
    {
        if(isOperand(i[0]))
        {
            expresionPostfija.push_back(i);
        }
        else if (isOperator(i[0]))
        {
            while (!pila.empty()
                    && !((pila.back()[0])=='(')
                    && hasHigherPrec((pila.back())[0], i[0]))
            {
                expresionPostfija.push_back(pila.back());
                pila.pop_back();
            }
            pila.push_back(i);
        }
        else if (i[0]=='(')
        {
            pila.push_back(i);
        }
        else if (i[0]==')')
        {
            while (!pila.empty()
                    && !((pila.back()[0])=='('))
            {
                expresionPostfija.push_back(pila.back());
                pila.pop_back();
            }
            pila.pop_back();
        }
        
    }
    while (!pila.empty())
    {
        expresionPostfija.push_back(pila.back());
        pila.pop_back();
    }
    
    for (auto &&i : expresionPostfija)
    {
        cout<<i<<' ';
    }
    for (auto &&i : expresionPostfija)
    {
        if(i == "+")
        {
            int a = stoi(pila.back());
            pila.pop_back();
            int b = stoi(pila.back());
            pila.pop_back();
            pila.push_back(to_string(a+b));
        }
        else if(i == "-")
        {
            int a = stoi(pila.back());
            pila.pop_back();
            int b = stoi(pila.back());
            pila.pop_back();
            pila.push_back(to_string(b-a));
        }
        else if(i == "*")
        {
            int a = stoi(pila.back());
            pila.pop_back();
            int b = stoi(pila.back());
            pila.pop_back();
            pila.push_back(to_string(a*b));
        }
        else if(i == "/")
        {
            int a = stoi(pila.back());
            pila.pop_back();
            int b = stoi(pila.back());
            pila.pop_back();
            pila.push_back(to_string(b/a));
        }
        else
            pila.push_back(i);
    }
    cout<<"Resultado: "<<pila[0]<<endl;
    
    expresionInfija.clear();
}

int main(int n, char *pal[])
{
    f=stdin; //entrada estandar del teclado
    if(n==2) //si se especifico un archivo de lectura
    {
        f=fopen(pal[1],"rt"); //lectura modo texto
        if(f==NULL)
            f=stdin;
    }
    if(f==stdin) //la lectura sera desde la entrada estandar
    printf("Ingrese texto ........ termine con Ctrl z \n");
    
    token = scanner();
    Program();
    if (syntaxError)
    {
        cout<<"Error de sintaxis."<<endl;
    }
    
    if(f !=stdin) // si la entrada fue de un archivo
        fclose(f); // entonces cerrar el archivo.
    return 0;
}

int scanner()
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
    
    if((c==';')||(c==',')||(c=='#')||(c=='(')||(c==')')||(c=='[')||(c==']')||(c=='{')||(c=='}'))
    {
        lexema[0]=c; lexema[1]=0;
        return c;
    }

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
        return PRODUCTO;
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
        return MAS;
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
        return MENOS;
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
            return DIVISION;
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
}

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
    if(strcmp(lexema,"BEGIN")==0) return BEGIN;
    if(strcmp(lexema,"END")==0) return END;

    return -1;
}


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;


bool isLetter (char letter)
{
    return (letter>='a'&&letter<='z')|(letter>='A'&&letter<='Z');
}

bool isDigit (char digit)
{
    return digit>='0'&&digit<='9';
}



int stateMachine(string word, const vector< vector<int> > &table, int numStates, const vector<string> &transitions)
{
    int state = 1;
    int input = 0;
    char symbol;
    int idx = -1;
    int numTransitions = transitions.size();
    do
    {
        ++idx;
        --state;
        input = -1;
        symbol = word[idx];
        for (int i = 0; i < numTransitions; ++i)
        {
            if (transitions[i]=="letter" && isLetter(symbol))
                input = i;
            else if (transitions[i]=="digit" && isDigit(symbol))
                input = i;
            else if (transitions[i]=="void" && !symbol)
                input = i;
            else if(symbol == transitions[i][0])
                input = i;
        }
        if (input == -1)
        {
            cout<<"Error, char desconocido"<<endl;
            return 1;
        }
        state = table[state][input];
        if (state == -1)
        {
            cout<<"Error"<<endl;
            return 1;
        }
    } while (state != 0);
    
    cout<<"Identificador aceptado"<<endl;
    return 0;
}

int main ()
{
    vector< vector<int> > table;
    int numStates = 0;
    vector<string> transitions;
    ifstream txt("table.txt");
    string line;
    string temp;
    //Leyendo las transisiones de la primera linea
    getline(txt,line);
    for (int i = 2; i < line.length() ; ++i)
    {
        if(line[i]==' ')
        {
            transitions.push_back(temp);
            temp.clear();
            continue;
        }
        temp.push_back(line[i]);
    }
    transitions.push_back(temp);

    while (getline(txt,line))
    {
        string::iterator it = line.begin();
        //Adelantando el 1er ' '
        while (*it != ' ')
        {
            ++it;
        }
        ++it;
        
        string temp;
        table.resize(numStates+1);

        for (; it != line.end(); ++it)
        {
            if(*it == ' ')
            {
                table[numStates].push_back( stoi(temp) );
                temp.clear();
                continue;
            }
            temp.push_back(*it);
        }
        table[numStates].push_back( stoi(temp) );
        
        ++numStates;
    }
    txt.close();
    string word;
    cout<<"Ingrese una palabra: ";
    cin>>word;
    stateMachine(word, table, numStates, transitions);
    return 0;
}

#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class State
{
    public:
        //set: vector de los estados que representa. Ej. {1,4,2}, {1}, etc
        vector<int> set;
        //key: estado real que se usará en la tabla de transiciones
        int key;
        State(int state,int key)
        {
            this -> key = key;
            set.push_back(state);
        }
        State(vector<int> set, int key)
        {
            this -> set = set;
            this -> key = key;
        }
};

class Automata
{
    public:
        vector<State> states;
        int noStates;
        map< int, map < string, vector<int> > > table;
        int noTransitions;
        vector<int> finalStates;
        int noFinalStates;
        vector<string> alphabet;
        int noAlphabet;
        string fileName;
        Automata(){noStates=0;}
        Automata(string fileName)
        {
            noStates = 0;
            this -> fileName = fileName;
        }
        void fill()
        {
            string ignore;
            cin>>ignore;
            cin>>noStates;
            for (int i = 0; i < noStates; ++i)
            {
                int x;
                cin>>x;
                //Nos permite inputs de estados que no esten necesariamente en orden
                //Ej. 6 2 123 3 4 se guardaria como 0 1 2 3 4
                states.push_back(State(x,i));
            }
            
            cin>>ignore;
            cin>>noFinalStates;
            for (int i = 0; i < noFinalStates; ++i)
            {
                int x;
                cin>>x;
                finalStates.push_back(x);
            }
            cin>>ignore;
            cin>>noAlphabet;
            for (int i = 0; i < noAlphabet; ++i)
            {
                string x;
                cin>>x;
                alphabet.push_back(x);
            }
            
            cin>>ignore;
            cin>>noTransitions;
            for (int i = 0; i < noTransitions; ++i)
            {
                int a;
                int b;
                string t;
                cin>> a >> t >> b;
                table[a][t].push_back(b);
            }
        }
        vector<int> getE_closure(vector<int> R)
        {
            //Verificando que los elementos en R existan en el vector de estados del automata
            for (auto &&i : R)
            {
                bool exists = false;
                for (auto &&j : states)
                {
                    if (i == j.key)
                    {
                        exists = true;
                        break;
                    }
                }
                if (!exists)
                {
                    cout<<"There's an element in R that doesn't exist in states."<<endl;
                    return vector<int>();
                }
            }
            // tempStack: pila temporal que nos ayuda en el algoritmo
            // para calcular E_closure
            vector<int> tempStack;
            for (auto &&i : R)
            {
                tempStack.push_back(i);
            }
            // E_closure: La clausura en vacio de un conjunto de estados
            vector<int> E_closure;
            for (auto &&i : R)
            {
                E_closure.push_back(i);
            }

            while (!tempStack.empty())
            {
                int r = tempStack.back();
                tempStack.pop_back();
                for (auto &&s : table[r]["-1"])
                {
                    // verificando que s no este en E_closure
                    bool exists = false;
                    for (auto &&k : E_closure)
                    {
                        if (k == s)
                        {
                            exists = true;
                            break;
                        }
                    }
                    // si no esta lo agregamos a E_closure y lo apilamos
                    if (!exists)
                    {
                        E_closure.push_back(s);
                        tempStack.push_back(s);
                    }
                }
            }
            return E_closure;
        }
        Automata getDFA()
        {
            // Inicializar D_est con E_clausura(s0) y considerarlo no marcado
            // Mientras exista un estado no marcado R en D_est Hacer
            //    a. Marcar R
            //    b. Por cada símbolo de entrada x, Hacer
            //        i. U <- E-clausura(move(R,x))
            //        ii. Si U no pertenece a D_est entonces
            //            Agregar U a D_est como un estado no marcado
            //        iii. D_tran(R,x) := U
            Automata dfa;
            // Inicializamos el 1er estado de dfa con la clausura_e del estado 0
            // se supone que el estado inicial siempre sera 0
            dfa.states.push_back(State(this->getE_closure(vector<int>{0}), 0));
            // si un estado pertenece a unmarked, significa que no esta marcado
            vector<State> unmarked;
            unmarked.push_back(dfa.states[0]);
            // counter: nos indica la clave del estado en dfa.states
            // para poder agregar estados en orden creciente Ej. 0 1 2 3 ...
            int counter = 1;
            while (!unmarked.empty())
            {
                State R = unmarked.back();
                unmarked.pop_back();
                for (auto &&i : this->alphabet)
                {
                    //move: move(R,x)
                    vector<int> move;
                    for (auto &&j : R.set)
                    {
                        if(!table[j][i].empty())
                        {
                            for (auto &&k : table[j][i])
                            {
                                //Verificando que no se encuentre en el vector move para no agregar mas de 1 vez
                                bool exists = false;
                                for (auto &&l : move)
                                {
                                    if (l == k)
                                    {
                                        exists = true;
                                        break;
                                    }
                                }
                                if(!exists)
                                    move.push_back(k);
                            }
                        }
                    }
                    vector<int> U = this->getE_closure(move);
                    //uState: estado del estado U dentro de dfa.states
                    int uState = 0;
                    bool uExists = false;
                    for (auto &&j : dfa.states)
                    {
                        if(j.set == U)
                        {
                            uExists = true;
                            break;
                        }
                        ++uState;
                    }
                    //Si U no existe dentro de dfa.states, lo agrega a dfa.states sin marcar
                    if (!uExists)
                    {
                        uState = counter;
                        dfa.states.push_back(State(U,counter));
                        for (auto &&j : U)
                        {
                            bool isFinal = false;
                            for (auto &&k : this->finalStates)
                            {
                                if (j == k)
                                {
                                    isFinal = true;
                                    break;
                                }
                            }
                            if (isFinal)
                            {
                                dfa.finalStates.push_back(uState);
                            }
                        }
                        ++counter;
                        unmarked.push_back(dfa.states[uState]);
                    }
                    dfa.table[R.key][i].push_back(uState);
                }
            }
            return dfa;
        }
        void print()
        {
            cout<<"Estados:"<<endl;
            for (auto &&i : states)
            {
                cout<<i.key<<" = { ";
                for (auto &&j : i.set)
                {
                    cout<<j<<' ';
                }
                cout<<'}'<<endl;
            }
            cout<<"Estados de Aceptacion"<<endl;
            for (auto &&i : finalStates)
            {
                cout<<i<<' ';
            }
            cout<<endl;
            cout<<"Transiciones a -> b: c(del estado a al estado b con c): "<<endl;
            for (auto &&i : table)
            {
                for (auto &&j : i.second)
                {
                    for (auto &&k : j.second)
                    {
                        cout<<i.first<<" -> "<<k<<": "<<j.first<<endl;
                    }
                }
            }
        }
        void generateDotFile()
        {
            string txt = "";
            txt.append("\tnode [shape = doublecircle]; ");
            for (auto &&i : finalStates)
            {
                txt.append(to_string(i)+" ");
            }
            txt.append(";\n");
            txt.append("\tnode [shape = circle];\n");
            for (auto &&i : table)
            {
                for (auto &&j : i.second)
                {
                    for (auto &&k : j.second)
                    {
                        txt.append("\t"+to_string(i.first)+" -> "+to_string(k)+" [ label = \""+j.first+"\" ];\n");
                    }
                }
            }
            ofstream file;
            file.open(fileName);
            if (!file.is_open())
            {
                cout<<"Error al abrir el archivo."<<endl;
                return;
            }
            file<<"digraph finite_state_machine {\n";
            file<<"\trankdir=LR;\n";
            file<<"\tsize=\"8.5\"\n";
            file<<txt;
            file<<"}\n";
            file.close();
            system(("dot -Tpng -O "+fileName).c_str());
        }
        void show()
        {
            system(("eog "+fileName+".png").c_str());
        }
};

int main()
{
    Automata nfa("nfa.txt");
    nfa.fill();
    //nfa.print();
    nfa.generateDotFile();
    nfa.show();
    //cout<<"--------------------\n";
    Automata dfa = nfa.getDFA();
    dfa.fileName = "dfa.txt";
    dfa.generateDotFile();
    dfa.print();
    dfa.show();
    return 0;
}
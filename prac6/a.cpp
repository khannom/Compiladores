#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    ifstream text("in.txt");
    int states;
    cin >> states;
    vector<vector<string>> automata;
    automata.reserve(states);
    for (int i = 0; i < states; i++)
    {
        for (int j = 0; j < states; j++)
        {
            automata[i].push_back("");
        }
    }

    int transitions;
    cin >> transitions;

    for (int i = 0; i < transitions; i++)
    {
        int a;
        int b;
        string t;
        cin>> a >> t >> b;
        automata[a][b] = t;
    }
    

    int r;
    cin >> r;

    vector<int> pila;
    pila.push_back(r);
    vector<int> clausura;
    clausura.push_back(r);

    while (!pila.empty())
    {
        int temp = pila.back();
        pila.pop_back();
        for (int s = 0; s < states; s++)
        {
            if (automata[temp][s] == "-1")
            {
                bool esta = false;
                for (auto &&k : clausura)
                {
                    if (k == s)
                    {
                        esta = true;
                        break;
                    }
                }
                if (!esta)
                {
                    clausura.push_back(s);
                    pila.push_back(s);
                }
            }
        }
    }


    

    for (auto &&i : clausura)
    {
        cout << i << endl;
    }

    text.close();
    return 0;
}
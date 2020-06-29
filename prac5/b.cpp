#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    vector<string> palabs;
    string linea;
    getline(cin, linea);
    string temp;
    for (auto &&i : linea)
    {
        if(i!=' ')
        {
            temp.push_back(i);
        }
        else
        {
            palabs.push_back(temp);
            temp.clear();
        }
    }
    palabs.push_back(temp);
    vector<string> pila;
    for (auto &&i : palabs)
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
    cout<<"resultado: "<<pila[0]<<endl;
    return 0;
}
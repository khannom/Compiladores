#include<fstream>
#include<vector>
#include<string>
#include<iostream>

using namespace std;

int main()
{
    /*char xd;
    ifstream txt("fuente.txt");
    while (txt>>noskipws>>xd)
    {
        cout<<xd;
    }*/
    vector< vector<int> > table;    
    string state = "10";
    table.reserve(table.size()+1);
    table[0].push_back(stoi(state));
    cout<<table[0][0]<<endl;
    
    

    return 0;
}
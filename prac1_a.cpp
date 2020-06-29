#include <iostream>
#include <string>

using namespace std;

int main ()
{
    string linea;
    cout<<"Ingrese una cadena: ";
    getline(cin,linea);
    for (int i = 0; i < linea.length(); ++i)
    {
        cout<<linea[i]<<endl;
    }
    
    return 0;
}
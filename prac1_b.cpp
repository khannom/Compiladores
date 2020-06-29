#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main ()
{
    ifstream MyFile("test.txt");
    string myText;
    if(MyFile.is_open()){
        while (getline(MyFile, myText)) {
            for (int i = 0; i < myText.length(); ++i)
            {
                cout<<myText[i]<<endl;
            }
            
        }
        cout<<endl;
        MyFile.close();
    }
    else
    {
        cout<<"Error al abrir el archivo.";
    }
    
    return 0;
}
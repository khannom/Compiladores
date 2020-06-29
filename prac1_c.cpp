#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void cifradoCesar(string fileName, int saltos)
{
    ifstream ReadFile(fileName);
    string str;
    string content;
    while (getline(ReadFile,str))
    {
        content.append(str+'\n');
    }
    ReadFile.close();
    ofstream WriteFile(fileName);
    saltos %= 26;
    if(WriteFile.is_open()){
        for (int i = 0; i < content.length(); ++i)
        {
            char newChar = content[i];
            if(newChar>='a' && newChar<='z')
            {
                newChar += saltos;
                if (newChar>'z')
                {
                        newChar -= 26;
                }
                WriteFile<<newChar;
            }
            else if (newChar>='A' && newChar<='Z')
            {
                newChar += saltos;
                if (newChar>'Z')
                {
                    newChar -= 26;
                }
                WriteFile<<newChar;
            }
            else
            {
                WriteFile<<newChar;
            }
        }
    }
    else
    {
        cout<<"Error al abrir el archivo.";
    }
    WriteFile.close();
}

void descifradoCesar(string fileName, int saltos)
{
    ifstream ReadFile(fileName);
    string str;
    string content;
    while (getline(ReadFile,str))
    {
        content.append(str+'\n');
    }
    ReadFile.close();
    ofstream WriteFile(fileName);
    saltos %= 26;
    if(WriteFile.is_open()){
        for (int i = 0; i < content.length(); ++i)
        {
            char newChar = content[i];
            if(newChar>='a' && newChar<='z')
            {
                newChar -= saltos;
                if (newChar<'a')
                {
                        newChar += 26;
                }
                WriteFile<<newChar;
            }
            else if (newChar>='A' && newChar<='Z')
            {
                newChar -= saltos;
                if (newChar<'A')
                {
                    newChar += 26;
                }
                WriteFile<<newChar;
            }
            else
            {
                WriteFile<<newChar;
            }
        }
    }
    else
    {
        cout<<"Error al abrir el archivo.";
    }
    WriteFile.close();
}


int main ()
{
    cifradoCesar("test.txt",3);
    descifradoCesar("test.txt",3);
    return 0;
}
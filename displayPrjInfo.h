#include <iostream>
#include <fstream>
using namespace std;
void displayProjectInfo()
{
    fstream newfile;
    newfile.open("Prj.txt", ios::in);
    if (newfile.is_open())
    {
        string projectInfo;
        while (getline(newfile, projectInfo))
        {
            cout << projectInfo << "\n";
        }
        newfile.close();
    }
}
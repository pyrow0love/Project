#ifndef DISPLAYALL_H
#define DISPLAYALL_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "definedFunction.h"
using namespace std;
void displayAllClass()
{
    vector<Student> classData; // vector to hold datas
    vector<string> headers = {"Group", "Full Name", "Student Id"};
    vector<int> maxLength(3, 0); // store max string length of each sections
    char delimiter = ',';
    string line;
    ifstream inputFile("group.txt"); // read file
    if (!inputFile)
    {
        cerr << "Failed to open the file." << endl;
    }
    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the first line read
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        Student student;
        string group;
        getline(iss, group, delimiter);
        student.groupNumber = stoi(group);
        int mark = 0; // mark value for groupNumber to use in createMaxLength func
        createMaxLength(group, mark, maxLength, headers);
        getline(iss, student.name, delimiter);
        mark = 1; // mark value for groupName to use in createMaxLength func

        createMaxLength(student.name, mark, maxLength, headers);
        getline(iss, student.studentId);
        mark = 2; // mark value for student Id to use in createMaxLength func
        createMaxLength(student.studentId, mark, maxLength, headers);
        classData.push_back(student);
    }
    inputFile.close();
    // display
    for (int x = 0; x < headers.size(); x++)
    {
        string spacing(abs(maxLength[x] - (int)headers[x].length()), ' '); // calculate the number of space
        cout << " | " << headers[x] + spacing;
    }
    cout << " |\n";
    for (int index = 0; index < classData.size(); index++)
    {
        string horizontalLine1(maxLength[0], '_');
        string horizontalLine2(maxLength[1], '_');
        string horizontalLine3(maxLength[2], '_');
        if (index == 0)
        {
            cout << " |_" << horizontalLine1 << "_|_" << horizontalLine2 << "_|_" << horizontalLine3 << "_| \n";
        }
        string currentGroupSpace(abs(maxLength[0] - (int)to_string(classData[index].groupNumber).length()), ' ');

        string currentnameSpace(abs(maxLength[1] - (int)classData[index].name.length()), ' ');    // calculate the number of space between the longest string name and the current string name
        string currentIdSpace(abs(maxLength[2] - (int)classData[index].studentId.length()), ' '); // calculate the number of space between the longest string name and the current string name
        cout << " | " << classData[index].groupNumber << currentGroupSpace
             << " | " + classData[index].name + currentnameSpace + " | " + classData[index].studentId + currentIdSpace + " |\n";
        cout << " |_" << horizontalLine1 << "_|_" << horizontalLine2 << "_|_" << horizontalLine3 << "_| \n";
    };
    classData.clear();
}
#endif // DISPLAYALL_H
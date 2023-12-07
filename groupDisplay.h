#ifndef GROUPDISPLAY_H
#define GROUPDISPLAY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "definedFunction.h"
using namespace std;
void displayGroup()
{
    vector<Student> groupInfo;
    vector<string> headers = {"Group", "Full Name", "Student Id"};
    vector<int> maxLength(3, 0); // store max string length of each sections
    char delimiter = ',';
    string line;
    int groupNum;
    bool found = false;
    cout << "Enter which group to display: ";
    cin >> groupNum;
    ifstream inputFile("group.txt"); // read file
    if (!inputFile)
    {
        cerr << "Failed to open the file." << endl;
    }
    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the first line
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string group;
        getline(iss, group, delimiter);
        if (stoi(group) == groupNum)
        {
            Student groupStudent;
            groupStudent.groupNumber = stoi(group);
            int mark = 0;
            createMaxLength(group, mark, maxLength, headers);

            getline(iss, groupStudent.name, delimiter);
            mark = 1;
            createMaxLength(groupStudent.name, mark, maxLength, headers);

            getline(iss, groupStudent.studentId);
            mark = 2;
            createMaxLength(groupStudent.studentId, mark, maxLength, headers);
            groupInfo.push_back(groupStudent);
            found = true;
        }
        else
        {
            continue;
        }
    }
    inputFile.close();
    if (found)
    {
        for (int x = 0; x < headers.size(); x++) // display header with spacing
        {
            string spacing(abs(maxLength[x] - (int)headers[x].length()), ' ');
            cout << " | " << headers[x] + spacing;
        }
        cout << " |\n";

        for (int index = 0; index < groupInfo.size(); index++)
        {

            string horizontalLine1(maxLength[0], '_');
            string horizontalLine2(maxLength[1], '_');
            string horizontalLine3(maxLength[2], '_');
            if (index == 0)
            {
                cout << " |_" << horizontalLine1 << "_|_" << horizontalLine2 << "_|_" << horizontalLine3 << "_| \n";
            }
            string currentGroupSpace(abs(maxLength[0] - (int)to_string(groupInfo[index].groupNumber).length()), ' ');
            string currentnameSpace(abs(maxLength[1] - (int)groupInfo[index].name.length()), ' ');    // calculate the number of space between the longest string name and the current string name
            string currentIdSpace(abs(maxLength[2] - (int)groupInfo[index].studentId.length()), ' '); // calculate the number of space between the longest string name and the current string name
            cout << " | " << groupInfo[index].groupNumber << currentGroupSpace
                 << " | " + groupInfo[index].name + currentnameSpace + " | " + groupInfo[index].studentId + currentIdSpace + " |\n";
            cout << " |_" << horizontalLine1 << "_|_" << horizontalLine2 << "_|_" << horizontalLine3 << "_| \n";
        }
    }
    else
    {
        cout << "No group available.\n";
    }
    groupInfo.clear();
}
#endif // GROUPDISPLAY_H
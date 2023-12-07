#ifndef CREATEGROUPFILE_H
#define CREATEGROUPFILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "definedFunction.h"
using namespace std;
// datatype
string trimString(string &str);
bool checkExistStudent(vector<Student> &groupData, string id, int size);
bool checkExistGroup(int groupNum, vector<Student> &groupData);
bool checkValidId(string id);
void selectionSort(vector<Student> &groupData, int size);
int numberOfGroups, peopleInAGroup;
int groupNum;
void userInputGroupInfo()
{
    vector<Student> groupData;
    cout << "Input the number of groups: ";
    cin >> numberOfGroups;
    for (int i = 0; i < numberOfGroups; i++)
    {
        do
        {
            cout << "Input the group number: ";
            cin >> groupNum;
        } while (groupNum < 1 || checkExistGroup(groupNum, groupData));
        do
        {
            cout << "Input the number of people in this group: ";
            cin >> peopleInAGroup;
        } while (peopleInAGroup < 1);

        for (int i = 0; i < peopleInAGroup; i++)
        {
            Student member;
            do
            {
                cout << "Enter student ID(numbers) #" << i + 1 << " : ";
                cin >> member.studentId;
                trimString(member.studentId);                                                                             // trim spaces
            } while (checkExistStudent(groupData, member.studentId, groupData.size()) || checkValidId(member.studentId)); // check Id if student existed before and check id valid

            member.groupNumber = groupNum;
            cin.sync(); // delete key buffer character
            cout << "Enter student name #" << i + 1 << " : ";
            getline(cin, member.name);
            trimString(member.name); // trim spaces
            groupData.push_back(member);
        }
    }
    selectionSort(groupData, groupData.size()); // sort group in order
    // Wrtie to file
    ofstream writeFile("group.txt");
    if (!writeFile)
    {
        cerr << "Error writing to file: " << endl;
    }
    writeFile << "Group,Full name,Student Id" << endl;
    for (size_t i = 0; i < groupData.size(); i++)
    {
        writeFile << groupData[i].groupNumber << "," + groupData[i].name + "," + groupData[i].studentId << endl;
        writeFile.flush();
    }
    writeFile.close();
    groupData.clear();
}
string trimString(string &str)
{
    string whiteSpaces = " \n\r\t\f\v"; // all types of possible spaces to remove
    // Remove leading whitespace
    int first_non_space = str.find_first_not_of(whiteSpaces);
    str.erase(0, first_non_space);

    // Remove trailing whitespace
    int last_non_space = str.find_last_not_of(whiteSpaces);
    str.erase(last_non_space + 1);
    return str;
}
bool checkExistStudent(vector<Student> &groupData, string id, int size)
{
    bool check = false;
    for (int i = 0; i < size; i++)
    {
        if (groupData[i].studentId == id)
        {
            cout << "Student already exist!" << endl;
            check = true;
            break;
        }
    }
    return check;
}
bool checkExistGroup(int groupNum, vector<Student> &groupData)
{
    bool check = false;
    for (int i = 0; i < groupData.size(); i++)
    {
        if (groupData[i].groupNumber == groupNum)
        {
            cout << "Group already exist!" << endl;
            check = true;
            break;
        }
    }
    return check;
}
void selectionSort(vector<Student> &groupData, int size)
{
    int startScan, minIndex, minValue;

    for (startScan = 0; startScan < (size - 1); startScan++)
    {
        minIndex = startScan;
        minValue = groupData[startScan].groupNumber;

        for (int index = startScan + 1; index < size; index++)
        {
            if (groupData[index].groupNumber < minValue)
            {
                minValue = groupData[index].groupNumber;
                minIndex = index;
            }
        }
        Student temp = groupData[minIndex];
        groupData[minIndex] = groupData[startScan];
        groupData[startScan] = temp;
    }
}
bool checkValidId(string id)
{
    bool check = false;
    for (int i = 0; i < id.length(); i++)
    {
        if (!isdigit(id[i]))
        {
            check = true;
        }
    }
    if (check == true)
    {
        cout << "Invalid ID number!" << endl;
    }
    return check;
}
#endif // CREATEGROUPFILE_H

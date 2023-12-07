#ifndef USER_SUBMIT_PROJECT_H
#define USER_SUBMIT_PROJECT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "definedFunction.h"
using namespace std;

void userSubmitProject()
{
    chrono::system_clock::time_point timePoint; // create a variable to hold time
    string submit, prjLine, deadline;
    tm tm1 = {};
    tm tm2 = {}; // Parse the date strings into system_clock::time_point objects
    int numOfPrj = get_Num_Of_Prj();
    int numOfGroup = get_Num_Of_Grp();
    int groupNum,
        projectNum; // hold project and group number
    do
    {
        cout << "Enter your group number: ";
        cin >> groupNum;
        while (cin.fail()) // check valid input if its int
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer: ";
            cin >> groupNum;
        }
    } while (checkValid_Grp_Or_Prj(numOfGroup, groupNum));
    do
    {
        cout << "Enter project number you want to submit: ";
        cin >> projectNum;
        while (cin.fail()) // check valid input if its int
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer: ";
            cin >> projectNum;
        }
    } while (checkValid_Grp_Or_Prj(numOfPrj, projectNum));
    int count = 0;
    ifstream readPrj("Prj.txt");
    if (!readPrj)
    {
        cerr << "Error read file" << endl;
    }
    if (readPrj)
    {
        while (getline(readPrj, prjLine))
        {
            if (prjLine.find("Deadline:") != string::npos) // find deadline of the input project
            {
                count += 1;
                if (count == projectNum)
                {
                    // Extract deadline
                    deadline = prjLine.substr(prjLine.find(":") + 2);
                }
            }
        }
    }
    readPrj.close();
    cout << "The deadline of the project is: " << deadline << endl;
    istringstream stream(deadline);
    stream >> get_time(&tm2, "%d/%m/%Y");
    auto prjDeadLine = chrono::system_clock::from_time_t(mktime(&tm2)); // create a comparable time variable

    vector<vector<string>> submitStatus(numOfGroup, vector<string>(numOfPrj)); // initiate vector to hold submit status
    readSubmitStatus(submitStatus, numOfGroup, numOfPrj);                      // get data from submit file and put in vector

    int option;
    do
    {
        cout << "Choose your option:" << endl
             << "1) Get the current date as submit time." << endl
             << "2) Input submit time (DD/MM/YYYY)." << endl;
    } while (!(cin >> option) || option < 1 || option > 2);

    if (option == 1) // if choose 1
    {
        auto submitDate = chrono::system_clock::now();
        timePoint = submitDate;
    }
    if (option == 2) // if choose 2
    {
        cout << "input submit time (DD/MM/YYYY): ";
        cin >> submit;
        istringstream iss(submit);
        iss >> get_time(&tm1, "%d/%m/%Y");
        auto submitDate = chrono::system_clock::from_time_t(mktime(&tm1)); //  create a comparable time variable
        timePoint = submitDate;
    }
    // compare time
    if (timePoint <= prjDeadLine)
    {
        submitStatus[groupNum - 1][projectNum - 1] = "On Time";
        cout << "On time submission!" << endl;
    }
    if (timePoint > prjDeadLine)
    {
        submitStatus[groupNum - 1][projectNum - 1] = "Late";
        cout << "Late submission!" << endl;
    }
    writeSubmitStatus(numOfPrj, numOfGroup, submitStatus); // write to file
    submitStatus.clear();                                  // clear vector
}
#endif // USER_SUBMIT_PROJECT_H
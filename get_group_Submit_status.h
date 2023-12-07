#ifndef GET_GROUP_SUBMIT_STATUS_H
#define GET_GROUP_SUBMIT_STATUS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "definedFunction.h"
using namespace std;

void get_Group_Submit_Status()
{
    int numGroup = get_Num_Of_Grp();
    int numPrj = get_Num_Of_Prj();
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
    } while (checkValid_Grp_Or_Prj(numGroup, groupNum));
    vector<vector<string>> submitStatus(numGroup, vector<string>(numPrj));
    readSubmitStatus(submitStatus, numGroup, numPrj);
    cout << "Submission status of group #" << groupNum << endl;
    for (int i = 0; i < numPrj; i++)
    {
        cout << "Project #" << i + 1 << ": " << submitStatus[groupNum - 1][i] << endl;
    }
}
#endif // GET_GROUP_SUBMIT_STATUS_H
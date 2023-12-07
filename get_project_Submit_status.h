#ifndef GET_PROJECT_SUBMIT_STATUS_H
#define GET_PROJECT_SUBMIT_STATUS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "definedFunction.h"
using namespace std;

void get_Project_Submit_Status()
{
    int numGroup = get_Num_Of_Grp();
    int numPrj = get_Num_Of_Prj();
    int projectNum; // hold project and group number
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
    } while (checkValid_Grp_Or_Prj(numPrj, projectNum));
    vector<vector<string>> submitStatus(numGroup, vector<string>(numPrj));
    readSubmitStatus(submitStatus, numGroup, numPrj);
    cout << "Submission status of project #" << projectNum << endl;
    for (int i = 0; i < numGroup; i++)
    {
        cout << "Group #" << i + 1 << ": " << submitStatus[i][projectNum - 1] << endl;
    }
}
#endif // GET_PROJECT_SUBMIT_STATUS_H
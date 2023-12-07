#ifndef INCOMPLETE_GRP_H
#define INCOMPLETE_GRP_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "definedFunction.h"
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
using namespace std;

void find_Incomplete_Grps()
{
    int numGroup = get_Num_Of_Grp();
    int numPrj = get_Num_Of_Prj();
    auto currentDate = chrono::system_clock::now(); // get current time variable
    tm tm2 = {};                                    // Parse the date strings into system_clock::time_point objects
    vector<string> deadLineDates;
    string prjLine;
    ifstream readPrj("Prj.txt");
    if (!readPrj)
    {
        cerr << "Error read file" << endl;
    }
    if (readPrj)
    {
        while (getline(readPrj, prjLine))
        {
            if (prjLine.find("Deadline:") != string::npos)
            {

                // Extract deadline
                string deadline = prjLine.substr(prjLine.find(":") + 2);
                deadLineDates.push_back(deadline); // get all deadLines of prj
            }
        }
    }
    readPrj.close();
    vector<vector<string>> submitStatus(numGroup, vector<string>(numPrj)); // initiate 2d vector
    readSubmitStatus(submitStatus, numGroup, numPrj);
    cout << "_________________________________________" << endl;
    cout << "Groups that incomplete:\n";

    for (int j = 0; j < deadLineDates.size(); j++)
    {
        bool flag = false;
        cout << "Project #" << j + 1 << ": ";
        for (int i = 0; i < numGroup; i++)
        {
            istringstream iss(deadLineDates[j]);
            iss >> get_time(&tm2, "%d/%m/%Y");
            auto deadline = chrono::system_clock::from_time_t(mktime(&tm2)); //  create a comparable time variable
            if (currentDate > deadline && submitStatus[i][j] == "Not Yet Submitted")
            {
                if (flag)
                {
                    cout << ", ";
                }
                cout << "Group " << i + 1;
                flag = true;
            }
        }
        cout << "\n";
    }
    submitStatus.clear();
}
#endif // INCOMPLETE_GRP_H
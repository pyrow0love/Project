#ifndef ONTIMESUBMIT_H
#define ONTIMESUBMIT_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "definedFunction.h"
using namespace std;
void find_On_Time_Grps()
{
    int numGroup = get_Num_Of_Grp();
    int numPrj = get_Num_Of_Prj();
    vector<vector<string>> submitStatus(numGroup, vector<string>(numPrj)); // initiate 2d vector
    readSubmitStatus(submitStatus, numGroup, numPrj);
    cout << "_________________________________________" << endl;
    cout << "Group submit projects On Time\n";

    for (int j = 0; j < numPrj; j++)
    {
        bool flag = false;
        cout << "project #" << j + 1 << ": ";
        for (int i = 0; i < numGroup; i++)
        {
            if (submitStatus[i][j] == "On Time")
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
#endif // ONTIMESUBMIT_H
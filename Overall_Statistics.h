#ifndef OVERALL_STATISTICS_H
#define OVERALL_STATISTICS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "definedFunction.h"
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <string>
#include <regex>
using namespace std;

void overallStatistics()
{
    regex pattern("\\d{1,2}/\\d{1,2}/\\d{4}");  // check input date format
    chrono::system_clock::time_point timePoint; // create a variable to hold user time
    string submit, prjLine;
    tm tm1 = {};
    tm tm2 = {}; // Parse the date strings into system_clock::time_point objects
    int option;
    vector<int> satisfiedProject;
    do
    {
        cout << "Choose your option:" << endl
             << "1) Get statistics from beginning of course to the current date." << endl
             << "2) Get statistics from beginning of course to user input time (DD/MM/YYYY)." << endl;
    } while (!(cin >> option) || option < 1 || option > 2);

    if (option == 1) // if choose 1
    {
        auto submitDate = chrono::system_clock::now(); // get current time variable
        timePoint = submitDate;
    }
    if (option == 2) // if choose 2
    {
        do
        {
            cout << "input submit time (DD/MM/YYYY): ";
            cin >> submit;
        } while (!regex_match(submit, pattern));
        istringstream iss(submit);
        iss >> get_time(&tm1, "%d/%m/%Y");
        auto submitDate = chrono::system_clock::from_time_t(mktime(&tm1)); //  create a comparable time variable
        timePoint = submitDate;
    }

    ifstream readPrj("Prj.txt");
    if (!readPrj)
    {
        cerr << "Error read file" << endl;
    }
    if (readPrj)
    {
        int projectnumber = 0;
        while (getline(readPrj, prjLine))
        {
            if (prjLine.find("Deadline:") != string::npos) // search for deadline dates of every project
            {
                projectnumber++;
                // Extract deadline
                string deadline = prjLine.substr(prjLine.find(":") + 2);
                istringstream iss(deadline);
                iss >> get_time(&tm2, "%d/%m/%Y");
                auto comparableDeadline = chrono::system_clock::from_time_t(mktime(&tm2)); //  create a comparable time variable
                if (comparableDeadline <= timePoint)
                {
                    satisfiedProject.push_back(projectnumber); // add project fit the user timepoint
                }
            }
        }
    }
    readPrj.close();
    if (satisfiedProject.size() > 0)
    {
        int numberOfGroup = get_Num_Of_Grp();
        int numberOfPrj = get_Num_Of_Prj();
        vector<int> maxChar(numberOfPrj + 1, 0);                                                 // create vector to hold max character for each element
        vector<vector<string>> submitStatus(numberOfGroup + 1, vector<string>(numberOfPrj + 1)); // initiate vector to hold status
        ifstream readSubmit("SubmissionStatus.txt");                                             // read the submission file to get the existed values
        if (!readSubmit)                                                                         // if file doesnt exist create new submit values
        {
            cerr << "\nError open file" << endl;
        }
        if (readSubmit)
        {
            int count = 0;
            string submitLine;
            while (getline(readSubmit, submitLine))
            {
                char delimiter = ',';
                istringstream ss(submitLine);
                for (int i = 0; i < numberOfPrj + 1; i++)
                {
                    getline(ss, submitStatus[count][i], delimiter); // read file to get all existed value and headers
                    if (count == 0)
                    {
                        maxChar[i] = submitStatus[count][i].length(); // assign longest of each element read
                    }

                    if (submitStatus[count][i].length() > maxChar[i])
                    {
                        maxChar[i] = submitStatus[count][i].length(); // find the longest elements
                    }
                }
                count++;
            }
        }
        readSubmit.close(); // close the file after reading it

        auto in_time_t = chrono::system_clock::to_time_t(timePoint);
        stringstream ss;
        ss << put_time(localtime(&in_time_t), "%d/%m/%Y"); // convert to stringstream format
        string seperateline;
        ofstream writefile("Overall statistics.txt"); // createFile
        cout << "STATISTICS OF SUBMISSION STATUS UP TO " << ss.str() << endl;
        writefile << "STATISTICS OF SUBMISSION STATUS UP TO " << ss.str() << endl; // write to file
        cout << endl;
        writefile << endl;
        for (int group = 0; group < numberOfGroup + 1; group++)
        {
            cout << "| ";
            writefile << "| "; // write file
            for (int j = 0; j < satisfiedProject.size(); j++)
            {
                if (j == 0)
                {
                    seperateline = "";
                    string spacing(maxChar[j] - (int)submitStatus[group][j].length(), ' ');
                    string Line(maxChar[j], '_');
                    seperateline = "|_" + Line + "_";
                    cout << submitStatus[group][j] + spacing << " | ";
                    writefile << submitStatus[group][j] + spacing << " | "; // write to file
                }
                int project = satisfiedProject[j];
                string Line(maxChar[project], '_');
                seperateline = seperateline + "|_" + Line + "_";
                if (j == satisfiedProject.size() - 1)
                {
                    seperateline += "|";
                }

                string spacing(maxChar[project] - (int)submitStatus[group][project].length(), ' ');
                cout << submitStatus[group][project] + spacing << " | ";
                writefile << submitStatus[group][project] + spacing << " | "; // write to file
            }
            cout << endl;
            writefile << endl;
            cout << seperateline;
            writefile << seperateline;
            cout << endl;
            writefile << endl;
        }

        writefile.close();
        submitStatus.clear();
        maxChar.clear();
    }
    else
    {
        cout << "\nNo project available in the given time!\n";
    }
    satisfiedProject.clear();
}
#endif // OVERALL_STATISTICS_H
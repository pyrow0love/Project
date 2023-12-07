#ifndef CREATEPROJECTS_H
#define CREATEPROJECTS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include "definedFunction.h"
using namespace std;
void createProjects()
{
    vector<Project> projectVector;
    int numProjects;
    cout << "Enter the number of projects: ";
    cin >> numProjects;

    cin.ignore(); // Consume the newline character left in the input buffer

    for (int i = 0; i < numProjects; i++)
    {
        Project project;

        do
        {
            cout << "Project " << i + 1 << " - Enter project number: ";
            if (cin >> project.projectNumber)
            {
                // Successful integer input
                break; // Exit the loop
            }
            else
            {
                cin.clear();                                         // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                cout << "Invalid input. Please enter a valid integer for project number.\n";
            }
        } while (true);
        cin.ignore(); // Consume the newline character left in the input buffer

        cout << "Project " << i + 1 << " - Enter project description: ";
        getline(cin, project.description);

        cout << "Project " << i + 1 << " - Enter project deadline(DD/MM/YYYY): ";
        getline(cin, project.deadline);

        projectVector.push_back(project);
    }

    // Write project information to "Prj.txt"
    ofstream file("Prj.txt");
    if (file.is_open())
    {
        for (const Project &project : projectVector)
        {
            file << "Project Number: " << project.projectNumber << "\n";
            file << "Description: " << project.description << "\n";
            file << "Deadline: " << project.deadline << "\n\n";
        }
        file.close();
        cout << "Project information has been saved to Prj.txt.\n";
    }
    else
    {
        cerr << "Unable to open Prj.txt for writing.\n";
    }
    int numGroups = get_Num_Of_Grp();
    vector<vector<string>> twoDVector(numGroups, vector<string>(numProjects));
    string myString = "Not Yet Submitted";
    for (int i = 0; i < numGroups; i++)
    {
        fill(twoDVector[i].begin(), twoDVector[i].end(), myString); // fill all vector value with not yet submitted
    }
    writeSubmitStatus(numProjects, numGroups, twoDVector); // create submit status file
    twoDVector.clear();
}
#endif // CREATEPROJECTS_H
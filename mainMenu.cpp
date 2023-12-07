#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>
#include "createGroupFile.h"
#include "groupDisplay.h"
#include "displayAll.h"
#include "displayPrjInfo.h"
#include "create_Projects.h"
#include "user_submit_project_func.h"
#include "get_group_Submit_status.h"
#include "get_project_Submit_status.h"
#include "Overall_Statistics.h"
#include "find_IncompleteGrp.h"
#include "find_OntimeSubmit.h"
using namespace std;
int main()
{
    int choice;
    int groupInfoChoice;
    char deadlineChoice;
    char statisticChoice;
    char submitStatusChoice;

    do
    {
        cout << "_____________________________\n";
        cout << "Project Submission of groups:\n";
        cout << "_____________________________\n";
        cout << "1. Group information\n";
        cout << "2. Project deadline declaration\n";
        cout << "3. Submit project\n";
        cout << "4. Statistic\n";
        cout << "5. Overall statistic\n";
        cout << "6. Find groups do not complete or submit on time\n";
        cout << "7. Exit\n";
        cout << "_____________________________\n";
        cout << "Enter your choice: ";
        cin >> choice;
        while (cin.fail()) // check valid input if its int
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer: ";
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
        {
            do
            {
                cout << "Group Information:\n";
                cout << "1) User input information of group\n";
                cout << "2) Display all class from last save\n";
                cout << "3) Display specified group from last save\n";
                cout << "4) Exit to main menu\n";
                cout << "Enter your choice: ";
                cin >> groupInfoChoice;
                while (cin.fail()) // check valid input
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter an integer: ";
                    cin >> groupInfoChoice;
                }
                switch (groupInfoChoice)
                {
                case 1:
                    userInputGroupInfo();
                    break;
                case 2:
                    displayAllClass();
                    break;
                case 3:
                    displayGroup();
                    break;
                case 4:
                    cout << "Returning to main menu ...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
                    break;
                }
            } while (groupInfoChoice != 4);
            break;
        }
        case 2:
        {
            do
            {
                cout << "Project Deadline Declaration:\n";
                cout << "a) Input\n";
                cout << "b) Display\n";
                cout << "c) Exit to main menu\n";
                cout << "Enter your choice: ";
                cin >> deadlineChoice;
                cin.ignore();
                if (tolower(deadlineChoice) == 'a')
                {
                    createProjects();
                }
                else if (tolower(deadlineChoice) == 'b')
                {
                    displayProjectInfo();
                }
                else if (tolower(deadlineChoice) == 'c')
                {
                    cout << "Returning to main menu ...\n";
                }
                else
                {
                    cout << "Invalid choice!\n";
                }
            } while (tolower(deadlineChoice) != 'c');
            break;
        }
        case 3:
        {
            userSubmitProject();
            break;
        }
        case 4:
        {
            do
            {
                cout << "Statistic:\n";
                cout << "a) State of submission of a project for groups\n";
                cout << "b) State of submission of all projects of a group\n";
                cout << "c) Exit to main menu\n";
                cout << "Enter your choice: ";
                cin >> statisticChoice;
                cin.ignore();
                if (tolower(statisticChoice) == 'a')
                {
                    get_Project_Submit_Status();
                }
                else if (tolower(statisticChoice) == 'b')
                {
                    get_Group_Submit_Status();
                }
                else if (tolower(statisticChoice) == 'c')
                {
                    cout << "Returning to main menu ...\n";
                }
                else
                {
                    cout << "Invalid choice!\n";
                }
            } while (tolower(statisticChoice) != 'c');
            break;
        }
        case 5:
        {
            overallStatistics();
            break;
        }
        case 6:
        {
            do
            {
                cout << "a) Groups do not complete\n";
                cout << "b) Groups submit on time\n";
                cout << "c) Exit to main menu\n";
                cout << "Enter your choice: ";
                cin >> submitStatusChoice;
                cin.ignore();
                if (tolower(submitStatusChoice) == 'a')
                {
                    find_Incomplete_Grps();
                }
                else if (tolower(submitStatusChoice) == 'b')
                {
                    find_On_Time_Grps();
                }
                else if (tolower(submitStatusChoice) == 'c')
                {
                    cout << "Returning to main menu ...\n";
                }
                else
                {
                    cout << "Invalid choice!\n";
                }
            } while (tolower(submitStatusChoice) != 'c');
            break;
        }
        case 7:
        {
            cout << "Exiting...\n";
            break;
        }
        default:
        {
            cout << "Invalid! Choice Out Of Range\n";
            break;
        }
        }
    } while (choice != 7);

    return 0;
}

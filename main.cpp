#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "Student.h"

using namespace std;

struct non_alpha {
    bool operator()(char c) {
        return !std::isalpha(c);
    }
};

bool validTest(string studentName, string gatorID) {
    bool idValid;
    bool nameValid;
    bool isValid;
    bool contains_non_alpha = find_if(studentName.begin(), studentName.end(), non_alpha()) != studentName.end();

    if (studentName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") == string::npos) {
        nameValid = true;
    } else {
        nameValid = false;
    }

    if (gatorID.length() == 8) {
        idValid = true;
    } else {
        idValid = false;
    }

    if (nameValid && idValid) {
        isValid = true;
    } else {
        isValid = false;
    }

    return isValid;
}


int main() {
    int numberOfCommands;
    string userInput;
    string studentNameOrID;
    Student student;

    cin >> numberOfCommands;
    cin >> userInput;

    for (int i = 0; i < numberOfCommands; i++) {
        if (userInput == "insert") {
            cin.ignore(); // Ignore newline left in the input buffer
            getline(cin, userInput);

            int startPos = userInput.find("\"");
            if (startPos != string::npos) {
                startPos++;

                int endPos = userInput.find("\"", startPos);

                if (endPos != string::npos) {
                    string studentName = userInput.substr(startPos, (endPos - startPos));

                    int gatorIDStart = userInput.find(" ", endPos + 1);
                    if (gatorIDStart != string::npos) {
                        string gatorID = userInput.substr(gatorIDStart + 1);

                        // Check if the input is valid before inserting
                        if (validTest(studentName, gatorID)) {
                            student.insert(studentName, gatorID);
                        }
                        else {
                            cout << "unsuccessful" << endl;
                        }
                    }
                }
            }
        }
        else if (userInput == "remove") {
            cin.ignore(); // Ignore newline left in the input buffer
            getline(cin, studentNameOrID);
            student.deleteStudent(studentNameOrID);
        }
        else if (userInput == "search") {
            cin.ignore(); // Ignore newline left in the input buffer
            getline(cin, studentNameOrID);
            studentNameOrID.erase(remove( studentNameOrID.begin(), studentNameOrID.end(), '\"' ),studentNameOrID.end());

            // Determine whether to search by name or GatorID
            if (isdigit(studentNameOrID[0])) {
                // Search by GatorID
                student.searchID(studentNameOrID);
            }
            else {
                // Search by name
                student.searchName(studentNameOrID);
            }
        }
        else if (userInput == "printInorder") {
            student.printInorder();
        }
        else if (userInput == "printPreorder") {
            student.printPreorder();
        }
        else if (userInput == "printPostorder") {
            student.printPostorder();
        }
        else if (userInput == "removeInorder") {
            int n;
            cin >> n;
            student.removeNthInorder(n);
        }

        else if (userInput == "printLevelCount") {
            student.printLevels();
        }
        else {
            cout << "Invalid command. Please try again." << endl;
        }

        cin >> userInput;
    }

    return 0;
}

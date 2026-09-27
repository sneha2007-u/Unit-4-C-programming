#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("students.txt");
    ofstream temporaryFile("students_temp.txt");

    if (!inputFile || !temporaryFile) {
        cerr << "Error: Could not open file(s).\n";
        return 1;
    }

    int targetRollNumber;
    double updatedMarks;

    cout << "Enter roll number to update: ";
    cin >> targetRollNumber;

    cout << "Enter updated marks: ";
    cin >> updatedMarks;

    string line;
    bool found = false;

    while (getline(inputFile, line)) {
        stringstream record(line);

        string rollText;
        string name;
        string marksText;

        if (getline(record, rollText, '|') &&
            getline(record, name, '|') &&
            getline(record, marksText)) {

            int rollNumber = stoi(rollText);

            if (rollNumber == targetRollNumber) {
                temporaryFile << rollNumber << '|'
                              << name << '|'
                              << updatedMarks << '\n';

                found = true;
            }
            else {
                temporaryFile << line << '\n';
            }
        }
    }

    inputFile.close();
    temporaryFile.close();

    if (!found) {
        remove("students_temp.txt");
        cout << "Student record not found. No update performed.\n";
        return 0;
    }

    if (remove("students.txt") != 0) {
        cerr << "Error: Could not remove old students.txt\n";
        return 1;
    }

    if (rename("students_temp.txt", "students.txt") != 0) {
        cerr << "Error: Could not rename temporary file.\n";
        return 1;
    }

    cout << "Student marks updated successfully.\n";

    return 0;
}

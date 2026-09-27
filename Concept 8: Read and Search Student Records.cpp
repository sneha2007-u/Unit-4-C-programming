#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("students.txt");

    if (!inputFile) {
        cerr << "Error: Could not open students.txt\n";
        return 1;
    }

    int targetRollNumber;

    cout << "Enter roll number to search: ";
    cin >> targetRollNumber;

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
            double marks = stod(marksText);

            if (rollNumber == targetRollNumber) {
                cout << "Record Found\n";
                cout << "Roll Number: " << rollNumber << '\n';
                cout << "Name: " << name << '\n';
                cout << "Marks: " << marks << '\n';

                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "Student record not found.\n";
    }

    return 0;
}

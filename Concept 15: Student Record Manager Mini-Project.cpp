#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

void addStudent() {
    ofstream outputFile("student_records.txt", ios::app);

    if (!outputFile) {
        cerr << "Error: Could not open student_records.txt\n";
        return;
    }

    int rollNumber;
    string name;
    double marks;

    cout << "Enter roll number: ";
    cin >> rollNumber;

    cout << "Enter name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Enter marks: ";
    cin >> marks;

    outputFile << rollNumber << '|' << name << '|' << marks << '\n';

    cout << "Record added successfully.\n";
}

void displayStudents() {
    ifstream inputFile("student_records.txt");

    if (!inputFile) {
        cout << "No student record file found.\n";
        return;
    }

    string line;

    cout << "\nRoll No.\tName\t\tMarks\n";
    cout << "----------------------------------------\n";

    while (getline(inputFile, line)) {
        stringstream record(line);

        string rollText;
        string name;
        string marksText;

        if (getline(record, rollText, '|') &&
            getline(record, name, '|') &&
            getline(record, marksText)) {

            cout << rollText << "\t\t"
                 << name << "\t\t"
                 << marksText << '\n';
        }
    }
}

void searchStudent() {
    ifstream inputFile("student_records.txt");

    if (!inputFile) {
        cout << "No student record file found.\n";
        return;
    }

    int targetRoll;

    cout << "Enter roll number to search: ";
    cin >> targetRoll;

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

            if (stoi(rollText) == targetRoll) {
                cout << "Record Found\n";
                cout << "Roll Number: " << rollText << '\n';
                cout << "Name: " << name << '\n';
                cout << "Marks: " << marksText << '\n';

                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }
}

void updateMarks() {
    ifstream inputFile("student_records.txt");
    ofstream temporaryFile("student_records_temp.txt");

    if (!inputFile || !temporaryFile) {
        cerr << "Error: Could not open record file(s).\n";
        return;
    }

    int targetRoll;
    double newMarks;

    cout << "Enter roll number to update: ";
    cin >> targetRoll;

    cout << "Enter new marks: ";
    cin >> newMarks;

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

            if (stoi(rollText) == targetRoll) {
                temporaryFile << rollText << '|'
                              << name << '|'
                              << newMarks << '\n';

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
        remove("student_records_temp.txt");
        cout << "Student not found. No changes made.\n";
        return;
    }

    if (remove("student_records.txt") != 0 ||
        rename("student_records_temp.txt", "student_records.txt") != 0) {

        cerr << "Error: Could not replace the record file.\n";
        return;
    }

    cout << "Marks updated successfully.\n";
}

int main() {
    int choice;

    do {
        cout << "\nStudent Record Manager\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Marks\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateMarks();
                break;

            case 0:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}

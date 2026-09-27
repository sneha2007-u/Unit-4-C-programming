#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main() {
    ofstream outputFile("students.txt", ios::app);

    if (!outputFile) {
        cerr << "Error: Could not open students.txt\n";
        return 1;
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

    cout << "Student record saved successfully.\n";

    return 0;
}

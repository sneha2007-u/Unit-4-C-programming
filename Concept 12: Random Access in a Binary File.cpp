#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

struct StudentRecord {
    int rollNumber;
    char name[30];
    float marks;
};

void addRecord(ofstream& file, int rollNumber, const char* name, float marks) {
    StudentRecord student{};

    student.rollNumber = rollNumber;
    strncpy(student.name, name, sizeof(student.name) - 1);
    student.marks = marks;

    file.write(
        reinterpret_cast<const char*>(&student),
        sizeof(student)
    );
}

int main() {

    {
        ofstream outputFile("records.dat", ios::binary | ios::trunc);

        if (!outputFile) {
            cerr << "Error: Could not create records.dat\n";
            return 1;
        }

        addRecord(outputFile, 101, "Amit", 85.5F);
        addRecord(outputFile, 102, "Neha", 91.0F);
        addRecord(outputFile, 103, "Ravi", 78.0F);
    }

    ifstream inputFile("records.dat", ios::binary);

    if (!inputFile) {
        cerr << "Error: Could not open records.dat\n";
        return 1;
    }

    int recordNumber;

    cout << "Enter record number to read (1 to 3): ";
    cin >> recordNumber;

    if (recordNumber < 1 || recordNumber > 3) {
        cerr << "Invalid record number.\n";
        return 1;
    }

    const streamoff offset =
        static_cast<streamoff>(recordNumber - 1) *
        static_cast<streamoff>(sizeof(StudentRecord));

    inputFile.seekg(offset, ios::beg);

    StudentRecord selectedStudent{};

    inputFile.read(
        reinterpret_cast<char*>(&selectedStudent),
        sizeof(selectedStudent)
    );

    if (!inputFile) {
        cerr << "Error: Could not read selected record.\n";
        return 1;
    }

    cout << "Roll Number: " << selectedStudent.rollNumber << '\n';
    cout << "Name: " << selectedStudent.name << '\n';
    cout << "Marks: " << selectedStudent.marks << '\n';

    return 0;
}

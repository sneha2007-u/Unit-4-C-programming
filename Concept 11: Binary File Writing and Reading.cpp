#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

struct StudentRecord {
    int rollNumber;
    char name[30];
    float marks;
};

int main() {
    StudentRecord student{};

    student.rollNumber = 101;
    strncpy(student.name, "Amit Patil", sizeof(student.name) - 1);
    student.marks = 85.5F;

    {
        ofstream outputFile("students.dat", ios::binary);

        if (!outputFile) {
            cerr << "Error: Could not create students.dat\n";
            return 1;
        }

        outputFile.write(
            reinterpret_cast<const char*>(&student),
            sizeof(student)
        );
    }

    StudentRecord readStudent{};

    {
        ifstream inputFile("students.dat", ios::binary);

        if (!inputFile) {
            cerr << "Error: Could not open students.dat\n";
            return 1;
        }

        inputFile.read(
            reinterpret_cast<char*>(&readStudent),
            sizeof(readStudent)
        );

        if (!inputFile) {
            cerr << "Error: Could not read record from students.dat\n";
            return 1;
        }
    }

    cout << "Roll Number: " << readStudent.rollNumber << '\n';
    cout << "Name: " << readStudent.name << '\n';
    cout << "Marks: " << readStudent.marks << '\n';

    return 0;
}

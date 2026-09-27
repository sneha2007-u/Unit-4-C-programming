#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("missing_file.txt");

    if (!inputFile.is_open()) {
        cerr << "Error: File could not be opened.\n";
        cerr << "Check whether missing_file.txt exists in the current folder.\n";
        return 1;
    }

    string line;

    while (getline(inputFile, line)) {
        cout << line << '\n';
    }

    if (inputFile.eof()) {
        cout << "End of file reached normally.\n";
    }
    else if (inputFile.bad()) {
        cerr << "A serious file I/O error occurred.\n";
    }
    else if (inputFile.fail()) {
        cerr << "A logical file read error occurred.\n";
    }

    return 0;
}

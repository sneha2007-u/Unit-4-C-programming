#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("message.txt");

    if (!inputFile) {
        cerr << "Error: Could not open message.txt\n";
        return 1;
    }

    string line;

    cout << "File Content:\n";

    while (getline(inputFile, line)) {
        cout << line << '\n';
    }

    inputFile.close();

    return 0;
}

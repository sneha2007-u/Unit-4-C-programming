#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ofstream outputFile("message.txt");

    if (!outputFile) {
        cerr << "Error: Could not create message.txt\n";
        return 1;
    }

    outputFile << "Welcome to C++ File Handling\n";
    outputFile << "This is the first line written to a file.\n";
    outputFile << "Files store data permanently.\n";

    outputFile.close();

    cout << "Data written successfully to message.txt\n";

    return 0;
}

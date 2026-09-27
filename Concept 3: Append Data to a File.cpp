#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ofstream outputFile("message.txt", ios::app);

    if (!outputFile) {
        cerr << "Error: Could not open message.txt for appending\n";
        return 1;
    }

    outputFile << "This line was added using append mode.\n";

    outputFile.close();

    cout << "New line appended successfully.\n";

    return 0;
}

#include <cctype>
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

    size_t lineCount = 0;
    size_t wordCount = 0;
    size_t characterCount = 0;

    bool insideWord = false;
    char ch;

    while (inputFile.get(ch)) {
        ++characterCount;

        if (ch == '\n') {
            ++lineCount;
        }

        if (isspace(static_cast<unsigned char>(ch))) {
            insideWord = false;
        }
        else if (!insideWord) {
            ++wordCount;
            insideWord = true;
        }
    }

    // Count the last line if it does not end with '\n'
    if (characterCount > 0) {
        inputFile.clear();
        inputFile.seekg(-1, ios::end);

        char lastCharacter;
        inputFile.get(lastCharacter);

        if (lastCharacter != '\n') {
            ++lineCount;
        }
    }

    cout << "Lines: " << lineCount << '\n';
    cout << "Words: " << wordCount << '\n';
    cout << "Characters: " << characterCount << '\n';

    return 0;
}

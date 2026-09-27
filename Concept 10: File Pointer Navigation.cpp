#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    fstream file("navigation.txt",
                 ios::in | ios::out | ios::trunc);

    if (!file) {
        cerr << "Error: Could not open navigation.txt\n";
        return 1;
    }

    file << "ABCDE";

    cout << "Output position after writing: "
         << file.tellp() << '\n';

    file.flush();

    file.seekg(0, ios::beg);

    char firstCharacter;
    file.get(firstCharacter);

    cout << "First character: "
         << firstCharacter << '\n';

    cout << "Input position after reading one character: "
         << file.tellg() << '\n';

    file.seekg(2, ios::beg);

    char thirdCharacter;
    file.get(thirdCharacter);

    cout << "Character at position 2: "
         << thirdCharacter << '\n';

    file.seekp(5, ios::beg);

    file << "F";

    file.close();

    cout << "Navigation completed. Check navigation.txt\n";

    return 0;
}

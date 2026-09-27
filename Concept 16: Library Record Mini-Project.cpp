#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

class Book {
private:
    int bookId;
    string title;
    string author;
    bool issued;

public:
    Book(int id, string bookTitle, string bookAuthor, bool issueStatus = false)
        : bookId(id),
          title(move(bookTitle)),
          author(move(bookAuthor)),
          issued(issueStatus) {}

    int getBookId() const {
        return bookId;
    }

    string toFileRecord() const {
        return to_string(bookId) + "|" +
               title + "|" +
               author + "|" +
               (issued ? "1" : "0");
    }

    void display() const {
        cout << "Book ID: " << bookId << '\n';
        cout << "Title: " << title << '\n';
        cout << "Author: " << author << '\n';
        cout << "Status: "
             << (issued ? "Issued" : "Available") << '\n';
    }
};

void addBook() {
    int id;
    string title;
    string author;

    cout << "Enter book ID: ";
    cin >> id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter title: ";
    getline(cin, title);

    cout << "Enter author: ";
    getline(cin, author);

    Book book(id, title, author);

    ofstream outputFile("library_books.txt", ios::app);

    if (!outputFile) {
        cerr << "Error: Could not open library_books.txt\n";
        return;
    }

    outputFile << book.toFileRecord() << '\n';

    cout << "Book added successfully.\n";
}

void displayBooks() {
    ifstream inputFile("library_books.txt");

    if (!inputFile) {
        cout << "No library record file found.\n";
        return;
    }

    string line;

    while (getline(inputFile, line)) {
        stringstream record(line);

        string idText;
        string title;
        string author;
        string issuedText;

        if (getline(record, idText, '|') &&
            getline(record, title, '|') &&
            getline(record, author, '|') &&
            getline(record, issuedText)) {

            Book book(
                stoi(idText),
                title,
                author,
                issuedText == "1"
            );

            book.display();

            cout << "-------------------------\n";
        }
    }
}

int main() {
    int choice;

    do {
        cout << "\nLibrary Record System\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 0:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>

#include "book.cpp"
#include "member.cpp"
#include "auth.cpp"

using namespace std;

void issueBook() {
    string title, memberId;
    cout << "Enter the title of the book to issue: ";
    cin >> title;
    cout << "Enter member ID: ";
    cin >> memberId;
    bool bookFound = false, memberFound = false;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].title == title && library[i].stock > 0) {
            bookFound = true;
            for (int j = 0; j < members.size(); j++) {
                if (members[j].id == memberId) {
                    memberFound = true;
                    cout << "Book issued successfully to " << members[j].name << "." << endl;
                    library[i].stock--;
                    return;
                }
            }
            cout << "Member not found." << endl;
            return;
        }
    }
    if (!bookFound)
        cout << "Book not found or out of stock." << endl;
}

int main() {
    bool loggedIn = login();
    if (!loggedIn) {
        return 1;
    }
    loadBooksFromCSV();
    cout << ":::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    cout << "::::::::::::::: Welcome to BUBT :::::::::::::::" << endl;
    cout << ":::::::::: Library Management System ::::::::::" << endl;
    cout << ":::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    int choice;
    do {
        cout << "1. Add book" << endl;
        cout << "2. Remove book" << endl;
        cout << "3. Book List" << endl;
        cout << "4. Add Member" << endl;
        cout << "5. Issue book" << endl;
        cout << "6. Return book" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            removeBook();
            break;
        case 3:
            bookList();
            break;
        case 4:
            addMember();
            break;
        case 5:
            issueBook();
            break;
        case 6:
            returnBook();
            break;
        case 7:
            logout(loggedIn);
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 7);
    writeBooksToCSV();
    return 0;
}



// Search Functionality
// Update Book Information
// Fine Calculation

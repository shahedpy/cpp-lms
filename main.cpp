// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include "book.cpp"

using namespace std;

class Member {
public:
    int intake;
    string id;
    string name;
    string department;
};

vector<Member> members;

void addMember() {
    Member newMember;
    cout << "Enter ID: ";
    cin >> newMember.id;
    cout << "Enter name: ";
    cin >> newMember.name;
    cout << "Enter department: ";
    cin >> newMember.department;
    cout << "Enter intake: ";
    cin >> newMember.intake;
    members.push_back(newMember);
    cout << "Member added successfully." << endl;
}
// auth.cpp

bool login() {
    string username, password;
    int attempts = 0;
    do {
        cout << "Enter username: ";
        cin >> username;
        password = getpass("Enter Password: ");

        if (username == "admin" && password == "admin") {
            return true;
        } else {
            cout << "Invalid username or password." << endl;
            attempts++;
        }
    } while (attempts < 3);
    cout << "Maximum login attempts reached. Access denied." << endl;
    return false;
}

void logout(bool& loggedIn){
    loggedIn = false;
    cout << "Logged out successfully." << endl;
}

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

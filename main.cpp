// main.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <ctime>


#include "book.cpp"
#include "auth.cpp"


using namespace std;

int main() {

    vector<Member> members;
    vector<Book> library;


    bool loggedIn = login();
    if (!loggedIn) {
        return 1;
    }
    loadMembersFromCSV(members);
    loadBooksFromCSV(library);
    loadIssueRecordsFromCSV();
    cout << ":::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    cout << "::::::::::::::: Welcome to BUBT :::::::::::::::" << endl;
    cout << ":::::::::: Library Management System ::::::::::" << endl;
    cout << ":::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    int choice;
    do {
        cout << "------------------------" << endl;
        cout << "|  1 | Add Book        |" << endl;
        cout << "|  2 | Update Book     |" << endl;
        cout << "|  3 | Remove Book     |" << endl;
        cout << "|  4 | Book List       |" << endl;
        cout << "|  5 | Issue Book      |" << endl;
        cout << "|  6 | Return Book     |" << endl;
        cout << "|  7 | Issue History   |" << endl;
        cout << "|  8 | Return History  |" << endl;
        cout << "|  9 | Add Member      |" << endl;
        cout << "| 10 | Update Member   |" << endl;
        cout << "| 11 | Member List     |" << endl;
        cout << "| 12 | Member History  |" << endl;
        cout << "| 13 | Member Details  |" << endl;
        cout << "| 14 | Change Password |" << endl;
        cout << "| 15 | Logout          |" << endl;
        cout << "------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addBook(library);
            break;
        case 2:
            updateBook(library);
            break;
        case 3:
            removeBook(library);
            break;
        case 4:
            bookList(library);
            break;
        case 5:
            issueBook(members, library);
            break;
        case 6:
            returnBook(library);
            break;
        case 7:
            issueHistory();
            break;
        case 8:
            returnHistory();
            break;
        case 9:
            addMember(members);
            break;
        case 10:
            updateMember(members);
            break;
        case 11:
            memberList(members);
            break;
        case 12:
            memberHistory();
            break;
        case 13:
            memberDetails();
            break;
        case 14:
            changePassword();
            break;
        case 15:
            writeBooksToCSV(library);
            writeMembersToCSV(members);
            writeIssueRecordsToCSV();
            logout(loggedIn);
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 15);
    return 0;
}

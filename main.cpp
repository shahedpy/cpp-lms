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
    vector<IssueRecord> issueRecord;
    vector<ReturnRecord> returnRecord;


    bool loggedIn = login();
    if (!loggedIn) {
        return 1;
    }
    loadMembersFromCSV(members);
    loadBooksFromCSV(library);
    loadIssueRecordsFromCSV(issueRecord);
    loadReturnRecordsFromCSV(returnRecord);
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
        cout << "| 12 | Remove Member   |" << endl;
        cout << "| 13 | Change Password |" << endl;
        cout << "| 14 | Logout          |" << endl;
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
            issueBook(members, library, issueRecord);
            break;
        case 6:
            returnBook(library, returnRecord);
            break;
        case 7:
            issueHistory(issueRecord);
            break;
        case 8:
            returnHistory(returnRecord);
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
            removeMember(members);
            break;
        case 13:
            changePassword();
            break;
        case 14:
            writeBooksToCSV(library);
            writeMembersToCSV(members);
            writeIssueRecordsToCSV(issueRecord);
            writeReturnRecordsToCSV(returnRecord);
            logout(loggedIn);
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 14);
    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>

using namespace std;

class Book {
public:
    string title;
    string author;
    string publisher;
    int year;
    int price;
    int stock;
};

class Member {
public:
    int intake;
    string id;
    string name;
    string department;
};

vector<Book> library;
vector<Member> members;

void addBook() {
    Book newBook;
    cout << "Enter title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter author: ";
    cin >> newBook.author;
    cout << "Enter publisher: ";
    cin >> newBook.publisher;
    cout << "Enter year: ";
    cin >> newBook.year;
    cout << "Enter price: ";
    cin >> newBook.price;
    cout << "Enter stock: ";
    cin >> newBook.stock;

    library.push_back(newBook);
    ofstream outFile("books.csv", ios::app);
    if (outFile.is_open()) {
        outFile << newBook.title << "," << newBook.author << "," << newBook.publisher << ","
                << newBook.year << "," << newBook.price << "," << newBook.stock << "\n";
        outFile.close();
        cout << "Book added successfully." << endl;
    } else {
        cout << "Unable to open file to save book data." << endl;
    }
}

void removeBook() {
    string title;
    cout << "Enter the title of the book to remove: ";
    cin >> title;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].title == title) {
            library.erase(library.begin() + i);
            cout << "Book removed successfully." << endl;
            cout << "---------------------------" << endl;
            return;
        }
    }
    cout << "Book not found." << endl;
}
void bookList(){
    if (library.empty()) {
        cout << "No books available in the library." << endl;
    } else {
        cout << "List of Books in the Library:" << endl;
        for (const auto &book : library) {
            cout << "---------------------------" << endl;
            cout << "Title:\t\t" << book.title << endl;
            cout << "Author:\t\t" << book.author << endl;
            cout << "Publisher:\t" << book.publisher << endl;
            cout << "Year:\t\t" << book.year << endl;
            cout << "Price:\t\t" << book.price << endl;
            cout << "Stock:\t\t" << book.stock << endl;
        }
        cout << "---------------------------" << endl;
    }
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

void returnBook() {
    string title;
    cout << "Enter the title of the book to return: ";
    cin >> title;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].title == title) {
            library[i].stock++;
            cout << "Book returned successfully." << endl;
            return;
        }
    }
    cout << "Book not found." << endl;
}

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

void readDataFromFile() {
    ifstream inFile("books.csv");
    if (inFile.is_open()) {
        string line;
        bool isFirstRow = true;
        while (getline(inFile, line)) {
            if (isFirstRow) {
                isFirstRow = false;
                continue;
            }
            Book newBook;
            stringstream ss(line);
            getline(ss, newBook.title, ',');
            getline(ss, newBook.author, ',');
            getline(ss, newBook.publisher, ',');
            ss >> newBook.year >> newBook.price >> newBook.stock;
            library.push_back(newBook);
        }
        inFile.close();
    } else {
        cout << "Unable to open file to read book data." << endl;
    }
}
void writeDataToFile() {
    ofstream outFile("books.csv");
    if (outFile.is_open()) {
        outFile << "Title,Author,Publisher,Year,Price,Stock\n";
        for (const auto &book : library) {
            outFile << book.title << "," << book.author << "," << book.publisher << ","
                    << book.year << "," << book.price << "," << book.stock << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file to write book data." << endl;
    }
}

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

int main() {
    bool loggedIn = login();
    if (!loggedIn) {
        return 1;
    }
    readDataFromFile();
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
    writeDataToFile();
    return 0;
}



// Search Functionality
// Update Book Information
// Fine Calculation

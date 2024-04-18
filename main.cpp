#include <iostream>
#include <fstream>
#include <vector>

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

class Student {
public:
    int intake;
    string id;
    string name;
    string department;
};

vector<Book> library;
vector<Student> students;

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
    ofstream outFile("books.txt", ios::app);
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
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Publisher: " << book.publisher << endl;
            cout << "Year: " << book.year << endl;
            cout << "Price: " << book.price << endl;
            cout << "Stock: " << book.stock << endl;
            cout << "---------------------------" << endl;
        }
    }
}

void issueBook() {
    string title, studentId;
    cout << "Enter the title of the book to issue: ";
    cin >> title;
    cout << "Enter student ID: ";
    cin >> studentId;
    bool bookFound = false, studentFound = false;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].title == title && library[i].stock > 0) {
            bookFound = true;
            for (int j = 0; j < students.size(); j++) {
                if (students[j].id == studentId) {
                    studentFound = true;
                    cout << "Book issued successfully to " << students[j].name << "." << endl;
                    library[i].stock--;
                    return;
                }
            }
            cout << "Student not found." << endl;
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

void addStudent() {
    Student newStudent;
    cout << "Enter ID: ";
    cin >> newStudent.id;
    cout << "Enter name: ";
    cin >> newStudent.name;
    cout << "Enter department: ";
    cin >> newStudent.department;
    cout << "Enter intake: ";
    cin >> newStudent.intake;
    students.push_back(newStudent);
    cout << "Student added successfully." << endl;
}

int main() {
    cout << ":::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    cout << "::::::::::::::: Welcome to BUBT :::::::::::::::" << endl;
    cout << ":::::::::: Library Management System ::::::::::" << endl;
    cout << ":::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    int choice;
    do {
        cout << "1. Add book" << endl;
        cout << "2. Remove book" << endl;
        cout << "3. Book List" << endl;
        cout << "4. Add student" << endl;
        cout << "5. Issue book" << endl;
        cout << "6. Return book" << endl;
        cout << "7. Exit" << endl;
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
            addStudent();
            break;
        case 5:
            issueBook();
            break;
        case 6:
            returnBook();
            break;
        case 7:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 7);
    return 0;
}



// Search Functionality
// Update Book Information
// Fine Calculation
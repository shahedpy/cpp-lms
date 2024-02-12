#include <iostream>

using namespace std;

class Book{
    public:
        string title;
        string author;
        string publisher;
        int year;
        int pages;
        int price;
        int stock;
};

class Student{
    public:
        string name;
        string rollNo;
        string branch;
        int year;
        int semester;
};


int main() {
    cout << "Welcome to LMS" << endl;
    int choice;
    do {

        cout << "1. Add book" << endl;
        cout << "2. Remove book" << endl;
        cout << "3. Add student" << endl;
        cout << "4. Issue book" << endl;
        cout << "5. Return book" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Add a book" << endl;
                break;
            case 2:
                cout << "Add a student" << endl;
                break;
            case 3:
                cout << "Add a student" << endl;
                break;
            case 4:
                cout << "Issue a book" << endl;
                break;
            case 5:
                cout << "Return a book" << endl;
                break;
            case 6:
                cout << "Exit" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 6);
        
    return 0;
}

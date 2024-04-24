// book.cpp
#include "member.cpp"

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

vector<Book> library;

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

void issueBook(vector<Member> members) {
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

void loadBooksFromCSV() {
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
            string temp;
            getline(ss, newBook.title, ',');
            getline(ss, newBook.author, ',');
            getline(ss, newBook.publisher, ',');
            getline(ss, temp, ',');
            newBook.year = stoi(temp);
            getline(ss, temp, ',');
            newBook.price = stoi(temp);
            getline(ss, temp, ',');
            newBook.stock = stoi(temp);
            library.push_back(newBook);
        }
        inFile.close();
    } else {
        cout << "Unable to open file to read book data." << endl;
    }
}

void writeBooksToCSV() {
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
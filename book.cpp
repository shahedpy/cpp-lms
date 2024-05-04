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
class IssueRecord {
    public:
        string bookTitle;
        string memberId;
        string date;
};

vector<Book> library;
vector<IssueRecord> issueRecord;

void addIssueRecord(const string& bookTitle, const string& memberId){
    IssueRecord ir;
    ir.bookTitle = bookTitle;
    ir.memberId = memberId;

    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    char dateString[11];
    strftime(dateString, sizeof(dateString), "%Y-%m-%d", localtime(&currentTime));

    ir.date = dateString;

    issueRecord.push_back(ir);
}


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

void updateBook(){
    string title;
    cout << "Enter the title of the book to update: ";
    cin.ignore();
    getline(cin, title);
      bool bookFound = false;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].title == title) {
            bookFound = true;
            cout << "Enter new title (or press enter to keep it unchanged): ";
            string newTitle;
            getline(cin, newTitle);
            if (!newTitle.empty()) {
                library[i].title = newTitle;
            }

            cout << "Enter new author (or press enter to keep it unchanged): ";
            string newAuthor;
            getline(cin, newAuthor);
            if (!newAuthor.empty()) {
                library[i].author = newAuthor;
            }

            cout << "Enter new publisher (or press enter to keep it unchanged): ";
            string newPublisher;
            getline(cin, newPublisher);
            if (!newPublisher.empty()) {
                library[i].publisher = newPublisher;
            }

            cout << "Enter new year (or enter 0 to keep it unchanged): ";
            int newYear;
            cin >> newYear;
            if (newYear != 0) {
                library[i].year = newYear;
            }

            cout << "Enter new price (or enter 0 to keep it unchanged): ";
            int newPrice;
            cin >> newPrice;
            if (newPrice != 0) {
                library[i].price = newPrice;
            }

            cout << "Enter new stock (or enter 0 to keep it unchanged): ";
            int newStock;
            cin >> newStock;
            if (newStock != 0) {
                library[i].stock = newStock;
            }

            cout << "Book updated successfully." << endl;
            return;
        }
    }
    if (!bookFound) {
        cout << "Book not found." << endl;
    }
}

void removeBook() {
    string title;
    cout << "Enter the title of the book to remove: ";
    cin.ignore();
    getline(cin, title);
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
                    addIssueRecord(title, memberId);
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

void issueHistory() {
    if (issueRecord.empty()) {
        cout << "No issue history available." << endl;
    } else {
        cout << "Issue History:" << endl;
        for (const auto &record : issueRecord) {
            cout << "---------------------------" << endl;
            cout << "Book Title:\t" << record.bookTitle << endl;
            cout << "Member ID:\t" << record.memberId << endl;
            cout << "Date Issued:\t" << record.date << endl;
        }
        cout << "---------------------------" << endl;
    }
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
void writeIssueRecordsToCSV() {
    ofstream outFile("issue_records.csv");
    if (outFile.is_open()) {
        outFile << "BookTitle,MemberId,Date\n";
        for (const auto &record : issueRecord) {
            outFile << record.bookTitle << "," << record.memberId << "," << record.date << "\n";
        }
        outFile.close();
        cout << "Issue records written to CSV successfully." << endl;
    } else {
        cout << "Unable to open file to write issue records." << endl;
    }
}


void loadIssueRecordsFromCSV() {
    ifstream inFile("issue_records.csv");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            IssueRecord record;
            stringstream ss(line);
            getline(ss, record.bookTitle, ',');
            getline(ss, record.memberId, ',');
            getline(ss, record.date, ',');
            issueRecord.push_back(record);
        }
        inFile.close();
    } else {
        cout << "Unable to open file to read issue records." << endl;
    }
}

void returnHistory() {
    cout << "Return History" << endl;
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
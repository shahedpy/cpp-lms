// return_history.cpp

class ReturnRecord {
    public:
        string bookTitle;
        string memberId;
        string date;
};

void addReturnRecord(const string& bookTitle, const string& memberId, vector<ReturnRecord>& returnRecord){
    ReturnRecord rr;
    rr.bookTitle = bookTitle;
    rr.memberId = memberId;

    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    char dateString[11];
    strftime(dateString, sizeof(dateString), "%Y-%m-%d", localtime(&currentTime));

    rr.date = dateString;

    returnRecord.push_back(rr);
}

void returnHistory(vector<ReturnRecord>& returnRecord) {
    if (returnRecord.empty()) {
        cout << "No return history available." << endl;
    } else {
        cout << "Return History:" << endl;
        for (const auto &record : returnRecord) {
            cout << "---------------------------" << endl;
            cout << "Book Title:\t" << record.bookTitle << endl;
            cout << "Member ID:\t" << record.memberId << endl;
            cout << "Date Returned:\t" << record.date << endl;
        }
        cout << "---------------------------" << endl;
    }
}

void loadReturnRecordsFromCSV(vector<ReturnRecord>& returnRecord) {
    ifstream inFile("return_records.csv");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            ReturnRecord record;
            stringstream ss(line);
            getline(ss, record.bookTitle, ',');
            getline(ss, record.memberId, ',');
            getline(ss, record.date, ',');
            returnRecord.push_back(record);
        }
        inFile.close();
    } else {
        cout << "Unable to open file to read return records." << endl;
    }
}


void writeReturnRecordsToCSV(vector<ReturnRecord>& returnRecord) {
    ofstream outFile("return_records.csv");
    if (outFile.is_open()) {
        outFile << "BookTitle,MemberId,Date\n";
        for (const auto &record : returnRecord) {
            outFile << record.bookTitle << "," << record.memberId << "," << record.date << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file to write return records." << endl;
    }
}
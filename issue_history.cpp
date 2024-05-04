// issue_history.cpp

class IssueRecord {
    public:
        string bookTitle;
        string memberId;
        string date;
};

void addIssueRecord(const string& bookTitle, const string& memberId, vector<IssueRecord>& issueRecord){
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

void issueHistory(vector<IssueRecord>& issueRecord) {
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

void loadIssueRecordsFromCSV(vector<IssueRecord>& issueRecord) {
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


void writeIssueRecordsToCSV(vector<IssueRecord>& issueRecord) {
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
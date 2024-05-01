// member.cpp
using namespace std;
class Member {
public:
    string id;
    string name;
    string department;
    int intake;
};

void addMember(vector<Member> members) {
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

void updateMember(vector<Member>& members) {
    string id;
    cout << "Enter the ID of the member to update: ";
    cin >> id;

    for (auto& member : members) {
        if (member.id == id) {
            cout << "Enter new name (or press enter to keep it unchanged): ";
            cin.ignore();
            getline(cin, member.name);

            cout << "Enter new department (or press enter to keep it unchanged): ";
            getline(cin, member.department);

            cout << "Enter new intake (or enter 0 to keep it unchanged): ";
            cin >> member.intake;

            cout << "Member updated successfully." << endl;
            return;
        }
    }

    cout << "Member not found." << endl;
}

void removeMember(vector<Member>& members) {
    string id;
    cout << "Enter the ID of the member to remove: ";
    cin >> id;

    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it->id == id) {
            members.erase(it);
            cout << "Member removed successfully." << endl;
            return;
        }
    }

    cout << "Member not found." << endl;
}

void memberList(const vector<Member>& members) {
    if (members.empty()) {
        cout << "No members available." << endl;
    } else {
        cout << "List of Members:" << endl;
        for (const auto& member : members) {
            cout << "ID:\t\t" << member.id << endl;
            cout << "Name:\t\t" << member.name << endl;
            cout << "Department:\t" << member.department << endl;
            cout << "Intake:\t\t" << member.intake << endl;
            cout << "---------------------------" << endl;
        }
    }
}

void memberHistory() {}

void memberDetails() {}

void loadMembersFromCSV(vector<Member>& members) {
    ifstream inFile("members.csv");
    if (inFile.is_open()) {
        string line;
        bool isFirstRow = true;
        while (getline(inFile, line)) {
            if (isFirstRow) {
                isFirstRow = false;
                continue;
            }
            stringstream ss(line);
            Member newMember;
            getline(ss, newMember.id, ',');
            getline(ss, newMember.name, ',');
            getline(ss, newMember.department, ',');
            string intakeStr;
            getline(ss, intakeStr, ',');
            newMember.intake = stoi(intakeStr);
            members.push_back(newMember);
        }
        inFile.close();
    } else {
        cout << "Unable to open file to read member data." << endl;
    }
}

void writeMembersToCSV(const vector<Member>& members) {
    ofstream outFile("members.csv");
    if (outFile.is_open()) {
        outFile << "ID,Name,Department,Intake\n";
        for (const auto& member : members) {
            outFile << member.id << "," << member.name << "," << member.department << "," << member.intake << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file to write member data." << endl;
    }
}
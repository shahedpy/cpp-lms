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

void updateMember(){}
void removeMember(){}
void memberList() {}
void loadMembersFromCSV() {}
void writeMembersToCSV() {
    ofstream outFile("members.csv");
    outFile << "ID,Name,Department\n";
}
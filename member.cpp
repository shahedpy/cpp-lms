class Member {
public:
    int intake;
    string id;
    string name;
    string department;
};

vector<Member> members;

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
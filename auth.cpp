// auth.cpp
bool login() {
    string username, password;
    int attempts = 0;
    do {
        cout << "Enter username: ";
        cin >> username;
        password = getpass("Enter Password: ");

        ifstream file("users.csv");
        string line;
        bool found = false;
        while (getline(file, line)) {
            size_t pos = line.find(",");
            string stored_username = line.substr(0, pos);
            string stored_password = line.substr(pos + 1);
            if (username == stored_username && password == stored_password) {
                found = true;
                break;
            }
        }
        file.close();

        if (found) {
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

void changePassword() {
    string username, oldPassword, newPassword;

    cout << "Enter username: ";
    cin >> username;
    oldPassword = getpass("Enter old password: ");
    newPassword = getpass("Enter new password: ");

    ifstream file("users.csv");
    ofstream tempFile("temp.csv");
    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos = line.find(",");
        string stored_username = line.substr(0, pos);
        string stored_password = line.substr(pos + 1);
        if (username == stored_username && oldPassword == stored_password) {
            tempFile << username << "," << newPassword << endl;
            found = true;
            cout << "Password changed successfully." << endl;
        } else {
            tempFile << line << endl;
        }
    }
    file.close();
    tempFile.close();

    remove("users.csv");
    rename("temp.csv", "users.csv");

    if (!found) {
        cout << "Incorrect old password. Password change failed." << endl;
    }
}
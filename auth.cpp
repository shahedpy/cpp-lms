bool login() {
    string username, password;
    int attempts = 0;
    do {
        cout << "Enter username: ";
        cin >> username;
        password = getpass("Enter Password: ");

        if (username == "admin" && password == "admin") {
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
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstring>
#include <filesystem>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

string status = "Assigned"; // Global status

// Function to check progress from user
void checkProgress() {
    string input;
    cout << "📝 Enter task progress (Completed/InProgress): ";
    getline(cin, input);

    if (input == "Completed") {
        status = "Completed";
        cout << "✅ Task marked as Completed.\n";
    }
    else if (input == "InProgress") {
        status = "InProgress";
        cout << "🔁 Task is still In Progress.\n";
    }
    else {
        cout << "⚠ Invalid input. Status remains: " << status << endl;
    }
}

// Base User class
class User {
protected:
    string username;
    string password;
    string role;
    time_t lastLoginTime;

public:
    User(string _username, string _password, string _role)
        : username(_username), password(_password), role(_role), lastLoginTime(0) {
    }

    string getRole() const {
        return role;
    }

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    void displayRole() const {
        cout << "Role: " << role << endl;
    }


    string basicHash(const string& input) {
        unsigned long hash = 5381;
        for (size_t i = 0; i < input.length(); ++i) {
            hash = ((hash << 5) + hash) + input[i]; // hash * 33 + input[i]
        }

        string result = "";
        while (hash > 0) {
            char c = 'a' + (hash % 26); // Convert to lowercase alphabet
            result += c;
            hash /= 26;
        }
        return result;
    }


    virtual void sendMessage() {}
    virtual void logAction(const string& action) const {}
    virtual ~User() = default;
};

// PerformanceReview class
class PerformanceReview {
public:
    virtual void reviewPerformance() {
        string role;
        cout << "Enter role to review (junior, employee, manager): ";
        cin >> role;

        string filePath;
        if (role == "junior") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\juniorCredentials.txt";
        }
        else if (role == "employee") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\employeeCredentials.txt";
        }
        else if (role == "manager") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\managerCredentials.txt";
        }
        else {
            cout << "Invalid role entered!" << endl;
            return;
        }

        ifstream infile(filePath);
        if (!infile.is_open()) {
            cout << "Error opening credentials file!" << endl;
            return;
        }

        cout << "Available users under role '" << role << "':" << endl;
        string uname, pwd;
        while (infile >> uname >> pwd) {
            cout << "- " << uname << endl;
        }
        infile.close();

        string targetName;
        cout << "Enter username to review: ";
        cin >> targetName;

        cin.ignore();
        string reviewText;
        cout << "Enter review: ";
        getline(cin, reviewText);

        ofstream reviewFile("C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\review.txt", ios::app);
        if (!reviewFile.is_open()) {
            cout << "Error creating review file!" << endl;
            return;
        }

        reviewFile << "Role: " << role << " | Name: " << targetName << " | Review: " << reviewText << endl;
        reviewFile.close();

        cout << "Review saved successfully." << endl;
    }

    virtual ~PerformanceReview() = default;
};



//OTP function


bool verifyOTP() {
    srand(time(0));
    int otp = rand() % 9000 + 1000;
    cout << "Your OTP is: " << otp << endl;

    int maxTries = 3;
    auto start = chrono::steady_clock::now();

    for (int attempt = 1; attempt <= maxTries; ++attempt) {
        auto now = chrono::steady_clock::now();
        int elapsed = chrono::duration_cast<chrono::seconds>(now - start).count();

        if (elapsed >= 30) {
            cout << "Time's up! Login failed." << endl;
            return false;
        }

        cout << "\nAttempt " << attempt << " of " << maxTries << ". ";
        cout << "Time remaining: " << 30 - elapsed << " seconds." << endl;

        int enteredOtp;
        cout << "Enter the OTP: ";
        cin >> enteredOtp;

        if (enteredOtp == otp) {
            return true;
        }
        else {
            cout << "Incorrect OTP!" << endl;
        }

        // Optional short delay for user experience
        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "Maximum attempts reached. Login failed." << endl;
    return false;
}

class Login : public User {
public:
    Login() : User("", "", "") {}

    bool performLogin() {
        cout << "=== Login ===" << endl;
        cin >> *this; // Get role, username, password

        string inputUsername = username;
        string inputHashedPassword = password; // Hash entered password
        string inputRole = role;

        string filePath;
        if (inputRole == "junior") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\juniorCredentials.txt";
        }
        else if (inputRole == "employee") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\employeeCredentials.txt";
        }
        else if (inputRole == "manager") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\managerCredentials.txt";
        }
        else if (inputRole == "director") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\directorCredentials.txt";
        }
        else if (inputRole == "executive") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\executiveCredentials.txt";
        }
        else {
            cout << "Invalid role entered!" << endl;
            return false;
        }

        ifstream file(filePath);
        if (!file.is_open()) {
            cout << "Error: Cannot open credentials file!" << endl;
            return false;
        }

        string fileUsername, filePassword;
        bool found = false;

        while (file >> fileUsername >> filePassword) {
            if (fileUsername == inputUsername && filePassword == inputHashedPassword) {
                found = true;
                break;
            }
        }
        file.close();

        if (!found) {
            cout << "Invalid credentials!" << endl;
            return false;
        }

        if (!verifyOTP()) {
            return false;
        }

        cout << "Login successful!" << endl;
        return true;
    }

    friend istream& operator>>(istream& in, Login& login);
};

istream& operator>>(istream& in, Login& login) {
    cout << "Enter role (junior, employee, manager, director, executive): ";
    in >> login.role;

    cout << "Enter username: ";
    in >> login.username;

    cout << "Enter password: ";
    in >> login.password;

    return in;
}

class Register : public User {
public:
    Register(string _username, string _password, string _role)
        : User(_username, _password, _role) {
    }

    void registerUser() const {
        string filePath;
        if (role == "junior") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\juniorCredentials.txt";
        }
        else if (role == "employee") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\employeeCredentials.txt";
        }
        else if (role == "manager") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\managerCredentials.txt";
        }
        else if (role == "director") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\directorCredentials.txt";
        }
        else if (role == "executive") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\executiveCredentials.txt";
        }
        else {
            cout << "Invalid role entered!" << endl;
            return;
        }

        ofstream file(filePath, ios::app);
        if (!file.is_open()) {
            cout << "Error: Cannot open credentials file for role '" << role << "'!" << endl;
            return;
        }

        string hashedPassword = password;  // Hash password here
        file << username << " " << hashedPassword << endl;
        file.close();

        cout << "User registered successfully in file: " << filePath << endl;
    }
};


// MessageHandler
// MessageHandler
class MessageHandler : public User {
public:
    MessageHandler(string _username, string _password, string _role)
        : User(_username, _password, _role) {
    }

    void sendMessage() override {
        string recipientUsername, recipientRole, messageType, messageContent;

        cout << "Enter recipient role (junior, employee, manager, director, executive): ";
        cin >> recipientRole;

        cout << "Enter recipient username: ";
        cin >> recipientUsername;

        cout << "Enter message type (INFO, PRIVATE, ALERT): ";
        cin >> messageType;
        for (char& ch : messageType) ch = toupper(ch);

        cin.ignore();
        cout << "Enter message content: ";
        getline(cin, messageContent);

        bool allowed = false;

        if (messageType == "INFO") {
            allowed = true;
        }
        else if (messageType == "PRIVATE") {
            if (isHigherOrEqualClearance(recipientRole)) {
                messageContent = encryptMessage(messageContent);
                allowed = true;
            }
        }
        else if (messageType == "ALERT") {
            if (canSendAlertTo(recipientRole)) {
                allowed = true;
            }
        }

        if (!allowed) {
            cout << "Message not allowed based on clearance rules!" << endl;
            return;
        }

        string inboxPath = recipientUsername + "_inbox.txt";
        ofstream inboxFile(inboxPath, ios::app);
        if (!inboxFile) {
            cout << "Error opening recipient's inbox!" << endl;
            return;
        }

        inboxFile << "From: " << username << " (" << role << ") | Type: " << messageType
            << " | Content: " << messageContent << endl;
        inboxFile.close();

        logAction("Sent " + messageType + " to " + recipientUsername);
        cout << "Message sent and stored." << endl;
    }

    string encryptMessage(const string& message) const {
        string encrypted = message;
        for (char& c : encrypted) c += 3;
        return encrypted;
    }

    int getRoleLevel(const string& roleName) const {
        if (roleName == "executive") return 5;
        if (roleName == "director")  return 4;
        if (roleName == "manager")   return 3;
        if (roleName == "employee")  return 2;
        if (roleName == "junior")    return 1;
        return 0;
    }

    bool isHigherOrEqualClearance(const string& targetRole) const {
        return getRoleLevel(role) >= getRoleLevel(targetRole);
    }

    bool canSendAlertTo(const string& targetRole) const {
        return getRoleLevel(role) > getRoleLevel(targetRole);
    }


    void seeMessages() const {
        string inboxPath = username + "_inbox.txt";
        ifstream inboxFile(inboxPath);

        cout << "\n=== Inbox for " << username << " ===" << endl;

        if (!inboxFile.is_open()) {
            cout << "No messages found or unable to open inbox." << endl;
            return;
        }

        string line;
        bool hasMessages = false;
        while (getline(inboxFile, line)) {
            cout << line << endl;
            hasMessages = true;
        }
        inboxFile.close();

        if (!hasMessages) {
            cout << "No messages in inbox." << endl;
        }
    }

};


// AuditLogger
class AuditLogger : public User {
public:
    AuditLogger(string _username, string _password, string _role)
        : User(_username, _password, _role) {
    }

    void logAction(const string& action) const override {
        string logPath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\_audit_log.txt";
        ofstream auditFile(logPath, ios::app);
        if (auditFile.is_open()) {
            auditFile << getCurrentTime() << " " << username << " " << action << endl;
            auditFile.close();
        }
    }

    static string getCurrentTime() {
        time_t now = time(0);
        char dt[26];
        ctime_s(dt, sizeof(dt), &now);
        dt[strlen(dt) - 1] = '\0';
        return string(dt);
    }
};

// Role-specific classes
class Junior : public MessageHandler {
public:
    Junior(string _username, string _password)
        : MessageHandler(_username, _password, "junior") {
    }
};

class Employee : public MessageHandler {
public:
    Employee(string _username, string _password)
        : MessageHandler(_username, _password, "employee") {
    }
};

class Manager : public MessageHandler {
public:
    Manager(string _username, string _password)
        : MessageHandler(_username, _password, "manager") {
    }
};

class Director : public MessageHandler, public PerformanceReview {
public:
    Director(string _username, string _password)
        : MessageHandler(_username, _password, "director") {
    }
};

class Executive : public MessageHandler, public PerformanceReview {
public:
    Executive(string _username, string _password)
        : MessageHandler(_username, _password, "executive") {
    }

    void manageUser() {
        int choice;
        cout << "Enter 1 to ADD a user or 2 to REMOVE a user: ";
        cin >> choice;

        string targetRole, filePath;
        cout << "Enter the role (junior, employee, manager, director, executive): ";
        cin >> targetRole;

        if (targetRole == "junior") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\juniorCredentials.txt";
        }
        else if (targetRole == "employee") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\employeeCredentials.txt";
        }
        else if (targetRole == "manager") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\managerCredentials.txt";
        }
        else if (targetRole == "director") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\directorCredentials.txt";
        }
        else if (targetRole == "executive") {
            filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\executiveCredentials.txt";
        }
        else {
            cout << "Invalid role entered!" << endl;
            return;
        }

        if (choice == 1) {
            string newUsername, newPassword;
            cout << "Enter username to add: ";
            cin >> newUsername;
            cout << "Enter password: ";
            cin >> newPassword;

            ofstream outFile(filePath, ios::app);
            if (!outFile) {
                cout << "Error: Cannot open file for writing!" << endl;
                return;
            }

            outFile << newUsername << " " << newPassword << endl;
            outFile.close();
            cout << "User added successfully." << endl;
        }
        else if (choice == 2) {
            string removeUsername;
            cout << "Enter username to remove: ";
            cin >> removeUsername;

            ifstream inFile(filePath);
            ofstream tempFile("temp.txt");

            if (!inFile || !tempFile) {
                cout << "Error: Cannot open file!" << endl;
                return;
            }

            string uname, pwd;
            bool found = false;

            while (inFile >> uname >> pwd) {
                if (uname != removeUsername) {
                    tempFile << uname << " " << pwd << endl;
                }
                else {
                    found = true;
                }
            }

            inFile.close();
            tempFile.close();

            if (found) {
                remove(filePath.c_str());
                rename("temp.txt", filePath.c_str());
                cout << "User removed successfully." << endl;
            }
            else {
                remove("temp.txt");
                cout << "Username not found." << endl;
            }
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
};



class TTL {
protected:
    time_t startTime;
    int lifetimeSeconds;

public:
    TTL(int _lifetimeSeconds) : lifetimeSeconds(_lifetimeSeconds) {
        startTime = time(0);
    }

    bool isExpired() {
        time_t now = time(0);
        double elapsed = difftime(now, startTime);
        return elapsed > lifetimeSeconds;
    }

    void resetTTL() {
        startTime = time(0);
    }

    int getLifetime() {
        return lifetimeSeconds;
    }

    int getElapsed() {
        time_t now = time(0);
        return static_cast<int>(difftime(now, startTime));
    }

};



class Task : public TTL {
private:
    string creator;
    string assignee;
    string description;
    string status;  // "Created", "Assigned", "InProgress", "Completed", "Expired"
    int priority;

public:
    Task(string _creator, string _description, int _priority, int _ttlSeconds)
        : TTL(_ttlSeconds), creator(_creator), assignee(""),
        description(_description), status("Created"), priority(_priority) {
    }

    void assignTask(string _assignee) {
        string role, ttl, priority, task;

        // Clear input buffer if needed
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Step 1: Get role
        cout << "Enter the role of the assignee (junior/employee/manager/director/executive): ";
        getline(cin, role);

        // Step 2: Get assignee username
        cout << "\nEnter the username of the assignee: ";
        getline(cin, _assignee);
        assignee = _assignee;

        // Step 3: Get Time-To-Live (TTL)
        cout << "Enter task TTL (in hours or deadline format): ";
        getline(cin, ttl);

        // Step 4: Get priority level
        cout << "Enter priority level (High/Medium/Low): ";
        getline(cin, priority);

        // Step 5: Get task content
        cout << "Enter the task to assign: ";
        getline(cin, task);

        // Step 6: Set status
        if (status == "Created" || status == "Assigned") {
            status = "Assigned";
        }

        // Step 7: Save to file (include role in filename)
        string filename = assignee + "" + role + ".txt";
        ofstream file(filename, ios::app); // append mode
        if (file.is_open()) {
            file << "Role: " << role << endl;
            file << "Assignee: " << _assignee << endl;
            file << "TTL: " << ttl << endl;
            file << "Priority: " << priority << endl;
            file << "Task: " << task << endl;
            file << "Status: " << status << endl;
            file << "-----------------------------" << endl;
            file.close();
            cout << " Task assigned and written to file: " << filename << endl;
        }
        else {
            cerr << " Error: Unable to open file for writing.\n";
        }
    }



    // Recursive function to check task status up to 3 times within TTL
    void markInProgress(int ttlSeconds, int attempt = 1, steady_clock::time_point startTime = steady_clock::now()) {
        if (status == "Completed" || status == "Expired") {
            return;
        }

        int elapsed = duration_cast<seconds>(steady_clock::now() - startTime).count();

        if (elapsed >= ttlSeconds) {
            if (status != "Completed") {
                status = "Expired";
                cout << " TTL expired after " << ttlSeconds << " seconds. Task is now Expired.\n";
            }
            return;
        }

        cout << "\n Attempt " << attempt << " of 3 — Time remaining: " << (ttlSeconds - elapsed) << " seconds\n";

        checkProgress(); // Ask user

        if (status == "Completed") return;

        if (attempt < 3) {
            cout << " Waiting 10 seconds before next attempt...\n";
            this_thread::sleep_for(seconds(10));
            markInProgress(ttlSeconds, attempt + 1, startTime); // Recursive call
        }
        else {
            if (status != "Completed") {
                status = "Expired";
                cout << " Task expired after 3 attempts.\n";
            }
        }
    }

    void completeTask() {
        if (status == "InProgress") {
            status = "Completed";
        }
    }

    void expireTask() {
        status = "Expired";
    }

    void checkAndExpire() {
        if (isExpired() && status != "Completed") {
            expireTask();
        }
    }

    void displayTask() {
        string filename;

        // Ask for the filename
        cout << "Enter the filename to display (e.g., manager_abdullah123.txt): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
        getline(cin, filename);

        // Open and read the file
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            cout << "\n📋 Contents of " << filename << ":\n";
            cout << "---------------------------------\n";
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
            cout << "---------------------------------\n";
        }
        else {
            cerr << "❌ Error: Could not open file '" << filename << "' for reading.\n";
        }
    }



};



// Global Notification System
class GlobalNotifier {
public:
    static void broadcastNotification(const string& sender, const string& role) {
        cin.ignore();
        string message;
        cout << "Enter notification message to broadcast: ";
        getline(cin, message);

        string filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\global_notifications.txt";
        ofstream outFile(filePath, ios::app);
        if (!outFile.is_open()) {
            cout << "Failed to open global notifications file." << endl;
            return;
        }

        outFile << AuditLogger::getCurrentTime() << " | From: " << sender << " (" << role << ") | " << message << endl;
        outFile.close();

        cout << "Notification broadcasted successfully." << endl;
    }

    static void viewGlobalNotifications() {
        string filePath = "C:\\Users\\hp\\Desktop\\24i-2027_24i-2098_CY-A\\OOP_Project\\global_notifications.txt";
        ifstream inFile(filePath);
        if (!inFile.is_open()) {
            cout << "No global notifications available or file could not be opened." << endl;
            return;
        }

        cout << "\n=== Global Notifications ===" << endl;
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }
};


// Hash function
string basicHash(const string& input) {
    unsigned long hash = 5381;
    for (size_t i = 0; i < input.length(); ++i) {
        hash = ((hash << 5) + hash) + input[i]; // hash * 33 + input[i]
    }

    string result = "";
    while (hash > 0) {
        char c = 'a' + (hash % 26); // Convert to lowercase alphabet
        result += c;
        hash /= 26;
    }
    return result;
}




#endif // HEADER
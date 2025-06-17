//
// Created by vertex laptop on 11/9/2024.
//
#include "registrationAndLoginSystem.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to register a new user
void registerUser() {
    User newUser;

    // Prompt the user for a username
    cout << "Enter username: ";
    cin >> newUser.username;

    // Check if username already exists
    if (userExists(newUser.username)) {
        cout << "Username already exists. Try a different one." << endl;
        registerUser();  // Recursive call to re-prompt for registration
        return;
    }

    // Prompt the user for a password
    cout << "Enter password: ";
    cin >> newUser.password;

    // Prompt for the user's role, with validation
    cout << "Enter role (admin/employee): ";
    cin >> newUser.role;
    promptValidRole(newUser.role);

    // Save the new user to the file
    saveUser(newUser);
    cout << "User registered successfully." << endl;
}

// Function to ensure a valid role is entered
void promptValidRole(string& role) {
    if (role != "admin" && role != "employee") {
        cout << "Invalid role. Please enter either 'admin' or 'employee': ";
        cin >> role;
        promptValidRole(role);  // Recursive call to re-prompt for a valid role
    }
}

// Function to check if a username exists in the file
bool userExists(const string& username) {
    ifstream infile("user.txt");
    User user;

    // Read each line in the file and check for a matching username
    while (infile >> user.username >> user.password >> user.role) {
        if (user.username == username) {
            return true;  // Username exists
        }
    }
    return false;  // Username does not exist
}

// Function to save a user to the file
void saveUser(const User& user) {
    ofstream outfile("user.txt", ios::app);  // Open file in append mode
    if (!outfile) {
        cout << "Could not open file for writing." << endl;
        return;
    }
    // Write the user's username, password, and role to the file
    outfile << user.username << " " << user.password << " " << user.role << endl;
    outfile.close();
}

// Function for user login
bool loginUser(User &user) {
    string username, password;

    // Prompt for username and password
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream infile("user.txt");  // Open the file for reading
    bool found = false;

    // Check each user in the file to find matching credentials
    while (infile >> user.username >> user.password >> user.role) {
        if (user.username == username && user.password == password) {
            cout << "Login successful! Welcome, " << user.role << " " << user.username << "." << endl;
            found = true;  // Credentials are valid
            return found;
        }
    }
    infile.close();  // Close the file

    if (!found) {
        cout << "Invalid username or password. Try again." << endl;
        loginUser(user);  // Recursive call to re-prompt for login
    }
}

// Function for password reset
void forgotPassword() {
    string username, newPassword;

    // Prompt for username
    cout << "Enter your username: ";
    cin >> username;

    // Check if the user exists
    if (!userExists(username)) {
        cout << "Username not found. Try again." << endl;
        forgotPassword();  // Recursive call to re-prompt for password reset
        return;
    }

    // Prompt for new password
    cout << "Enter a new password: ";
    cin >> newPassword;

    // Open the original file and a temporary file
    ifstream infile("user.txt");
    ofstream tempFile("temp.txt");

    if (!infile || !tempFile) {
        cout << "Could not open files for password reset." << endl;
        return;
    }

    User user;
    bool updated = false;

    // Copy each line from the original file to the temporary file, updating the password if the username matches
    while (infile >> user.username >> user.password >> user.role) {
        if (user.username == username) {
            user.password = newPassword;  // Update the password for the found user
            updated = true;
        }
        tempFile << user.username << " " << user.password << " " << user.role << endl;
    }
    infile.close();
    tempFile.close();

    // Replace the original file with the temporary file
    if (updated) {
        remove("user.txt");  // Delete the original file
        rename("temp.txt", "user.txt");  // Rename temp file to original file
        cout << "Password has been reset successfully." << endl;
    } else {
        remove("temp.txt");  // Delete the temp file if no update occurred
        cout << "Error! Username not found." << endl;
    }
}

//
// Created by vertex laptop on 11/9/2024.
//
#ifndef REGISTERANDLOGINUSER_H
#define REGISTERANDLOGINUSER_H
#include <iostream>
using namespace std;
struct User {
    string username;
    string password;
    string role;  // "admin" or "employee"
};
void registerUser();
bool userExists(const string& username);
void saveUser(const User& user);
bool loginUser(User &user);
void forgotPassword();
void promptValidRole(string& role);
#endif //REGISTRATIONANDLOGINSYSTEM_H

//
// Created by vertex laptop on 11/9/2024.
//

#ifndef EMPLOYEEMANAGEMENT_H
#define EMPLOYEEMANAGEMENT_H
#include <iostream>
using namespace std;
//struct for employee information
struct Employee {
    int id;
    string name;
    string position;
    double salary;
};
void menuOfEmployeeSystem();
void addEmployee();
void viewEmployees();
void deleteEmployee();
void markAttendance();
void viewAttendance();




#endif //EMPLOYEEMANAGEMENT_H

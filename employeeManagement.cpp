//
// Created by vertex laptop on 11/9/2024.
//

#include "employeeManagement.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Employee structure to hold basic information
void menuOfEmployeeSystem() {
    int choice;
    do {
        //display menu options
        cout<<"\t\t\t\t\t----------------------------------------------"<<endl;
        cout<<"\t\t\t\t\t|--------EMPLOYEE  MANAGEMENT  SYSTEM--------|"<<endl;
        cout<<"\t\t\t\t\t----------------------------------------------"<<endl<<endl;
        cout<<"\t\t\t\t\t1- Add Employee"<<endl;
        cout<<"\t\t\t\t\t2- View Employees"<<endl;
        cout<<"\t\t\t\t\t3- Delete Employee"<<endl;
        cout<<"\t\t\t\t\t4- Mark Attendance"<<endl;
        cout<<"\t\t\t\t\t5- View Attendance"<<endl;
        cout<<"\t\t\t\t\t6- Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        //switch statement to handle different menu options
        switch (choice) {
            case 1:
                system("clear");//clear screen
                addEmployee();
            break;
            case 2:
                system("clear");
                viewEmployees();
            break;
            case 3:
                system("clear");
                deleteEmployee();
            break;
            case 4:
                system("clear");
                markAttendance();
            break;
            case 5:
                system("clear");
                viewAttendance();
            break;
            case 6:
                system("clear");
                cout<<"Exiting the system..."<<endl;
            break;
            default:
                system("clear");
                cout<<"Invalid choice! Please try again."<<endl;
        }
    } while (choice != 6);//exit when choice is 6
}
// Function to add a new employee
void addEmployee() {
    cout<<"\t\t\t\t\t------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------ADD EMPLOYEE--------|"<<endl;
    cout<<"\t\t\t\t\t------------------------------"<<endl<<endl;
    // Open the file in append mode to add new employee data at the end
    ofstream file("employees.txt", ios::app);
    Employee emp;
    // Gather employee information from the user
    cout<<"Enter Employee ID: ";
    cin>>emp.id;
    cin.ignore();// Ignore newline character left by previous input
    cout<<"Enter Employee Name: ";
    getline(cin, emp.name);
    cout<<"Enter Position: ";
    getline(cin, emp.position);
    cout<<"Enter Salary: $";
    cin>>emp.salary;
    // Write employee data to file
    if (file.is_open()) {
        file<<emp.id<<endl<<emp.name<<endl<<emp.position<<endl<<emp.salary<<endl;
        cout<<"Employee added successfully!"<<endl;
    }
    else {
        cout<<"Unable to open file for writing."<<endl;
    }
    file.close();
}
// Function to display all employees
void viewEmployees() {
    cout<<"\t\t\t\t\t------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------ALL EMPLOYEE--------|"<<endl;
    cout<<"\t\t\t\t\t------------------------------"<<endl<<endl;
    ifstream file("employees.txt");  // Open file in read mode
    Employee emp;// Temporary Employee object to hold data from the file
    string line;
    if (file.is_open()) {
        // Read each employee's data line-by-line
        while (getline(file,line)) {
            emp.id=stoi(line);
            getline(file,emp.name);
            getline(file,emp.position);
            getline(file,line);
            emp.salary=stod(line);
            // Display employee data
            cout<<"ID: "<<emp.id<<endl;
            cout<<"Name: "<<emp.name<<endl;
            cout<<"Position: "<<emp.position<<endl;
            cout<<"Salary: $"<<emp.salary<<endl;
            cout<<"----------------------------------------"<<endl;
        }
    } else {
        cout<<"Unable to open file for reading."<<endl;
    }
    file.close();
}
// Function to delete an employee by ID
void deleteEmployee() {
    cout<<"\t\t\t\t\t---------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------DELETE EMPLOYEE--------|"<<endl;
    cout<<"\t\t\t\t\t---------------------------------"<<endl<<endl;
    ifstream file("employees.txt");       // Open original file in read mode
    ofstream tempFile("temp.txt");        // Create a temporary file to store updated data
    int id;
    Employee emp;
    bool found=false;
    cout<<"Enter Employee ID to delete: ";
    cin>>id;
    string line;
    if (file.is_open() && tempFile.is_open()) {
        while (getline(file,line)) {
            emp.id=stoi(line);
            getline(file,emp.name);
            getline(file,emp.position);
            getline(file,line);
            emp.salary=stod(line);
            // If employee ID doesn't match the specified ID, copy to tempFile
            if (emp.id!=id) {
                tempFile<<emp.id<<endl<<emp.name<<endl<<emp.position<<endl<<emp.salary<<endl;
            }
            else {
                found=true;//mark not found
            }
        }
        file.close();
        tempFile.close();
        remove("employees.txt");           // Delete the original file
        rename("temp.txt", "employees.txt");  // Rename temporary file to original file name
        if (found) {
            cout<<"Employee deleted successfully!"<<endl;
        } else {
            cout<<"Employee not found!"<<endl;
        }
    } else {
        cout<<"Unable to open file."<<endl;
    }
}
//function for marking attendance
void markAttendance() {
    cout<<"\t\t\t\t\t---------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------MARK ATTENDANCE--------|"<<endl;
    cout<<"\t\t\t\t\t---------------------------------"<<endl<<endl;
    ifstream employeeFile("employees.txt");//read employee data
    string date;
    cout<<"Enter date for attendance (DD-MM-YYYY): ";
    cin>>date;
    // Create a new attendance file for the specified date
    ofstream attendanceFile("attendance_" + date + ".txt", ios::app);  // Create an attendance file for the specified date
    if (!employeeFile.is_open() || !attendanceFile.is_open()) {
        cout<<"Unable to open files for attendance."<<endl;
        return;
    }
    Employee emp;
    string status; string line;
    cout<<"Mark attendance for date: "<<date<<endl;
    cout<<"Enter 'P' for Present or 'A' for Absent."<<endl;
    // Iterate over each employee to mark their attendance
    while (getline(employeeFile,line)) {
        emp.id=stoi(line);
        getline(employeeFile,emp.name);
        getline(employeeFile,emp.position);
        getline(employeeFile,line);//read and discard salary line
        cout<<"Employee ID: "<<emp.id<<endl;
        cout<<"Name: "<<emp.name<<endl;
        cout<<"Status (P/A): ";
        cin>>status;
        // Validate input and save to file if valid
        if (status=="P" || status=="A") {
            attendanceFile<<emp.id<<endl<<emp.name<<endl<<status<<endl;
        } else {
            cout << "Invalid status, skipping." << endl;
        }
        cout<<"------------------------------------------"<<endl;
    }
    cout<<"Attendance marked for date: "<<date<<endl;
    employeeFile.close();
    attendanceFile.close();
}
// Function to view attendance for a specific date
void viewAttendance() {
    cout<<"\t\t\t\t\t---------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------VIEW ATTENDANCE--------|"<<endl;
    cout<<"\t\t\t\t\t---------------------------------"<<endl<<endl;
    string date;
    cout<<"Enter the date (DD-MM-YYYY) to view attendance: ";
    cin>>date;
    // Open attendance file for the specified date
    ifstream attendanceFile("attendance_" + date + ".txt");
    // Check if the file exists and is open
    if (!attendanceFile.is_open()) {
        cout<<"No attendance record found for the date: "<<date<<endl;
        return;
    }
    int id;
    string name,status;
    string line;
    // Display each attendance record
    while (getline(attendanceFile,line)) {
        id=stoi(line);//read and convert employee id
        getline(attendanceFile,name);
        getline(attendanceFile,status);
        cout<<"ID: "<<id<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Status: "<<status<<endl;
        cout<<"----------------------------"<<endl;
    }
    attendanceFile.close();
}
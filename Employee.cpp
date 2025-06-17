

#include "Employee.h"
Employee::Employee() : name(""), role(""), salary(0.0), performanceScore(0) {}

Employee::Employee(const string& name, const string& role, double salary, int performanceScore)
    : name(name), role(role), salary(salary), performanceScore(performanceScore) {}

Employee::~Employee() {}

// Getters
string Employee::getName() const { return name; }
string Employee::getRole() const { return role; }
double Employee::getSalary() const { return salary; }
int Employee::getPerformanceScore() const { return performanceScore; }

// Setters
void Employee::setName(const string& name) { this->name = name; }
void Employee::setRole(const string& role) { this->role = role; }
void Employee::setSalary(double salary) { this->salary = salary; }
void Employee::setPerformanceScore(int score) { this->performanceScore = score; }

// Methods from UML diagram
void Employee::displayInfo() const {
    cout << "\n--- Employee Information ---" << endl;
    cout << "Name: " << name << endl;
    cout << "Role: " << role << endl;
    cout << "Salary: $" << salary << endl;
    cout << "Performance Score: " << performanceScore << endl;
}

double Employee::calculateBonus() const {
    return salary * (performanceScore / 100.0);
}

// JSON conversion methods
json Employee::toJSON() const {
    json j;
    j["name"] = name;
    j["role"] = role;
    j["salary"] = salary;
    j["performanceScore"] = performanceScore;
    j["type"] = "Employee"; // For polymorphic reconstruction
    return j;
}

void Employee::fromJSON(const json& j) {
    name = j["name"];
    role = j["role"];
    salary = j["salary"];
    performanceScore = j["performanceScore"];
}
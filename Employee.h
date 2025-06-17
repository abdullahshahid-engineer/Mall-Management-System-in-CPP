

#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


class Employee {
protected:
    string name;
    string role;
    double salary;
    int performanceScore;

public:
    Employee();

    Employee(const string& name, const string& role, double salary, int performanceScore);

    virtual ~Employee();

    // Getters
    string getName() const;
    string getRole() const;
    double getSalary() const;
    int getPerformanceScore() const;

    // Setters
    void setName(const string& name);
    void setRole(const string& role);
    void setSalary(double salary);
    void setPerformanceScore(int score);

    // Methods from UML diagram
    virtual void displayInfo() const;

    virtual double calculateBonus() const;

    // JSON conversion methods
    json toJSON() const;

    virtual void fromJSON(const json& j) ;
};






#endif //EMPLOYEE_H

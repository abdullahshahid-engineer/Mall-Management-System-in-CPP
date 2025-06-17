

#ifndef EMPLOYEESTATS_H
#define EMPLOYEESTATS_H
#include <vector>
#include <iostream>
#include "Employee.h"
using namespace std;
template<typename T>
class EmployeeStats {
private:
    vector<Employee*>* employees;

public:
    EmployeeStats(vector<Employee*>* emps) : employees(emps) {}

    T calculateAverageSalary() const {
        if (employees->empty()) return 0;

        T total = 0;
        for (const auto& emp : *employees) {
            total += emp->getSalary();
        }
        return total / employees->size();
    }

    T calculateAveragePerformance() const {
        if (employees->empty()) return 0;

        T total = 0;
        for (const auto& emp : *employees) {
            total += emp->getPerformanceScore();
        }
        return total / employees->size();
    }

    void displayStats() const {
        cout << "\n=== Employee Statistics ===" << endl;
        cout << "Total employees: " << employees->size() << endl;
        cout << "Average salary: $" << calculateAverageSalary() << endl;
        cout << "Average performance score: " << calculateAveragePerformance() << endl;

        // Count employees by role
        int cashiers = 0, security = 0, managers = 0, others = 0;

        for (const auto& emp : *employees) {
            string role = emp->getRole();
            if (role == "Cashier") cashiers++;
            else if (role == "Security") security++;
            else if (role == "Manager") managers++;
            else others++;
        }

        cout << "Cashiers: " << cashiers << endl;
        cout << "Security personnel: " << security << endl;
        cout << "Managers: " << managers << endl;
        cout << "Other employees: " << others << endl;
    }
};






#endif //EMPLOYEESTATS_H

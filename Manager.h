//
// Created by Bismillah Traders on 4/29/2025.
//

#ifndef MANAGER_H
#define MANAGER_H
#include "Employee.h"
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class Manager : public Employee {
public:
    Manager();

    Manager(const string& name, double salary, int performanceScore);

    void manageOperations() const;

    void displayInfo() const override;

    double calculateBonus() const override;

    json toJSON() const;
};



#endif //MANAGER_H

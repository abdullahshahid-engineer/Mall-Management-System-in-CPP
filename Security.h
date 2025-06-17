//
// Created by Bismillah Traders on 4/29/2025.
//

#ifndef SECURITY_H
#define SECURITY_H
#include <iostream>
#include "Employee.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


class Security : public Employee {
public:
    Security();

    Security(const string& name, double salary, int performanceScore);

    void monitorSecurity() const;

    void displayInfo() const override ;

    double calculateBonus() const override;

    json toJSON() const;
};




#endif //SECURITY_H

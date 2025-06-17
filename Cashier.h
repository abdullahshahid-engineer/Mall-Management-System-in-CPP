//
// Created by Bismillah Traders on 4/29/2025.
//

#ifndef CASHIER_H
#define CASHIER_H
#include "Employee.h"
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


class Cashier : public Employee {
public:
    Cashier();

    Cashier(const string& name, double salary, int performanceScore);

    void processSales() const ;

    void displayInfo() const override;

    double calculateBonus() const override;

    json toJSON() const ;
};



#endif //CASHIER_H

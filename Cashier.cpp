//
// Created by Bismillah Traders on 4/29/2025.
//

#include "Cashier.h"
Cashier::Cashier() : Employee() {
    role = "Cashier";
}

Cashier::Cashier(const string& name, double salary, int performanceScore)
    : Employee(name, "Cashier", salary, performanceScore) {}

void Cashier::processSales() const {
    cout << "Cashier " << name << " is processing sales." << endl;
}

void Cashier::displayInfo() const {
    Employee::displayInfo();
    cout << "Position: Cashier" << endl;
}

double Cashier::calculateBonus() const {
    // Cashiers get a different bonus calculation
    return salary * 0.05 * (performanceScore / 100.0);
}

json Cashier::toJSON() const {
    json j = Employee::toJSON();
    j["type"] = "Cashier";
    return j;
}
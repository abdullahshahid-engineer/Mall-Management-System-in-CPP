//
// Created by Bismillah Traders on 4/29/2025.
//

#include "Manager.h"
Manager::Manager() : Employee() {
    role = "Manager";
}

Manager::Manager(const string& name, double salary, int performanceScore)
    : Employee(name, "Manager", salary, performanceScore) {}

void Manager::manageOperations() const {
    cout << "Manager " << name << " is managing operations." << endl;
}

void Manager::displayInfo() const  {
    Employee::displayInfo();
    cout << "Position: Manager" << endl;
}

double Manager::calculateBonus() const {
    // Managers get a higher bonus
    return salary * 0.1 * (performanceScore / 100.0);
}

json Manager::toJSON() const {
    json j = Employee::toJSON();
    j["type"] = "Manager";
    return j;
}
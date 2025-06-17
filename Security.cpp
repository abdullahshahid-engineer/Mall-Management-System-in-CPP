//
// Created by Bismillah Traders on 4/29/2025.
//

#include "Security.h"
Security::Security() : Employee() {
    role = "Security";
}

Security::Security(const string& name, double salary, int performanceScore)
    : Employee(name, "Security", salary, performanceScore) {}

void Security::monitorSecurity() const {
    cout << "Security " << name << " is monitoring the premises." << endl;
}

void Security::displayInfo() const {
    Employee::displayInfo();
    cout << "Position: Security Personnel" << endl;
}

double Security::calculateBonus() const {
    // Security personnel get a different bonus calculation
    return salary * 0.04 * (performanceScore / 100.0);
}

json Security::toJSON() const {
    json j = Employee::toJSON();
    j["type"] = "Security";
    return j;
}


#include "AccessController.h"
AccessController::AccessController() {}

void AccessController::grantAccess(Employee* emp) const {
    if (emp == nullptr) {
        cout << "Invalid employee reference." << endl;
        return;
    }

    cout << "Access granted to " << emp->getName() << " (" << emp->getRole() << ")" << endl;
}

// JSON conversion methods
json AccessController::toJSON() const {
    json j;
    return j; // No internal state to save
}

void AccessController::fromJSON(const json& j) {
    // No internal state to load
}
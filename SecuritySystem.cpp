
#include "SecuritySystem.h"
//SecuritySystem *SecuritySystem::instance=nullptr;
SecuritySystem* SecuritySystem::getInstance() {
    if (!instance) {
        instance = new SecuritySystem();
    }
    return instance;
}

// Destructor
SecuritySystem::~SecuritySystem() {
    // Cleanup if needed
}

// Getters from UML diagram
LogManager& SecuritySystem::getLogManager() {
    return logManager;
}

AccessController& SecuritySystem::getAccessController() {
    return accessController;
}

// Additional utility methods
void SecuritySystem::logSecurityEvent(const string& event) {
    logManager.addLog(event);
}

void SecuritySystem::authorizeEmployee(Employee* emp) {
    accessController.grantAccess(emp);
    logManager.addLog(emp->getName() + " was granted access at " + getCurrentTimeStamp());
}

string SecuritySystem::getCurrentTimeStamp() const {
    // Simple timestamp for logging
    time_t now = time(0);
    return ctime(&now);
}

// JSON conversion methods
void SecuritySystem::saveToFile(const string& filename) {
    json j;
    j["logManager"] = logManager.toJSON();

    ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4); // Pretty printing with 4-space indent
        file.close();
        cout << "Security system data saved to " << filename << " successfully." << endl;
    } else {
        cout << "Failed to open file for writing." << endl;
    }
}

void SecuritySystem::loadFromFile(const string& filename) {
    try {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File not found or couldn't be opened." << endl;
            return;
        }

        json j;
        file >> j;
        file.close();

        logManager.fromJSON(j["logManager"]);

        cout << "Security system data loaded from " << filename << " successfully." << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}
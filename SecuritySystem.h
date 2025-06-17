

#ifndef SECURITYSYSTEM_H
#define SECURITYSYSTEM_H

#include <iostream>
#include "AccessController.h"
#include "LogManager.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

class SecuritySystem {
private:
    static SecuritySystem* instance;
    LogManager logManager;
    AccessController accessController;

    // Private constructor for singleton pattern
    SecuritySystem() {}

public:
    // Delete copy constructor and assignment operator
    SecuritySystem(const SecuritySystem&) = delete;
    SecuritySystem& operator=(const SecuritySystem&) = delete;

    // Singleton getInstance method
    static SecuritySystem* getInstance() ;

    // Destructor
    ~SecuritySystem() ;

    // Getters from UML diagram
    LogManager& getLogManager() ;
    AccessController& getAccessController() ;

    // Additional utility methods
    void logSecurityEvent(const string& event) ;

    void authorizeEmployee(Employee* emp);
    string getCurrentTimeStamp() const;

    // JSON conversion methods
    void saveToFile(const string& filename);

    void loadFromFile(const string& filename);
};



#endif //SECURITYSYSTEM_H


#ifndef LOGMANAGER_H
#define LOGMANAGER_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


class LogManager {
private:
    vector<string> logs; // Using vector for log storage

public:
    LogManager() ;

    // Methods from UML diagram
    void addLog(const string& entry);

    void showLogs() const;

    // Operator overloading as shown in UML
    bool operator>(const LogManager& other) const;

    // JSON conversion methods
    json toJSON() const ;

    void fromJSON(const json& j) ;
};



#endif //LOGMANAGER_H

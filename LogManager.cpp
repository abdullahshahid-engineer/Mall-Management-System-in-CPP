

#include "LogManager.h"
LogManager::LogManager() {}

// Methods from UML diagram
void LogManager::addLog(const string& entry) {
    logs.push_back(entry);
    cout << "Log entry added: " << entry << endl;
}

void LogManager::showLogs() const {
    cout << "\n=== Security Logs ===" << endl;
    if (logs.empty()) {
        cout << "No logs recorded." << endl;
        return;
    }

    for (size_t i = 0; i < logs.size(); i++) {
        cout << i + 1 << ". " << logs[i] << endl;
    }
}

// Operator overloading as shown in UML
bool LogManager::operator>(const LogManager& other) const {
    return logs.size() > other.logs.size();
}

// JSON conversion methods
json LogManager::toJSON() const {
    json j;
    j["logs"] = logs;
    return j;
}

void LogManager::fromJSON(const json& j) {
    logs = j["logs"].get<vector<string>>();
}
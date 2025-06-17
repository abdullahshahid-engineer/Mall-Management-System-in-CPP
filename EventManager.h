

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <iostream>
#include "json.hpp"
#include "Event.h"
#include "Entertainment.h"
#include "EventStatistics.h"
#include <vector>
#include <fstream>
using namespace std;
using json = nlohmann::json;
class EventManager {
private:
    static EventManager* instance;
    vector<Event*> events;

    // Private constructor for singleton pattern
    EventManager() {}

public:
    // Get singleton instance
    static EventManager* getInstance(){
        if (!instance) {
            instance = new EventManager();
        }
        return instance;
    }

    // Destructor
    ~EventManager();

    // Add event
    void addEvent(Event* event);

    // Remove event
    bool removeEvent(int eventId);

    // Get event by ID
    Event* getEventById(int eventId);

    // Get all events
    vector<Event*>& getAllEvents();

    // Display all events
    void displayAllEvents() const;

    // Sort events by date
    void sortEventsByDate();

    // Save events to JSON file
    void saveEventsToFile(const string& filename);

    // Load events from JSON file
    void loadEventsFromFile(const string& filename);

    // Get statistics
    EventStatistics<double>* getStatistics();
};

string getCurrentDate();
void eventManagementMenu();

#endif //EVENTMANAGER_H

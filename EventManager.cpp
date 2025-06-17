

#include "EventManager.h"
// Initialize static instance
EventManager* EventManager::instance = nullptr;

    // Destructor
EventManager::~EventManager() {
    for (auto event : events) {
        delete event;
    }
    events.clear();
}

    // Add event
void EventManager::addEvent(Event* event) {
    events.push_back(event);
}

    // Remove event
bool EventManager::removeEvent(int eventId) {
    for (auto it = events.begin(); it != events.end(); ++it) {
        if ((*it)->getEventId() == eventId) {
            delete *it;
            events.erase(it);
            return true;
        }
    }
    return false;
}

    // Get event by ID
Event* EventManager::getEventById(int eventId) {
    for (auto event : events) {
        if (event->getEventId() == eventId) {
            return event;
        }
    }
    return nullptr;
}

    // Get all events
vector<Event*>& EventManager::getAllEvents() {
    return events;
}

    // Display all events
void EventManager::displayAllEvents() const {
    cout << "\n=== All Events ===" << endl;
    if (events.empty()) {
        cout << "No events found." << endl;
        return;
    }

    for (const auto& event : events) {
        event->displayInfo();
        cout << "------------------------" << endl;
    }
}

    // Sort events by date
void EventManager::sortEventsByDate() {
    sort(events.begin(), events.end(), [](const Event* a, const Event* b) {
        return *a < *b;
    });
}

    // Save events to JSON file
void EventManager::saveEventsToFile(const string& filename) {
    json j;
    j["events"] = json::array();

    for (const auto& event : events) {
        j["events"].push_back(event->toJSON());
    }

    ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
        cout << "Events saved to " << filename << " successfully." << endl;
    } else {
        cout << "Failed to open file for writing." << endl;
    }
}

    // Load events from JSON file
void EventManager::loadEventsFromFile(const string& filename) {
    // Clear existing events
    for (auto event : events) {
        delete event;
    }
    events.clear();

    try {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File not found or couldn't be opened." << endl;
            return;
        }

        json j;
        file >> j;
        file.close();

        for (const auto& eventJson : j["events"]) {
            string type = eventJson["type"];
            Event* event = nullptr;

            if (type == "Entertainment") {
                event = new Entertainment();
            } else {
                event = new Event();
            }

            event->fromJSON(eventJson);
            events.push_back(event);
        }

        cout << "Events loaded from " << filename << " successfully." << endl;
    } catch (const exception& e) {
        cout << "Error loading events: " << e.what() << endl;
    }
}

    // Get statistics
EventStatistics<double>* EventManager::getStatistics() {
    return new EventStatistics<double>(&events);
}

string getCurrentDate() {
    // In a real application, you'd get the current date from system
    // Since we're not including ctime, use a placeholder
    return "2025-04-25";
}

void eventManagementMenu() {
    EventManager* eventManager = EventManager::getInstance();
    int choice;

    do {
        cout << "\n===== EVENT MANAGEMENT MENU =====" << endl;
        cout << "1. Add New Event" << endl;
        cout << "2. Add New Entertainment Event" << endl;
        cout << "3. Display All Events" << endl;
        cout << "4. Find Event by ID" << endl;
        cout << "5. Remove Event" << endl;
        cout << "6. View Event Statistics" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Add new general event
                int id;
                string name, description, date, time, location;
                double price;
                int capacity;

                cout << "\nEnter Event ID: ";
                cin >> id;
                cin.ignore();

                // Check if event with this ID already exists
                if (eventManager->getEventById(id)) {
                    cout << "Event with this ID already exists." << endl;
                    break;
                }

                cout << "Enter Event Name: ";
                getline(cin, name);

                cout << "Enter Description: ";
                getline(cin, description);

                cout << "Enter Date (YYYY-MM-DD): ";
                getline(cin, date);

                cout << "Enter Time (HH:MM): ";
                getline(cin, time);

                cout << "Enter Location: ";
                getline(cin, location);

                cout << "Enter Ticket Price: $";
                cin >> price;

                cout << "Enter Capacity: ";
                cin >> capacity;

                Event* event = new Event(id, name, description, date, time, location, price, capacity);
                eventManager->addEvent(event);

                cout << "Event added successfully!" << endl;
                break;
            }
            case 2: {
                // Add new entertainment event
                int id;
                string name, description, date, time, location;
                double price;
                int capacity;
                string type, artist, genre;
                int duration;

                cout << "\nEnter Entertainment Event ID: ";
                cin >> id;
                cin.ignore();

                // Check if event with this ID already exists
                if (eventManager->getEventById(id)) {
                    cout << "Event with this ID already exists." << endl;
                    break;
                }

                cout << "Enter Event Name: ";
                getline(cin, name);

                cout << "Enter Description: ";
                getline(cin, description);

                cout << "Enter Date (YYYY-MM-DD): ";
                getline(cin, date);

                cout << "Enter Time (HH:MM): ";
                getline(cin, time);

                cout << "Enter Location: ";
                getline(cin, location);

                cout << "Enter Ticket Price: $";
                cin >> price;

                cout << "Enter Capacity: ";
                cin >> capacity;

                cin.ignore();
                cout << "Enter Entertainment Type (Concert, Movie, Play, etc.): ";
                getline(cin, type);

                cout << "Enter Artist/Performer: ";
                getline(cin, artist);

                cout << "Enter Duration (minutes): ";
                cin >> duration;

                cin.ignore();
                cout << "Enter Genre: ";
                getline(cin, genre);

                Entertainment* entertainment = new Entertainment(id, name, description, date, time, location,
                                                               price, capacity, type, artist, duration, genre);
                eventManager->addEvent(entertainment);

                cout << "Entertainment event added successfully!" << endl;
                break;
            }
            case 3:
                // Display all events
                eventManager->displayAllEvents();
                break;
            case 4: {
                // Find event by ID
                int id;
                cout << "\nEnter Event ID to find: ";
                cin >> id;

                Event* event = eventManager->getEventById(id);
                if (event) {
                    event->displayInfo();
                } else {
                    cout << "Event not found." << endl;
                }
                break;
            }
            case 5: {
                // Remove event
                int id;
                cout << "\nEnter Event ID to remove: ";
                cin >> id;

                if (eventManager->removeEvent(id)) {
                    cout << "Event removed successfully!" << endl;
                } else {
                    cout << "Event not found." << endl;
                }
                break;
            }
            case 6: {
                // View event statistics
                EventStatistics<double>* stats = eventManager->getStatistics();
                stats->displayStatistics();
                delete stats;
                break;
            }
            case 0:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}
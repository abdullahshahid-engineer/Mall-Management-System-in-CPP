

#include "Event.h"
Event::Event()
        : eventId(0), eventName(""), description(""), date(""), time(""),
          location(""), ticketPrice(0.0), capacity(0), bookedSeats(0) {}

Event::Event(int id, const string& name, const string& desc, const string& dt,
          const string& tm, const string& loc, double price, int cap)
        : eventId(id), eventName(name), description(desc), date(dt),
          time(tm), location(loc), ticketPrice(price), capacity(cap), bookedSeats(0) {}

Event::~Event() {}

// Getters
int Event::getEventId() const { return eventId; }
string Event::getEventName() const { return eventName; }
string Event::getDescription() const { return description; }
string Event::getDate() const { return date; }
string Event::getTime() const { return time; }
string Event::getLocation() const { return location; }
double Event::getTicketPrice() const { return ticketPrice; }
int Event::getCapacity() const { return capacity; }
int Event::getBookedSeats() const { return bookedSeats; }
int Event::getAvailableSeats() const { return capacity - bookedSeats; }

// Setters
void Event::setEventId(int id) { eventId = id; }
void Event::setEventName(const string& name) { eventName = name; }
void Event::setDescription(const string& desc) { description = desc; }
void Event::setDate(const string& dt) { date = dt; }
void Event::setTime(const string& tm) { time = tm; }
void Event::setLocation(const string& loc) { location = loc; }
void Event::setTicketPrice(double price) { ticketPrice = price; }
void Event::setCapacity(int cap) { capacity = cap; }
void Event::setBookedSeats(int seats) { bookedSeats = seats; }

    // Book seats method
bool Event::bookSeats(int numSeats) {
    if (numSeats <= getAvailableSeats()) {
        bookedSeats += numSeats;
        return true;
    }
    return false;
}

    // Cancel booking method
bool Event::cancelBooking(int numSeats) {
    if (numSeats <= bookedSeats) {
        bookedSeats -= numSeats;
        return true;
    }
    return false;
}

    // Polymorphic display method
void Event::displayInfo() const {
    cout << "\n--- Event Information ---" << endl;
    cout << "Event ID: " << eventId << endl;
    cout << "Name: " << eventName << endl;
    cout << "Description: " << description << endl;
    cout << "Date: " << date << endl;
    cout << "Time: " << time << endl;
    cout << "Location: " << location << endl;
    cout << "Ticket Price: $" << ticketPrice << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Available Seats: " << getAvailableSeats() << endl;
}

    // Polymorphic method to get event type
string Event::getEventType() const { return "General"; }

    // JSON serialization
json Event::toJSON() const {
    json j;
    j["eventId"] = eventId;
    j["eventName"] = eventName;
    j["description"] = description;
    j["date"] = date;
    j["time"] = time;
    j["location"] = location;
    j["ticketPrice"] = ticketPrice;
    j["capacity"] = capacity;
    j["bookedSeats"] = bookedSeats;
    j["type"] = getEventType();
    return j;
}

    // JSON deserialization
void Event::fromJSON(const json& j) {
    eventId = j["eventId"];
    eventName = j["eventName"];
    description = j["description"];
    date = j["date"];
    time = j["time"];
    location = j["location"];
    ticketPrice = j["ticketPrice"];
    capacity = j["capacity"];
    bookedSeats = j["bookedSeats"];
}

    // Operator overloading for comparison
bool Event::operator==(const Event& other) const {
    return eventId == other.eventId;
}

bool Event::operator!=(const Event& other) const {
    return !(*this == other);
}

    // Operator overloading for comparison by date
bool Event::operator<(const Event& other) const {
    return date < other.date;
}
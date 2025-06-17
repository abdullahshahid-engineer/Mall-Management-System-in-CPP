

#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class Event {
protected:
    int eventId;
    string eventName;
    string description;
    string date;
    string time;
    string location;
    double ticketPrice;
    int capacity;
    int bookedSeats;

public:
    Event();

    Event(int id, const string& name, const string& desc, const string& dt,
          const string& tm, const string& loc, double price, int cap);

    virtual ~Event();

    // Getters
    int getEventId() const;
    string getEventName() const;
    string getDescription() const;
    string getDate() const;
    string getTime() const;
    string getLocation() const;
    double getTicketPrice() const;
    int getCapacity() const;
    int getBookedSeats() const ;
    int getAvailableSeats() const;

    // Setters
    void setEventId(int id);
    void setEventName(const string& name);
    void setDescription(const string& desc);
    void setDate(const string& dt);
    void setTime(const string& tm);
    void setLocation(const string& loc);
    void setTicketPrice(double price);
    void setCapacity(int cap);
    void setBookedSeats(int seats);

    // Book seats method
    bool bookSeats(int numSeats);

    // Cancel booking method
    bool cancelBooking(int numSeats);

    // Polymorphic display method
    virtual void displayInfo() const;

    // Polymorphic method to get event type
    virtual string getEventType() const;

    // JSON serialization
    virtual json toJSON() const;

    // JSON deserialization
    virtual void fromJSON(const json& j);

    // Operator overloading for comparison
    bool operator==(const Event& other) const;

    bool operator!=(const Event& other) const;

    // Operator overloading for comparison by date
    bool operator<(const Event& other) const;
};



#endif //EVENT_H

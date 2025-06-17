

#ifndef BOOKING_H
#define BOOKING_H
#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class Booking {
private:
    int bookingId;
    int eventId;
    int customerId;
    string bookingDate;
    int numTickets;
    double totalAmount;
    bool isPaid;

public:
    Booking();

    Booking(int bId, int eId, int cId, const string& date, int tickets, double amount);

    // Getters
    int getBookingId() const;
    int getEventId() const;
    int getCustomerId() const;
    string getBookingDate() const;
    int getNumTickets() const;
    double getTotalAmount() const;
    bool getIsPaid() const;

    // Setters
    void setBookingId(int id);
    void setEventId(int id);
    void setCustomerId(int id);
    void setBookingDate(const string& date);
    void setNumTickets(int tickets);
    void setTotalAmount(double amount);
    void setIsPaid(bool paid);

    // Process payment
    bool processPayment() ;

    // Display booking information
    void displayInfo() const ;

    // JSON serialization
    json toJSON() const ;

    // JSON deserialization
    void fromJSON(const json& j);

    // Operator overloading
    bool operator==(const Booking& other) const;
};




#endif //BOOKING_H

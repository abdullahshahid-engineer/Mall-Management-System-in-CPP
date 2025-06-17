

#include "Booking.h"
Booking::Booking()
        : bookingId(0), eventId(0), customerId(0), bookingDate(""),
          numTickets(0), totalAmount(0.0), isPaid(false) {}

Booking::Booking(int bId, int eId, int cId, const string& date, int tickets, double amount)
        : bookingId(bId), eventId(eId), customerId(cId), bookingDate(date),
          numTickets(tickets), totalAmount(amount), isPaid(false) {}

    // Getters
int Booking::getBookingId() const { return bookingId; }
int Booking::getEventId() const { return eventId; }
int Booking::getCustomerId() const { return customerId; }
string Booking::getBookingDate() const { return bookingDate; }
int Booking::getNumTickets() const { return numTickets; }
double Booking::getTotalAmount() const { return totalAmount; }
bool Booking::getIsPaid() const { return isPaid; }

    // Setters
void Booking::setBookingId(int id) { bookingId = id; }
void Booking::setEventId(int id) { eventId = id; }
void Booking::setCustomerId(int id) { customerId = id; }
void Booking::setBookingDate(const string& date) { bookingDate = date; }
void Booking::setNumTickets(int tickets) { numTickets = tickets; }
void Booking::setTotalAmount(double amount) { totalAmount = amount; }
void Booking::setIsPaid(bool paid) { isPaid = paid; }

    // Process payment
bool Booking::processPayment() {
    isPaid = true;
    return isPaid;
}

    // Display booking information
void Booking::displayInfo() const {
    cout << "\n--- Booking Information ---" << endl;
    cout << "Booking ID: " << bookingId << endl;
    cout << "Event ID: " << eventId << endl;
    cout << "Customer ID: " << customerId << endl;
    cout << "Booking Date: " << bookingDate << endl;
    cout << "Number of Tickets: " << numTickets << endl;
    cout << "Total Amount: $" << totalAmount << endl;
    cout << "Payment Status: " << (isPaid ? "Paid" : "Unpaid") << endl;
}

    // JSON serialization
json Booking::toJSON() const {
    json j;
    j["bookingId"] = bookingId;
    j["eventId"] = eventId;
    j["customerId"] = customerId;
    j["bookingDate"] = bookingDate;
    j["numTickets"] = numTickets;
    j["totalAmount"] = totalAmount;
    j["isPaid"] = isPaid;
    return j;
}

    // JSON deserialization
void Booking::fromJSON(const json& j) {
    bookingId = j["bookingId"];
    eventId = j["eventId"];
    customerId = j["customerId"];
    bookingDate = j["bookingDate"];
    numTickets = j["numTickets"];
    totalAmount = j["totalAmount"];
    isPaid = j["isPaid"];
}

    // Operator overloading
bool Booking::operator==(const Booking& other) const {
    return bookingId == other.bookingId;
}
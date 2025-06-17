

#ifndef ONLINEBOOKINGSYSTEM_H
#define ONLINEBOOKINGSYSTEM_H
#include <iostream>
#include "json.hpp"
#include "Event.h"
#include "Booking.h"
#include "EventManager.h"
#include <vector>
#include <fstream>
#include "CustomerSalesSystem.h"
using namespace std;
using json = nlohmann::json;
class Mall;
class OnlineBookingSystem {
private:
    static OnlineBookingSystem* instance;
    vector<Booking*> bookings;
    EventManager* eventManager;
    Mall* mall;

    // Private constructor for singleton pattern
    OnlineBookingSystem() {
        eventManager = EventManager::getInstance();
        //mall = Mall::getInstance();
    }

public:
    // Get singleton instance
    static OnlineBookingSystem* getInstance() {
        if (!instance) {
            instance = new OnlineBookingSystem();
        }
        return instance;
    }

    // Destructor
    ~OnlineBookingSystem() {
        for (auto booking : bookings) {
            delete booking;
        }
        bookings.clear();
    }

    // Create booking
    bool createBooking(int customerId, int eventId, int numTickets, const string& bookingDate) {
        // Find the event
        Event* event = eventManager->getEventById(eventId);
        if (!event) {
            cout << "Event not found." << endl;
            return false;
        }

        // Check seat availability
        if (!event->bookSeats(numTickets)) {
            cout << "Not enough seats available." << endl;
            return false;
        }

        // Generate booking ID
        int bookingId = bookings.empty() ? 1 : bookings.back()->getBookingId() + 1;

        // Calculate total amount
        double totalAmount = event->getTicketPrice() * numTickets;

        // Create the booking
        Booking* booking = new Booking(bookingId, eventId, customerId, bookingDate, numTickets, totalAmount);
        bookings.push_back(booking);

        cout << "Booking created successfully!" << endl;
        booking->displayInfo();

        return true;
    }

    // Cancel booking
    bool cancelBooking(int bookingId) {
        for (auto it = bookings.begin(); it != bookings.end(); ++it) {
            if ((*it)->getBookingId() == bookingId) {
                // Find the event and return seats
                Event* event = eventManager->getEventById((*it)->getEventId());
                if (event) {
                    event->cancelBooking((*it)->getNumTickets());
                }

                // Delete and remove the booking
                delete *it;
                bookings.erase(it);

                cout << "Booking cancelled successfully!" << endl;
                return true;
            }
        }

        cout << "Booking not found." << endl;
        return false;
    }

    // Process payment for booking
    bool processPayment(int bookingId) {
        for (auto booking : bookings) {
            if (booking->getBookingId() == bookingId) {
                if (booking->getIsPaid()) {
                    cout << "Booking already paid." << endl;
                    return true;
                }

                booking->processPayment();
                cout << "Payment processed successfully!" << endl;
                return true;
            }
        }

        cout << "Booking not found." << endl;
        return false;
    }

    // Get booking by ID
    Booking* getBookingById(int bookingId) {
        for (auto booking : bookings) {
            if (booking->getBookingId() == bookingId) {
                return booking;
            }
        }
        return nullptr;
    }

    // Get bookings by customer ID
    vector<Booking*> getBookingsByCustomerId(int customerId) {
        vector<Booking*> customerBookings;
        for (auto booking : bookings) {
            if (booking->getCustomerId() == customerId) {
                customerBookings.push_back(booking);
            }
        }
        return customerBookings;
    }

    // Display all bookings
    void displayAllBookings() const {
        cout << "\n=== All Bookings ===" << endl;
        if (bookings.empty()) {
            cout << "No bookings found." << endl;
            return;
        }

        for (const auto& booking : bookings) {
            booking->displayInfo();
            cout << "------------------------" << endl;
        }
    }

    // Display customer bookings
    void displayCustomerBookings(int customerId) const {
        cout << "\n=== Bookings for Customer ID " << customerId << " ===" << endl;
        bool found = false;

        for (const auto& booking : bookings) {
            if (booking->getCustomerId() == customerId) {
                booking->displayInfo();
                cout << "------------------------" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No bookings found for this customer." << endl;
        }
    }

    // Save bookings to JSON file
    void saveBookingsToFile(const string& filename) {
        json j;
        j["bookings"] = json::array();

        for (const auto& booking : bookings) {
            j["bookings"].push_back(booking->toJSON());
        }

        ofstream file(filename);
        if (file.is_open()) {
            file << j.dump(4);
            file.close();
            cout << "Bookings saved to " << filename << " successfully." << endl;
        } else {
            cout << "Failed to open file for writing." << endl;
        }
    }

    // Load bookings from JSON file
    void loadBookingsFromFile(const string& filename) {
        // Clear existing bookings
        for (auto booking : bookings) {
            delete booking;
        }
        bookings.clear();

        try {
            ifstream file(filename);
            if (!file.is_open()) {
                cout << "File not found or couldn't be opened." << endl;
                return;
            }

            json j;
            file >> j;
            file.close();

            for (const auto& bookingJson : j["bookings"]) {
                Booking* booking = new Booking();
                booking->fromJSON(bookingJson);
                bookings.push_back(booking);

                // Update event booked seats
                Event* event = eventManager->getEventById(booking->getEventId());
                if (event) {
                    event->setBookedSeats(event->getBookedSeats() + booking->getNumTickets());
                }
            }

            cout << "Bookings loaded from " << filename << " successfully." << endl;
        } catch (const exception& e) {
            cout << "Error loading bookings: " << e.what() << endl;
        }
    }
};
void bookingManagementMenu();
void eventAndBookingMenu(Mall* mall);



#endif //ONLINEBOOKINGSYSTEM_H

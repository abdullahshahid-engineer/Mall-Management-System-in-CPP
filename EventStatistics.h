

#ifndef EVENTSTATISTICS_H
#define EVENTSTATISTICS_H
#include <iostream>
#include <vector>
#include "Event.h"
using namespace std;
template <typename T>
class EventStatistics {
private:
    vector<Event*>* events;

public:
    EventStatistics(vector<Event*>* evts) : events(evts) {}

    // Calculate average ticket price
    T calculateAverageTicketPrice() const {
        if (events->empty()) return 0;

        T totalPrice = 0;
        for (const auto& event : *events) {
            totalPrice += event->getTicketPrice();
        }
        return totalPrice / events->size();
    }

    // Calculate total revenue potential
    T calculateTotalRevenuePotential() const {
        T totalRevenue = 0;
        for (const auto& event : *events) {
            totalRevenue += event->getTicketPrice() * event->getCapacity();
        }
        return totalRevenue;
    }

    // Calculate current revenue
    T calculateCurrentRevenue() const {
        T currentRevenue = 0;
        for (const auto& event : *events) {
            currentRevenue += event->getTicketPrice() * event->getBookedSeats();
        }
        return currentRevenue;
    }

    // Calculate booking percentage
    T calculateBookingPercentage() const {
        if (events->empty()) return 0;

        T totalSeats = 0;
        T totalBooked = 0;

        for (const auto& event : *events) {
            totalSeats += event->getCapacity();
            totalBooked += event->getBookedSeats();
        }

        if (totalSeats == 0) return 0;
        return (totalBooked / totalSeats) * 100;
    }

    // Display statistics
    void displayStatistics() const {
        cout << "\n=== Event Statistics ===" << endl;
        cout << "Total Events: " << events->size() << endl;
        cout << "Average Ticket Price: $" << calculateAverageTicketPrice() << endl;
        cout << "Total Revenue Potential: $" << calculateTotalRevenuePotential() << endl;
        cout << "Current Revenue: $" << calculateCurrentRevenue() << endl;
        cout << "Booking Percentage: " << calculateBookingPercentage() << "%" << endl;
    }
};

#endif //EVENTSTATISTICS_H

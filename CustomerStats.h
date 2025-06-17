

#ifndef CUSTOMERSTATS_H
#define CUSTOMERSTATS_H
#include<iostream>
#include<vector>
using namespace std;
#include"Customer.h"
template <typename T>
class CustomerStats {
private:
    vector<Customer*>* customers;
    static CustomerStats<T>* instance;

    CustomerStats() : customers(nullptr) {}

public:
    static CustomerStats<T>* getInstance(vector<Customer*>* custs) {
        if (!instance) {
            instance = new CustomerStats<T>();
            instance->customers = custs;
        }
        return instance;
    }

    ~CustomerStats() {
        // Do not delete customers as they are owned elsewhere
    }

    T calculateTotalCustomers() {
        return static_cast<T>(customers->size());
    }

    T calculateVIPPercentage() {
        if (customers->empty()) return 0;

        int vipCount = 0;
        for (const auto& customer : *customers) {
            if (customer->getMembershipStatus() == "VIP") {
                vipCount++;
            }
        }

        return static_cast<T>(vipCount) / static_cast<T>(customers->size()) * 100;
    }

    void displayStatistics() {
        cout << "\n=== Customer Statistics ===" << endl;
        cout << "Total Customers: " << calculateTotalCustomers() << endl;
        cout << "VIP Percentage: " << calculateVIPPercentage() <<"%"<< endl;

        // Count by membership status
        int regularCount = 0,  vipCount = 0;

        for (const auto& customer : *customers) {
            if (customer->getMembershipStatus() == "Regular") {
                regularCount++;
            } else if (customer->getMembershipStatus() == "VIP") {
                vipCount++;
            }
        }
        cout << "Regular Customers: " << regularCount << endl;
        cout << "VIP Customers: " << vipCount << endl;
    }
};

// Initialize the static member
template <typename T>
CustomerStats<T>* CustomerStats<T>::instance = nullptr;
#endif //CUSTOMERSTATS_H

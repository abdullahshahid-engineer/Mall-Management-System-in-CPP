

#include "VIPCustomer.h"
VIPCustomer::VIPCustomer() : Customer(), loyaltyPoints(0) {}
VIPCustomer::VIPCustomer(int id, const string& name, int points )
    : Customer(id, name, "VIP"), loyaltyPoints(points) {}

int VIPCustomer::getLoyaltyPoints() const { return loyaltyPoints; }
void VIPCustomer::setLoyaltyPoints(int points) { loyaltyPoints = points; }

void VIPCustomer::addLoyaltyPoints(int points) {
    loyaltyPoints += points;
    cout << points << " loyalty points added. Total: " << loyaltyPoints << endl;
}

int VIPCustomer::checkLoyaltyPoints() {
    cout << "Current loyalty points: " << loyaltyPoints << endl;
    return loyaltyPoints;
}

float VIPCustomer::applyDiscountBasedOnPoints() {
    float discount = 0.0f;
    if (loyaltyPoints >= 1000) {
        discount = 0.20f; // 20% discount
    } else if (loyaltyPoints >= 500) {
        discount = 0.15f; // 15% discount
    } else if (loyaltyPoints >= 100) {
        discount = 0.10f; // 10% discount
    }
    cout << "Applied discount of " << discount * 100 << "% based on loyalty points." << endl;
    return discount;
}

void VIPCustomer::displayInfo() const  {
    Customer::displayInfo();
    cout << "Loyalty Points: " << loyaltyPoints << endl;
}

json VIPCustomer::toJSON() const {
    json j = Customer::toJSON();
    j["loyaltyPoints"] = loyaltyPoints;
    j["type"] = "vip";
    return j;
}

void VIPCustomer::fromJSON(const json& j)  {
    Customer::fromJSON(j);
    loyaltyPoints = j["loyaltyPoints"];
}
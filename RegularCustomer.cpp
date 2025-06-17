

#include "RegularCustomer.h"
RegularCustomer::RegularCustomer() : Customer() {}
RegularCustomer::RegularCustomer(int id, const string& name) : Customer(id, name, "Regular") {}

void RegularCustomer::welcomeMessage() {
    cout << "Welcome " << name << "! Thank you for shopping with us." << endl;
}


json RegularCustomer::toJSON() const {
    json j = Customer::toJSON();
    j["type"] = "regular";
    return j;
}
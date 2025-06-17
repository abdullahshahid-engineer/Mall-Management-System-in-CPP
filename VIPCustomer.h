

#ifndef VIPCUSTOMER_H
#define VIPCUSTOMER_H
#include<iostream>
#include "Customer.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class VIPCustomer : public Customer {
private:
    int loyaltyPoints;

public:
    VIPCustomer();
    VIPCustomer(int id, const string& name, int points = 0);

    int getLoyaltyPoints() const ;
    void setLoyaltyPoints(int points);

    void addLoyaltyPoints(int points);

    int checkLoyaltyPoints();

    float applyDiscountBasedOnPoints();

    void displayInfo() const override;

    json toJSON() const override;

    void fromJSON(const json& j) override;
};




#endif //VIPCUSTOMER_H

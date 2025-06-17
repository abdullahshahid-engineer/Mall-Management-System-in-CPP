

#ifndef REGULARCUSTOMER_H
#define REGULARCUSTOMER_H
#include<iostream>
#include "Customer.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


class RegularCustomer : public Customer {
public:
    RegularCustomer();
    RegularCustomer(int id, const string& name);

    void welcomeMessage();


    json toJSON() const override;
};




#endif //REGULARCUSTOMER_H

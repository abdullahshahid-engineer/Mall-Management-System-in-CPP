

#ifndef PAYMENTMETHOD_H
#define PAYMENTMETHOD_H
#include <iostream>
#include <string>
using namespace std;
#include "json.hpp"
using json = nlohmann::json;

class PaymentMethod {
private:
    string methodType;
public:
    PaymentMethod();
    PaymentMethod(const string& type);

    string getMethodType() const;
    void setMethodType(const string& type);

    bool processPayment(float amount);

    json toJSON() const;

    void fromJSON(const json& j);
};




#endif //PAYMENTMETHOD_H



#include "PaymentMethod.h"
PaymentMethod::PaymentMethod() : methodType("") {}
PaymentMethod::PaymentMethod(const string& type) : methodType(type) {}

string PaymentMethod::getMethodType() const { return methodType; }
void PaymentMethod::setMethodType(const string& type) { methodType = type; }

bool PaymentMethod::processPayment(float amount) {
    cout << "Processing payment of $" << amount << " using " << methodType << endl;
    return true;
}

json PaymentMethod::toJSON() const {
    json j;
    j["methodType"] = methodType;
    return j;
}

void PaymentMethod::fromJSON(const json& j) {
    methodType = j["methodType"];
}
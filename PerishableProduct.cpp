//
// Created by dell on 4/17/2025.
//

#include "PerishableProduct.h"
PerishableProduct::PerishableProduct() : Product(), expiryDate("") {}

PerishableProduct::PerishableProduct(int i, const std::string& n, double p, int sid, int q, const std::string& cat, const std::string& exp)
    : Product(i, n, p, sid, q, cat), expiryDate(exp) {}

// Getters and setters
string PerishableProduct::getExpiryDate() const {
    return expiryDate;
}
void PerishableProduct::setExpiryDate(const std::string& exp) {
    expiryDate=exp;
}

// Override display info
void PerishableProduct::displayInfo() const {
    Product::displayInfo();
    cout << "Expiry Date: " << expiryDate << endl;
}
Product* PerishableProduct::clone() const {
    return new PerishableProduct(*this);
}

// Override availability check
bool PerishableProduct::checkAvailability() const {
    return quantity > 0;
}
json PerishableProduct::toJSON() const {
    json j = Product::toJSON();
    j["type"] = "perishable";
    j["expiryDate"] = expiryDate;
    return j;
}

void PerishableProduct::fromJSON(const json& j) {
    Product::fromJSON(j);
    expiryDate = j.at("expiryDate").get<string>();
}
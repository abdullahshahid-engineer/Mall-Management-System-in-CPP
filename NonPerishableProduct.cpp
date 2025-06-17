//
// Created by dell on 4/17/2025.
//

#include "NonPerishableProduct.h"
// Constructors
NonPerishableProduct::NonPerishableProduct() : Product(), warrantyPeriod(0) {}

NonPerishableProduct::NonPerishableProduct(int i, const string& n, double p, int sid, int q, const string& cat, int wp)
    : Product(i, n, p, sid, q, cat), warrantyPeriod(wp) {}

// Getters and setters
int NonPerishableProduct::getWarrantyPeriod() const {
    return warrantyPeriod;
}
void NonPerishableProduct::setWarrantyPeriod(int wp) {
    warrantyPeriod = wp;
}

Product* NonPerishableProduct::clone() const {
    return new NonPerishableProduct(*this);
}
// Override display info
void NonPerishableProduct::displayInfo() const {
    Product::displayInfo();
    cout << "Warranty Period: " << warrantyPeriod << " months" << endl;
}
json NonPerishableProduct::toJSON() const {
    json j = Product::toJSON();
    j["type"] = "nonperishable";
    j["warrantyPeriod"] = warrantyPeriod;
    return j;
}

void NonPerishableProduct::fromJSON(const json& j) {
    Product::fromJSON(j);
    warrantyPeriod = j.at("warrantyPeriod").get<int>();
}

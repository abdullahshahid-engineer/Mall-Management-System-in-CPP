//
// Created by dell on 4/17/2025.
//

#ifndef PERISHABLEPRODUCT_H
#define PERISHABLEPRODUCT_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Product.h"
using namespace std;


class PerishableProduct : public Product {
private:
    string expiryDate;
public:
    // Constructors
    PerishableProduct();

    PerishableProduct(int i, const string& n, double p, int sid, int q, const string& cat, const string& exp);

    // Getters and setters
    string getExpiryDate() const;
    void setExpiryDate(const string& exp);

     // Override display info
    void displayInfo() const override;
    virtual Product* clone() const;
    json toJSON() const override;
    void fromJSON(const json& j) override;

    // Override availability check
    bool checkAvailability() const override;
};

#endif //PERISHABLEPRODUCT_H

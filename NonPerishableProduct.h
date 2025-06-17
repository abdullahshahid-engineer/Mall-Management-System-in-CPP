//
// Created by dell on 4/17/2025.
//

#ifndef NONPERISHABLEPRODUCT_H
#define NONPERISHABLEPRODUCT_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Product.h"
using namespace std;
class NonPerishableProduct : public Product {
private:
    int warrantyPeriod;

public:
    // Constructors
    NonPerishableProduct();

    NonPerishableProduct(int i, const string& n, double p, int sid, int q, const string& cat, int wp);

    // Getters and setters
    int getWarrantyPeriod() const;
    void setWarrantyPeriod(int wp);

    virtual Product* clone() const;
    json toJSON() const override;
    void fromJSON(const json& j) override;
    // Override display info
    void displayInfo() const override;
};


#endif //NONPERISHABLEPRODUCT_H

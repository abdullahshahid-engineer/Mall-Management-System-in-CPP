//
// Created by dell on 4/17/2025.
//

#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class Product {
protected:
    int id;
    string name;
    double price;
    int stockID;
    int quantity;
    string category;

public:
    // Constructors
    Product();

    Product(int i, const string& n, double p, int sid, int q, const string& cat);

    // Virtual destructor for polymorphism
    virtual ~Product();
    virtual Product* clone() const;
    // Getters
    int getID() const;
    string getName() const;
    double getPrice() const;
    int getStockID() const;
    int getQuantity() const;
    string getCategory() const;

    // Setters
    void setID(int i);
    void setName(const string& n);
    void setPrice(double p);
    void setStockID(int sid);
    void setQuantity(int q);
    void setCategory(const string& cat);

    // Update quantity
    void updateQuantity(int q);

    // Check availability
    virtual bool checkAvailability() const;

    // Display product information
    virtual void displayInfo() const;

    // Operator overloading for comparison
    bool operator==(const Product& other) const;

    bool operator!=(const Product& other) const;

    // Operator overloading for arithmetic operations
    Product& operator+=(int q);

    Product& operator-=(int q);
    virtual json toJSON() const ;

    virtual void fromJSON(const json& j);
};


#endif //PRODUCT_H

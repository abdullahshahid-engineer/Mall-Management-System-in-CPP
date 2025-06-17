//
// Created by dell on 4/17/2025.
//

#ifndef INVENTORY_H
#define INVENTORY_H
#include "Product.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "PerishableProduct.h"
#include "NonPerishableProduct.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

class Inventory {
private:
    int id;
    vector<Product*> products;

public:
    // Constructors
    Inventory();

    explicit Inventory(int i);

    // Destructor
    ~Inventory();


    // Getters
    int getID() const;
    int getSize() const;

    // Get product by index
    Product* getProduct(int index) const;

    // Find product by ID
    Product* findProduct(int productId) const;

    // Add product
    void addProduct(Product *product);

    // Remove product
    void removeProduct(int productId);

    // Update stock
    void updateStock(int productId, int quantity);

    // Check availability
    bool checkAvailability(int productId) const;

    // Display inventory
    void displayInventory() const;
    Inventory(const Inventory& other);

    // Assignment Operator
    Inventory& operator=(const Inventory& other);
    json toJSON() const;
    void fromJSON(const json& j);
};

#endif //INVENTORY_H

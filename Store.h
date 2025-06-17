//
// Created by dell on 4/17/2025.
//

#ifndef STORE_H
#define STORE_H
#include <iostream>
#include <string>
#include "StoreStockStats.h"
#include <fstream>
#include <sstream>
#include "StoreStats.h"
#include "json.hpp"
using json = nlohmann::json;
#include "Inventory.h"
using namespace std;


class Store {
protected:
    int storeID;
    string name;
    string category;
    Inventory inventory;

public:
    friend class StoreStats;
    // Constructors
    Store();
    Store(int id, const string& n, const string& cat, const Inventory& inv);
    // Virtual destructor
    virtual ~Store();

    // Copy constructor
    Store(const Store& other);

    // Assignment operator
    Store& operator=(const Store& other);
    friend bool compareStores(const Store& s1, const Store& s2);
    // Getters
    int getStoreID() const;
    string getName() const;
    string getCategory() const;
    Inventory& getInventory();
    const Inventory& getInventory() const;

    // Setters
    void setStoreID(int id);
    void setName(const string& n);
    void setCategory(const string& cat);

    // Display store info
    virtual void displayInfo() const;
    json toJSON() const;
    void fromJSON(const json& j);
};

#endif //STORE_H

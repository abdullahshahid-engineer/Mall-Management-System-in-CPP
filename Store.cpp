//
// Created by dell on 4/17/2025.
//

#include "Store.h"
Store::Store() : storeID(0), name(""), category(""){}

Store::Store(int id, const string& n, const string& cat, const Inventory& inv)
        : storeID(id), name(n), category(cat), inventory(inv){}

// Virtual destructor
Store::~Store() {}

// Copy constructor
Store::Store(const Store& other)
        : storeID(other.storeID), name(other.name), category(other.category),
          inventory(other.inventory) {}

// Assignment operator
Store& Store::operator=(const Store& other) {
    if (this != &other) {
        // Copy from other
        storeID = other.storeID;
        name = other.name;
        category = other.category;
        inventory = other.inventory;
    }
    return *this;
}
// Getters
int Store::getStoreID() const {
    return storeID;
}
string Store::getName() const {
    return name;
}
string Store::getCategory() const {
    return category;
}
Inventory& Store::getInventory() {
    return inventory;
}
const Inventory& Store::getInventory() const {
    return inventory;
}

// Setters
void Store::setStoreID(int id) {
    storeID=id;
}
void Store::setName(const string& n) {
    name=n;
}
void Store::setCategory(const string& cat) {
    category=cat;
}

void Store::displayInfo() const {
    cout << "Store ID: " << storeID << endl;
    cout << "Name: " << name << endl;
    cout << "Category: " << category << endl;
}
json Store::toJSON() const {
    return json{
                {"storeID", storeID},
                {"name", name},
                {"category", category},
                {"inventory", inventory.toJSON()}
    };
}

void Store::fromJSON(const json& j) {
    storeID = j.at("storeID").get<int>();
    name = j.at("name").get<string>();
    category = j.at("category").get<string>();
    inventory.fromJSON(j.at("inventory"));
}

bool compareStores(const Store& s1, const Store& s2) {
    return s1.storeID == s2.storeID;
}
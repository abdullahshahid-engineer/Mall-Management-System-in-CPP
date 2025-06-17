//
// Created by dell on 4/17/2025.
//

#include "Inventory.h"

Inventory::Inventory() : id(0) {}
Inventory::Inventory(int i) : id(i) {}

Inventory::~Inventory() {
    for (auto* p : products) {
        delete p;
    }
    products.clear();
}

// Copy constructor
Inventory::Inventory(const Inventory& other) : id(other.id) {
    for (auto* p : other.products) {
        products.push_back(p->clone());
    }
}

// Assignment operator
Inventory& Inventory::operator=(const Inventory& other) {
    if (this != &other) {
        for (auto* p : products) delete p;
        products.clear();
        id = other.id;
        for (auto* p : other.products) {
            products.push_back(p->clone());
        }
    }
    return *this;
}

int Inventory::getID() const { return id; }
int Inventory::getSize() const { return products.size(); }

Product* Inventory::getProduct(int index) const {
    if (index >= 0 && index < products.size()) return products[index];
    return nullptr;
}

Product* Inventory::findProduct(int productId) const {
    for (auto* p : products) {
        if (p && p->getID() == productId) return p;
    }
    return nullptr;
}

void Inventory::addProduct(Product* product) {
    if (!product) return;
    for (auto* p : products) {
        if (p && p->getID() == product->getID()) {
            cout << "Product with ID " << product->getID() << " already exists." << endl;
            return;
        }
    }
    products.push_back(product->clone());
}

void Inventory::removeProduct(int productId) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (*it && (*it)->getID() == productId) {
            delete *it;
            products.erase(it);
            cout << "Product with ID " << productId << " removed successfully." << endl;
            return;
        }
    }
    cout << "Product with ID " << productId << " not found." << endl;
}

void Inventory::updateStock(int productId, int quantity) {
    Product* product = findProduct(productId);
    if (product) {
        product->setQuantity(quantity);
        cout << "Stock updated successfully for product ID " << productId << "." << endl;
    } else {
        cout << "Product with ID " << productId << " not found." << endl;
    }
}

bool Inventory::checkAvailability(int productId) const {
    Product* product = findProduct(productId);
    return product ? product->checkAvailability() : false;
}

void Inventory::displayInventory() const {
    cout << "Inventory ID: " << id << "\nTotal Products: " << products.size() << endl;
    for (size_t i = 0; i < products.size(); ++i) {
        if (products[i]) {
            cout << "\n--- Product " << (i + 1) << " ---" << endl;
            products[i]->displayInfo();
        }
    }
}

json Inventory::toJSON() const {
    json j;
    j["id"] = id;
    j["products"] = json::array();
    for (auto* p : products) {
        if (p) j["products"].push_back(p->toJSON());
    }
    return j;
}

void Inventory::fromJSON(const json& j) {
    id = j.at("id").get<int>();
    for (auto& item : j.at("products")) {
        string type = item.at("type").get<string>();
        Product* p = nullptr;

        if (type == "perishable") {
            p = new PerishableProduct();
        } else if (type == "nonperishable") {
            p = new NonPerishableProduct();
        } else if (type == "product") {
            p = new Product();
        }

        if (p) {
            p->fromJSON(item);
            products.push_back(p);
        } else {
            cout << "Error: Unknown product type in JSON!" << endl;
        }
    }
}

//
// Created by dell on 4/17/2025.
//

#include "Product.h"
Product::Product():id(0), name(""), price(0.0), stockID(0), quantity(0), category("") {}

Product::Product(int i, const string& n, double p, int sid, int q, const string& cat)
        : id(i), name(n), price(p), stockID(sid), quantity(q), category(cat) {}

// Virtual destructor for polymorphism
Product::~Product() {}
Product* Product::clone() const {
    return new Product(*this);
}
// Getters
int Product::getID() const {
    return id;
}
string Product::getName() const {
    return name;
}
double Product::getPrice() const {
    return price;
}
int Product::getStockID() const {
    return stockID;
}
int Product::getQuantity() const {
    return quantity;
}
string Product::getCategory() const {
    return category;
}

// Setters
void Product::setID(int i) {
    id = i;
}
void Product::setName(const string& n) {
    name = n;
}
void Product::setPrice(double p) {
    price = p;
}
void Product::setStockID(int sid) {
    stockID = sid;
}
void Product::setQuantity(int q) {
    quantity = q;
}
void Product::setCategory(const string& cat) {
    category = cat;
}

// Update quantity
void Product::updateQuantity(int q) {
    quantity = q;
}

// Check availability
bool Product::checkAvailability() const {
    return quantity > 0;
}

// Display product information
void Product::displayInfo() const {
    cout << "Product ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Price: $" << price << endl;
    cout << "Stock ID: " << stockID << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Category: " << category << endl;
}

// Operator overloading for comparison
bool Product::operator==(const Product& other) const {
    return id == other.id && stockID == other.stockID;
}

bool Product::operator!=(const Product& other) const {
    return !(*this == other);
}

// Operator overloading for arithmetic operations
Product& Product::operator+=(int q) {
    quantity += q;
    return *this;
}

Product& Product::operator-=(int q) {
    if (quantity >= q)
        quantity -= q;
    else
        cout << "Error: Not enough quantity to reduce!" << endl;
    return *this;
}

json Product::toJSON() const {
    return {
            {"type", "product"},
                {"id", id},
                {"name", name},
                {"price", price},
                {"stockID", stockID},
                {"quantity", quantity},
                {"category", category}
    };
}

void Product::fromJSON(const json& j) {
    id = j.at("id").get<int>();
    name = j.at("name").get<string>();
    price = j.at("price").get<double>();
    stockID = j.at("stockID").get<int>();
    quantity = j.at("quantity").get<int>();
    category = j.at("category").get<string>();
}
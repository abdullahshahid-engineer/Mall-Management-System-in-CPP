

#include "Transaction.h"
Transaction::Transaction() :storeId(0),productId(0), transactionId(0), productName(""), quantity(0), price(0.0f) {}
Transaction::Transaction(int id, int prodId,int storeid,const string& product, int qty, float p)
    : transactionId(id), productName(product), quantity(qty), price(p), storeId(storeid),productId(prodId) {}

int Transaction::getTransactionId() const { return transactionId; }
string Transaction::getProductName() const { return productName; }
int Transaction::getQuantity() const { return quantity; }
float Transaction::getPrice() const { return price; }
int Transaction::getStoreId() const { return storeId; }
int Transaction::getProductId() const { return productId; }

void Transaction::setTransactionId(int id) { transactionId = id; }
void Transaction::setProductName(const string& product) { productName = product; }
void Transaction::setQuantity(int qty) { quantity = qty; }
void Transaction::setPrice(float p) { price = p; }
void Transaction::setStoreId(int id) { storeId = id; }
void Transaction::setProductId(int id) { productId = id; }

float Transaction::getTotalPrice() const {
    return price * this->quantity;
}

json Transaction::toJSON() const {
    json j;
    j["transactionId"] = transactionId;
    j["productId"] = productId;
    j["storeId"] = storeId;
    j["productName"] = productName;
    j["quantity"] = quantity;
    j["price"] = price;
    return j;
}

void Transaction::fromJSON(const json& j) {
    transactionId = j["transactionId"];
    productId = j["productId"];
    storeId = j["storeId"];
    productName = j["productName"];
    quantity = j["quantity"];
    price = j["price"];
}

// Operator overloading - adding transactions
Transaction Transaction::operator+(const Transaction& other) const {
    if (productName == other.productName) {
        return Transaction(transactionId,productId,storeId, productName, quantity + other.quantity, price);
    }
    return *this; // If product names are different, return the original transaction
}
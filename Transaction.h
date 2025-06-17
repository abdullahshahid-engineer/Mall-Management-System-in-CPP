

#ifndef TRANSACTION_H
#define TRANSACTION_H
#include<iostream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class Transaction {
private:
    int transactionId;
    int storeId;
    int productId;
    string productName;
    int quantity;
    float price;

public:
    Transaction();
    Transaction(int id, int prodId,int storeid,const string& product, int qty, float p);
    int getTransactionId() const;
    string getProductName() const;
    int getQuantity() const;
    float getPrice() const;
    int getStoreId() const;
    int getProductId() const;

    void setTransactionId(int id);
    void setProductName(const string& product);
    void setQuantity(int qty);
    void setPrice(float p);
    void setStoreId(int id);
    void setProductId(int id);

    float getTotalPrice() const;

    json toJSON() const;

    void fromJSON(const json& j) ;

    // Operator overloading - adding transactions
    Transaction operator+(const Transaction& other) const;
};




#endif //TRANSACTION_H

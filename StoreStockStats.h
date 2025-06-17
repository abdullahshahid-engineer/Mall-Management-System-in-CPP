//
// Created by dell on 4/20/2025.
//

#ifndef STORESTOCKSTATS_H
#define STORESTOCKSTATS_H
// StoreStockStats.h



#include "Inventory.h"
#include <iostream>
using namespace std;

template <typename T>
class StoreStockStats {
private:
    static StoreStockStats<T>* instance;
    T stockAmount;
    Inventory* inventory;

    // Private constructor
    StoreStockStats() : stockAmount(0), inventory(nullptr) {}
    explicit StoreStockStats(Inventory* inv) : inventory(inv), stockAmount(0) {}

public:
    // Delete copy constructor and assignment
    StoreStockStats(const StoreStockStats&) = delete;
    StoreStockStats& operator=(const StoreStockStats&) = delete;

    // Singleton instance getter
    static StoreStockStats<T>* getInstance(Inventory* inv = nullptr) {
        if (instance == nullptr) {
            if (inv != nullptr)
                instance = new StoreStockStats<T>(inv);
            else
                instance = new StoreStockStats<T>();
        }
        return instance;
    }
    T getStockAmount() {
        return stockAmount;
    }
    void countProductInStore() {
        int size = inventory->getSize();
        cout <<"Total Products in Store : "<< size <<" Products "<<endl;
    }
    void calculateStockAmount() {
        if (inventory == nullptr) return;
        T total = 0;
        for (int i = 0; i < inventory->getSize(); i++) {
            Product* p = inventory->getProduct(i);
            if (p) {
                total += static_cast<T>(p->getPrice() * p->getQuantity());
            }
        }
        stockAmount = total;
    }

    void display() const {
        cout << "Total Stock Amount: " << stockAmount << endl;
    }

    void setInventory(Inventory* inv) {
        inventory = inv;
    }
};

// Initialize static member
template <typename T>
StoreStockStats<T>* StoreStockStats<T>::instance = nullptr;



#endif //STORESTOCKSTATS_H

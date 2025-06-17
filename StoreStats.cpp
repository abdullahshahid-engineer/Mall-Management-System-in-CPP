//
// Created by dell on 4/26/2025.
//

#include "StoreStats.h"
#include "Mall.h"
#include "Store.h"
void StoreStats::showTotalStores(Mall& mall) {
    cout << "Total Stores in Mall \"" << mall.name << "\": " << mall.stores.size() << endl;
}

// Show total products in each store
void StoreStats::showProductsInEachStore(Mall& mall) {
    cout << "Products in each store:" << endl;
    for (auto store : mall.stores) {
        if (store) {
            cout << "--------------------------------" << endl;
            cout << "Store Name: " << store->name << endl;
            cout << "Store ID: " << store->storeID << endl;
            cout << "Total Products: " << store->inventory.getSize() << endl;
        }
    }
    cout << "--------------------------------" << endl;
}
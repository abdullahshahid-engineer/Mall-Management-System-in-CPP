//
// Created by dell on 4/26/2025.
//

#ifndef STORESTATS_H
#define STORESTATS_H



#include "Inventory.h"
#include <iostream>
using namespace std;
class Mall;
class Store;
class StoreStats {
public:
    // Show total number of stores in the mall
    static void showTotalStores(Mall& mall);

    // Show total products in each store
    static void showProductsInEachStore(Mall& mall);
};




#endif //STORESTATS_H

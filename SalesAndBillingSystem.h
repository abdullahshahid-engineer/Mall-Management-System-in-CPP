//
// Created by dell on 11/10/2024.
//

#ifndef SALESANDBILLINGSYSTEM_H
#define SALESANDBILLINGSYSTEM_H



#include "ProductAndInventoryManagement.h"

struct Sale {
    int vehicleId;
    int customerId;
    double price;
    int quantity;
    double totalAmount;
    double discount;
    double netAmount;
};
void vehicleSelectionAndQuantity(Vehicles *&vehicles,const int &vehicleCount,Sale &sale);
double applyDiscountAndTax(Sale &sale);
void generateReceipt(Sale &sale);
void menuofSalesAndBillingSystem(Vehicles *&vehicle,const int &vehiclesCount,Sale &sale);
void viewSaleHistory();


#endif //SALESANDBILLINGSYSTEM_H

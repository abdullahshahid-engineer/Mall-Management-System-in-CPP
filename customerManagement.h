//
// Created by Bismillah Traders on 11/10/2024.
//

#ifndef CUSTOMERMANAGENET_H
#define CUSTOMERMANAGENET_H


#include <iostream>
using namespace std;
struct Customer {
         int id;
    string name;
    string contact;
    int loyaltyPoints;
    string feedBack;
};

int manageLoyaltyPoints(int customerId);
void addCustomer(Customer *&customer,int &customerCount);
void menuOfCustomer(Customer *&customer,int &customerCount);
void viewCustomers();
void viewLoyaltyPoints();
void viewCustomerHistory();
void viewCustomerAnalysis();


#endif //CUSTOMERMANAGENET_H

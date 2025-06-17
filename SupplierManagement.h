//
// Created by dell on 11/7/2024.
//

#ifndef SUPPLIERMANAGEMENT_H
#define SUPPLIERMANAGEMENT_H
#include<iostream>
#include "ProductAndInventoryManagement.h"
using namespace std;
struct Supplier {
    int id;
    string name;
    string contact;
    string address;
    string email;
    int rating;
};
void rateSupplier(Supplier*& suppliers, int count, int id);
void displaySupplierRating(Supplier* suppliers, int count,int id);
void menuOfSuplierManagement(Supplier *&suppliers,int supplierCount,Vehicles *&vehicles,int &vehiclesCount);
void addSupplier(Supplier*& suppliers, int& supplierCount);
void backupSuppliers(Supplier *&suppliers, int &supplierCount);
int findSupplierIndex(Supplier *&suppliers, int supplierCount, int id);
void displaySuppliers(Supplier *suppliers,int supplierCount);
void writeSuppliers(Supplier*& suppliers, int& supplierCount);
void deleteSupplier(Supplier *&suppliers, int &supplierCount,int id);
void updateSuppliers(Supplier *&suppliers, int supplierCount,int id);
void addProductFromSuppliers(Supplier *&suppliers, int supplierCount,Vehicles *&vehicles,int &vehiclesCount);
void viewSupplierRecord(Supplier *&suppliers, int supplierCount);

#endif //SUPPLIERMANAGEMENT_H

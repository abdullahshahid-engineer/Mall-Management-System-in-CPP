//
// Created by dell on 4/17/2025.
//

#ifndef MALL_H
#define MALL_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Store.h"
#include "Employee.h"
class CustomerSalesSystem;
#include "Security.h"
#include "ParkingSystem.h"
#include "AdvertisementSystem.h"
#include "Manager.h"
#include "OnlineBookingSystem.h"
#include "SecuritySystem.h"
#include "EmployeeStats.h"
#include "Product.h"
#include "PerishableProduct.h"
#include "NonPerishableProduct.h"
#include "Inventory.h"
#include "StoreStockStats.h"
#include "StoreStats.h"
#include "Cashier.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


class Mall {
private:
    string name;
    string location;
    vector<Store*> stores;
//Employee class object in vector form
    vector<Employee*> employees;
    // Singleton pattern implementation
    static Mall* instance;
    // Private constructor for singleton pattern
    Mall();
    public:
    friend class StoreStats;
    friend ostream& operator<<(ostream& os, const Mall& mall);
    static Mall* getInstance();
    void initialize(const string& n, const string& loc);
    ~Mall();
    string getName();
    string getLocation();
    int getStoreCapacity();
    int getStoreCount();
    void setName(const string &name);
    void setLocation(const string &location);
    void setStore(Store *store);
    Store *getStore();


    Store* findStore(int storeID) const;
    // Find store by name
    Store* findStore(const string& storeName) const;
    Store* getStoreByID(int id);
    void displayInfo() const;
    void displayAllStores() const;
    void removeStore(const int &ids);
    void loadStoreDataFromFile(const string& filename);
    void saveStoreDataToFile(const string& filename);

//BSSE24021 functions for employee
    void addEmployee(Employee* emp);

    void showEmployees() const;
    vector<Employee*> &getAllEmployee();

    // Additional utility methods
    int getEmployeeCount() const;

    Employee* findEmployeeByName(const string& name) const;

    void removeEmployee(const string& name) ;

    // JSON conversion methods
    void saveEmployeeData(string filename) const ;
    void loadEmployeeData(string filename) ;
};


void mainMenu(Mall *mall);
void storeMenu(Mall *mall);
void inventoryMenu(Mall *mall);
void displayEmployeeMenu();
void displaySecurityMenu();
void employeeMenu(Mall *mall);
void securityMenu(Mall *mall);
#endif //MALL_H

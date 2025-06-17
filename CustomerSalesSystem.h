//
// Created by dell on 4/25/2025.
//

#ifndef CUSTOMERSALESSYSTEM_H
#define CUSTOMERSALESSYSTEM_H
#include<iostream>
#include<string>
#include<fstream>
#include "Customer.h"
#include "json.hpp"
#include "Invoice.h"
#include <vector>
#include "CustomerStats.h"
#include "Transaction.h"
#include "PaymentMethod.h"
#include "RegularCustomer.h"
#include "VIPCustomer.h"
using json = nlohmann::json;
using namespace std;
class Mall;
class CustomerSalesSystem {
private:
    vector<Customer*> customers;
    vector<Invoice*> invoices;
    vector<Transaction*> transactions;
    vector<PaymentMethod*> paymentMethods;

    // Singleton pattern implementation
    static CustomerSalesSystem* instance;
    CustomerSalesSystem() {}

public:
    static CustomerSalesSystem* getInstance();

    ~CustomerSalesSystem();

    void addCustomer(Customer* customer);

    void addInvoice(Invoice* invoice);


    void addTransaction(Transaction* transaction);

    void addPaymentMethod(PaymentMethod* method);
    Transaction* findTransactionById(int id);
    Customer* findCustomerById(int id) ;

    vector<Customer*>& getCustomers() ;


    Invoice* findInvoiceById(int id) ;

    void displayAllCustomers() ;

    void saveCustomerDataToFile(const string& filename) ;

    void loadCustomerDataFromFile(const string& filename);
};

void customerAndSalesMenu(Mall* mall);
void customerMenu(Mall* mall, CustomerSalesSystem* system);
void feedbackMenu(Mall* mall, CustomerSalesSystem* system);
void transactionMenu(Mall* mall, CustomerSalesSystem* system);
void statisticsMenu(Mall* mall, CustomerSalesSystem* system);

#endif //CUSTOMERSALESSYSTEM_H

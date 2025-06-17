

#ifndef INVOICE_H
#define INVOICE_H
#include<iostream>
#include "Customer.h"
#include"Transaction.h"
#include "PaymentMethod.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


class Invoice {
private:
    int invoiceId;
    Customer* customer;
    vector<Transaction*> items;
    float totalAmount;
    PaymentMethod* paymentMethod;

public:
    Invoice();

    Invoice(int id, Customer* cust, PaymentMethod* payment = nullptr);

    ~Invoice();

    int getInvoiceId() const ;
    Customer* getCustomer() const ;
    float getTotalAmount() const;
    PaymentMethod* getPaymentMethod() const ;

    void setInvoiceId(int id) ;
    void setCustomer(Customer* cust);
    void setTotalAmount(float amount) ;
    void setPaymentMethod(PaymentMethod* method);

    void addTransaction(Transaction* transaction);

    float calculateTotal();

    float applyDiscount(float discountRate);
    void createReceipt() ;

    json toJSON() const;

    void fromJSON(const json& j, Customer* cust = nullptr, PaymentMethod* payment = nullptr);
};



#endif //INVOICE_H

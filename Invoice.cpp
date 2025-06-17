
#include "Invoice.h"
Invoice::Invoice()
        : invoiceId(0), customer(nullptr), totalAmount(0.0f),
          paymentMethod(nullptr) {}

Invoice::Invoice(int id, Customer* cust, PaymentMethod* payment)
        : invoiceId(id), customer(cust), totalAmount(0.0f),
          paymentMethod(payment) {}

Invoice::~Invoice() {
    // Only clearing the vector, not deleting the objects
    items.clear();
}

int Invoice::getInvoiceId() const { return invoiceId; }
Customer* Invoice::getCustomer() const { return customer; }
float Invoice::getTotalAmount() const { return totalAmount; }
PaymentMethod* Invoice::getPaymentMethod() const { return paymentMethod; }

void Invoice::setInvoiceId(int id) { invoiceId = id; }
void Invoice::setCustomer(Customer* cust) { customer = cust; }
void Invoice::setTotalAmount(float amount) { totalAmount = amount; }
void Invoice::setPaymentMethod(PaymentMethod* method) { paymentMethod = method; }

void Invoice::addTransaction(Transaction* transaction) {
    for (const auto& item : items) {
        if (item->getTransactionId() == transaction->getTransactionId()) {
            return;
        }
    }
    items.push_back(transaction);
    calculateTotal();
}

float Invoice::calculateTotal() {
    totalAmount = 0.0f;
    for (const auto& item : items) {
        totalAmount += item->getTotalPrice();
    }
    //cout << "Subtotal calculated: $" << totalAmount << endl;
    return totalAmount;
}

float Invoice::applyDiscount(float discountRate) {
    float finalRate = discountRate;

    if (customer && customer->getMembershipStatus() == "VIP") {
        cout << "Customer is VIP: Applying extra 5% discount." << endl;
        finalRate += 0.05f; // Add 5% extra discount
    }

    float discountedTotal = totalAmount * (1 - finalRate);
    cout << "Applied total discount of " << finalRate * 100 << "%" << endl;
    cout << "Discounted total: $" << discountedTotal << endl;
    totalAmount = discountedTotal;
    return discountedTotal;
}

void Invoice::createReceipt() {
    cout << "\n========== RECEIPT ==========" << endl;
    cout << "Invoice ID: " << invoiceId << endl;
    cout << "Customer: " << customer->getName() << endl;
    cout << "Items:" << endl;
    int total = 0;
    for (const auto& item : items) {
        cout << "- " << item->getProductName()
             << " (Qty: " << item->getQuantity()
             << ") - $" << item->getPrice()
             << " each = $" << item->getTotalPrice() << endl;
        total=item->getTotalPrice();
    }
    cout<<"Discounted Amount : $"<<(total-totalAmount)<<endl;
    cout << "Total Amount: $" << totalAmount << endl;
    if (paymentMethod) {
        cout << "Payment Method: " << paymentMethod->getMethodType() << endl;
    }
    cout << "============================" << endl;
}

json Invoice::toJSON() const {
    json j;
    j["invoiceId"] = invoiceId;
    j["totalAmount"] = totalAmount;

    if (customer) {
        j["customerId"] = customer->getCustomerId();
    }

    if (paymentMethod) {
        j["paymentMethod"] = paymentMethod->toJSON();
    }

    j["items"] = json::array();
    for (const auto& item : items) {
        j["items"].push_back(item->toJSON());
    }

    return j;
}

void Invoice::fromJSON(const json& j, Customer* cust , PaymentMethod* payment ) {
    invoiceId = j["invoiceId"];
    totalAmount = j["totalAmount"];
    customer = cust;
    paymentMethod = payment;

    // Transactions will need to be loaded separately and associated
    items.clear();

    // Load transactions from JSON array
    if (j.contains("items") && j["items"].is_array()) {
        for (const auto& itemJson : j["items"]) {
            Transaction* t = new Transaction();
            t->fromJSON(itemJson);
            items.push_back(t);
        }
    }
}
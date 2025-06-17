//
// Created by dell on 4/25/2025.
//

#include "CustomerSalesSystem.h"
#include "Mall.h"
// Initialize the static member
CustomerSalesSystem* CustomerSalesSystem::instance = nullptr;
CustomerSalesSystem* CustomerSalesSystem::getInstance() {
    if (!instance) {
        instance = new CustomerSalesSystem();
    }
    return instance;
}

CustomerSalesSystem::~CustomerSalesSystem() {
    for (auto customer : customers) {
        delete customer;
    }
    for (auto invoice : invoices) {
        delete invoice;
    }
    for (auto transaction : transactions) {
        delete transaction;
    }
    for (auto method : paymentMethods) {
        delete method;
    }

    customers.clear();
    invoices.clear();
    transactions.clear();
    paymentMethods.clear();
}

void CustomerSalesSystem::addCustomer(Customer* customer) {
    customers.push_back(customer);
}

void CustomerSalesSystem::addInvoice(Invoice* invoice) {
    invoices.push_back(invoice);
}


void CustomerSalesSystem::addTransaction(Transaction* transaction) {
    transactions.push_back(transaction);
}

void CustomerSalesSystem::addPaymentMethod(PaymentMethod* method) {
    paymentMethods.push_back(method);
}
Transaction* CustomerSalesSystem::findTransactionById(int id) {
    for (auto transaction : transactions) {
        if (transaction->getTransactionId() == id) {
            return transaction;
        }
    }
    return nullptr;
}
Customer* CustomerSalesSystem::findCustomerById(int id) {
    for (auto customer : customers) {
        if (customer->getCustomerId() == id) {
            return customer;
        }
    }
    return nullptr;
}

vector<Customer*>& CustomerSalesSystem::getCustomers() {
    return customers;
}


Invoice* CustomerSalesSystem::findInvoiceById(int id) {
    for (auto invoice : invoices) {
        if (invoice->getInvoiceId() == id) {
            return invoice;
        }
    }
    return nullptr;
}

void CustomerSalesSystem::displayAllCustomers() {
    cout << "\n=== Customer List ===" << endl;
    for (const auto& customer : customers) {
        customer->displayInfo();
        cout << "--------------------" << endl;
    }
}

void CustomerSalesSystem::saveCustomerDataToFile(const string& filename) {
    try {
        json j;

        j["customers"] = json::array();
        for (const auto& customer : customers) {
            j["customers"].push_back(customer->toJSON());
        }

        j["invoices"] = json::array();
        for (const auto& invoice : invoices) {
            j["invoices"].push_back(invoice->toJSON());
        }

        j["transactions"] = json::array();
        for (const auto& transaction : transactions) {
            j["transactions"].push_back(transaction->toJSON());
        }

        j["paymentMethods"] = json::array();
        for (const auto& method : paymentMethods) {
            j["paymentMethods"].push_back(method->toJSON());
        }

        ofstream file(filename);
        if (file.is_open()) {
            file << j.dump(4); // Pretty printing with 4-space indent
            file.close();
            cout << "Customer and Sales data saved to " << filename << " successfully." << endl;
        } else {
            cout << "Failed to open file for writing." << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error saving data: " << e.what() << endl;
    }
}

void CustomerSalesSystem::loadCustomerDataFromFile(const string& filename) {
    try {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File not found or couldn't be opened." << endl;
            return;
        }

        json j;
        file >> j;
        file.close();

        // Clear existing data
        for (auto customer : customers) delete customer;
        for (auto invoice : invoices) delete invoice;
        for (auto transaction : transactions) delete transaction;
        for (auto method : paymentMethods) delete method;

        customers.clear();
        invoices.clear();
        transactions.clear();
        paymentMethods.clear();

        // Load customers
        for (auto& el : j["customers"]) {
            Customer* customer = nullptr;
            string type = el["type"];

            if (type == "vip") {
                customer = new VIPCustomer();
            } else {
                customer = new RegularCustomer();
            }

            customer->fromJSON(el);


            customers.push_back(customer);
        }

        // Load payment methods
        for (auto& el : j["paymentMethods"]) {
            PaymentMethod* method = new PaymentMethod();
            method->fromJSON(el);
            paymentMethods.push_back(method);
        }

        // Load transactions
        for (auto& el : j["transactions"]) {
            Transaction* transaction = new Transaction();
            transaction->fromJSON(el);
            transactions.push_back(transaction);
        }

        // Load invoices (complex due to associations)
        for (auto& el : j["invoices"]) {
            Invoice* invoice = new Invoice();

            int customerId = el["customerId"];
            Customer* customer = findCustomerById(customerId);

            invoice->fromJSON(el, customer);

            // Add transactions to invoice
            if (el.contains("items")) {
                for (auto& itemEl : el["items"]) {
                    int transactionId = itemEl["transactionId"];
                    for (auto transaction : transactions) {
                        if (transaction->getTransactionId() == transactionId) {
                            invoice->addTransaction(transaction);
                            break;
                        }
                    }
                }
            }

            invoices.push_back(invoice);
        }

        cout << "Customer and Sales data loaded from " << filename << " successfully." << endl;
    }
    catch (const exception& e) {
        cerr << "Error loading data: " << e.what() << endl;
    }
}




void customerMenu(Mall* mall, CustomerSalesSystem* system) {
    cout << endl << "Customer Management System" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Display All Customers" << endl;
        cout << "3. Find Customer by ID" << endl;
        cout << "4. Add Loyalty Points (VIP only)" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                int id;
                string name;
                int type;

                cout << "Enter Customer ID: ";
                cin >> id;
                if (system->findCustomerById(id)) {
                    cout << "Customer with this ID already exists." << endl;
                    break;
                }
                cin.ignore();
                cout << "Enter Customer Name: ";
                getline(cin, name);
                cout << "Customer Type (1: Regular, 2: VIP): ";
                cin >> type;

                Customer* customer = nullptr;
                if (type == 1) {
                    customer = new RegularCustomer(id, name);
                } else if (type == 2) {
                    int points;
                    cout << "Initial Loyalty Points: ";
                    cin >> points;
                    customer = new VIPCustomer(id, name, points);
                } else {
                    cout << "Invalid customer type selected." << endl;
                    continue;
                }

                system->addCustomer(customer);
                cout << "Customer added successfully!" << endl;
                break;
            }
            case 2: {
                system->displayAllCustomers();
                break;
            }
            case 3: {
                int id;
                cout << "Enter Customer ID: ";
                cin >> id;

                Customer* customer = system->findCustomerById(id);
                if (customer) {
                    customer->displayInfo();
                } else {
                    cout << "Customer not found." << endl;
                }
                break;
            }
            case 4: {
                int id, points;
                cout << "Enter Customer ID: ";
                cin >> id;

                Customer* customer = system->findCustomerById(id);
                if (customer && customer->getMembershipStatus() == "VIP") {
                    VIPCustomer* vipCustomer = static_cast<VIPCustomer*>(customer);
                    cout << "Enter loyalty points to add: ";
                    cin >> points;
                    vipCustomer->addLoyaltyPoints(points);
                } else {
                    cout << "Customer not found or not a VIP customer." << endl;
                }
                break;
            }
            case 0: {
                cout << "Returning to Main Menu" << endl;
                break;
            }
            default:
                cout << "Invalid Choice. Please Try again!!!" << endl;
        }
    } while (option != 0);
}
void feedbackMenu(Mall* mall, CustomerSalesSystem* system) {
    cout << endl << "Customer Feedback System" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. Submit Feedback" << endl;
        cout << "2. Search Feedback" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                int customerId, feedbackId;
                string content;

                cout << "Enter Customer ID: ";
                cin >> customerId;

                Customer* customer = system->findCustomerById(customerId);
                if (!customer) {
                    cout << "Customer not found." << endl;
                    break;
                }

                cout << "Enter Feedback ID: ";
                cin >> feedbackId;
                for (Customer* customer : system->getCustomers()) {
                    const vector<Feedback*>& feedbacks = customer->getFeedbacks();
                    for (Feedback* fb : feedbacks) {
                        if (fb->getFeedbackId() == feedbackId) {
                            cout<<"FeedBack Id already Exist."<<endl;
                            return;
                        }
                    }
                }
                cin.ignore();
                cout << "Enter Feedback Content: ";
                getline(cin, content);

                Feedback* feedback = new Feedback(feedbackId, customer, content);
                feedback->submitFeedback();
                cout << "Feedback submitted successfully!" << endl;
                break;
            }
            case 2: {
                int searchId;
                cout << "Enter Feedback ID to search: ";
                cin >> searchId;

                bool found = false;
                for (Customer* customer : system->getCustomers()) {
                    const vector<Feedback*>& feedbacks = customer->getFeedbacks();
                    for (Feedback* fb : feedbacks) {
                        if (fb->getFeedbackId() == searchId) {
                            cout << "\nFeedback found!" << endl;
                            cout << "Customer Name: " << customer->getName() << endl;
                            cout << "Feedback Content: " << fb->getContent() << endl;
                            found = true;
                            break;
                        }
                    }
                    if (found) break;
                }

                if (!found) {
                    cout << "No feedback found with the given ID." << endl;
                }
                break;
            }
            case 0: {
                cout << "Returning to Main Menu" << endl;
                break;
            }
            default:
                cout << "Invalid Choice. Please Try again!!!" << endl;
        }
    } while (option != 0);
}

void customerAndSalesMenu(Mall* mall) {
    CustomerSalesSystem* system = CustomerSalesSystem::getInstance();

    cout << "Welcome to Customer and Sales Management System!" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. Customer Management" << endl;
        cout << "2. Transactions and Invoices" << endl;
        cout << "3. Customer Feedback" << endl;
        cout << "4. Statistics and Analytics" << endl;
        cout << "0. Back to Mall Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                customerMenu(mall, system);
                break;
            }
            case 2: {
                transactionMenu(mall, system);
                break;
            }
            case 3: {
                feedbackMenu(mall, system);
                break;
            }
            case 4: {
                statisticsMenu(mall, system);
                break;
            }
            case 0: {
                cout << "Returning to Mall Main Menu" << endl;
                break;
            }
            default:
                cout << "Invalid Choice. Please Try again!!!" << endl;
        }
    } while (option != 0);
}
void transactionMenu(Mall* mall, CustomerSalesSystem* system) {
    cout << endl << "Transaction Management" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. Create New Transaction" << endl;
        cout << "2. Create Invoice" << endl;
        cout << "3. Display Invoice" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                int id,storId,prodctId;
                cout << "Enter Transaction ID: ";
                cin >> id;
                if (system->findTransactionById(id)) {
                    cout << "Transaction with this ID already exists." << endl;
                    break;
                }
                mall->displayAllStores();
                cout<<endl << "Enter Store ID: ";
                cin >> storId;
                Store* store = mall->findStore(storId);
                if (!store) {
                    cout << "Store not found." << endl;
                    continue;
                }
                Inventory& inventory = store->getInventory();
                inventory.displayInventory();
                cout<<endl << "Enter Product ID: ";
                cin >> prodctId;
                cout<<"Enter Product quantity: ";
                int quantity;
                cin >> quantity;
                Product *product=inventory.findProduct(prodctId);
                if (!product) {
                    cout << "Product not found." << endl;
                    continue; // Go back to the menu
                }
                string productName=product->getName();
                double price=product->getPrice();
                int newQuantity=product->getQuantity()-quantity;
                Transaction* transaction = new Transaction(id,prodctId,storId, productName, quantity, price);
                system->addTransaction(transaction);
                inventory.updateStock(prodctId,newQuantity);
                cout << "Transaction created successfully!" << endl;
                break;
            }
            case 2: {
                int invoiceId, customerId;
                string paymentType;

                cout << "Enter Invoice ID: ";
                cin >> invoiceId;
                if (system->findInvoiceById(invoiceId)) {
                    cout << "Invoice with this ID already exists." << endl;
                    break;
                }
                cout << "Enter Customer ID: ";
                cin >> customerId;
                cin.ignore();
                cout << "Enter Payment Method Type: ";
                getline(cin, paymentType);

                Customer* customer = system->findCustomerById(customerId);
                if (!customer) {
                    cout << "Customer not found." << endl;
                    break;
                }

                PaymentMethod* paymentMethod = new PaymentMethod(paymentType);
                system->addPaymentMethod(paymentMethod);

                Invoice* invoice = new Invoice(invoiceId, customer, paymentMethod);
                int transactionId;
                cout << "Enter Transaction ID to add to invoice: ";
                cin >> transactionId;
                Transaction *trans=system->findTransactionById(transactionId);
                invoice->addTransaction(trans);
                system->addInvoice(invoice);
                float discountRate;
                cout << "Enter Discount Rate (0.0 to 1.0): ";
                cin >> discountRate;
                invoice->applyDiscount(discountRate);
                cout << "Discount applied successfully!" << endl;
                paymentMethod->processPayment(invoice->getTotalAmount());
                cout << "Payment processed successfully!" << endl;
                cout << "Invoice created successfully!" << endl;
                invoice->createReceipt();
                break;
            }
            case 3: {
                int invoiceId;

                cout << "Enter Invoice ID: ";
                cin >> invoiceId;

                Invoice* invoice = system->findInvoiceById(invoiceId);
                if (!invoice) {
                    cout << "Invoice not found." << endl;
                    break;
                }

                invoice->createReceipt();
                break;
            }
            case 0: {
                cout << "Returning to Main Menu" << endl;
                break;
            }
            default:
                cout << "Invalid Choice. Please Try again!!!" << endl;
        }
    } while (option != 0);
}
void statisticsMenu(Mall* mall, CustomerSalesSystem* system) {
    cout << endl << "Statistics and Analytics" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. View Customer Statistics" << endl;
        cout << "2. Calculate VIP Customer Percentage" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                CustomerStats<double>* stats = CustomerStats<double>::getInstance(&system->getCustomers());
                stats->displayStatistics();
                break;
            }
            case 2: {
                CustomerStats<double>* stats = CustomerStats<double>::getInstance(&system->getCustomers());
                double vipPercentage = stats->calculateVIPPercentage();
                cout << "VIP Customer Percentage: " << vipPercentage << "%" << endl;
                break;
            }
            case 0: {
                cout << "Returning to Main Menu" << endl;
                break;
            }
            default:
                cout << "Invalid Choice. Please Try again!!!" << endl;
        }
    } while (option != 0);
}


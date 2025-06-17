//
// Created by dell on 4/17/2025.
//

#include "Mall.h"
#include "CustomerSalesSystem.h"
//====================================================================================================//
//-------------------------------BSSE24001 WORK IN MALL CLASS-----------------------------------------//
//====================================================================================================//
Mall* Mall::instance = nullptr;
Mall::Mall() : name(""), location("") {}

// Singleton instance access
Mall* Mall::getInstance() {
    if (!instance) {
        instance = new Mall();
    }
    return instance;
}

// Destructor
Mall::~Mall() {
    for (Store* store : stores) {
        delete store;
    }
    stores.clear();
}

void Mall::initialize(const string& n, const string& loc) {
    name = n;
    location = loc;
}

string Mall::getName() {
    return name;
}
string Mall::getLocation() {
    return location;
}

int Mall::getStoreCapacity() {
    return stores.capacity();
}
int Mall::getStoreCount() {
    return stores.size();
}

void Mall::setName(const string& n) {
    name = n;
}
void Mall::setLocation(const string& loc) {
    location = loc;
}

void Mall::setStore(Store* store) {
    stores.push_back(store);
}

Store* Mall::getStoreByID(int id) {
    for (auto store : stores) {
        if (store->getStoreID() == id)
            return store;
    }
    return nullptr;
}

Store* Mall::findStore(int storeID) const {
    for (Store* store : stores) {
        if (store->getStoreID() == storeID)
            return store;
    }
    return nullptr;
}
void Mall::displayInfo() const {
    cout<<"\n=== "<<name << " Mall Information ===" <<endl;
    cout<<"Location: " << location << endl;
    cout<<"Total Stores: " << stores.size() <<endl;
}
ostream& operator<<(ostream& os, const Mall& mall) {
    os<<mall.name;
    os<<mall.location;
    return os;
}
// Find store by name
Store* Mall::findStore(const string& storeName) const {
    for (Store* store : stores) {
        if (store->getName() == storeName)
            return store;
    }
    return nullptr;
}
// Display all stores
void Mall::displayAllStores() const {
    cout << "\n=== Stores in " << name << " Mall ===" << endl;
    for (const Store* store : stores) {
            cout << "\n\n--- Store " << store->getStoreID() << " ---" << endl;
            store->displayInfo();
    }
}

void Mall::removeStore(const int& ids) {
    for (auto it = stores.begin(); it != stores.end(); ++it) {
        if ((*it)->getStoreID() == ids) {
            delete *it;
            stores.erase(it);
            cout<<"Store Successfully Removed"<<endl;
            return;
        }
    }
    cout<<"There is no store with that ID."<<endl;
}

void Mall::saveStoreDataToFile(const string& filename) {
    try {
        json j;
        j["name"] = name;
        j["location"] = location;
        j["stores"] = json::array();

        for (const Store* s : stores) {
            j["stores"].push_back(s->toJSON());
        }

        ofstream file(filename);
        if (file.is_open()) {
            file << j.dump(4); // Pretty printing with 4-space indent
            file.close();
            cout << "Data saved to " << filename << " successfully.\n";
        } else {
            cout << "Failed to open file for writing.\n";
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void Mall::loadStoreDataFromFile(const string& filename) {
    try {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File not found or couldn't be opened.\n";
            return;
        }

        json j;
        file >> j;
        file.close();

        name = j["name"];
        location = j["location"];

        for (auto& el : j["stores"]) {
            Store* s = new Store();
            s->fromJSON(el);
            stores.push_back(s);
        }

        cout << "Data loaded from " << filename << " successfully.\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void storeMenu(Mall *mall) {
    int option;
    do {
        cout << "\n===== Store Management System =====" << endl;
        cout<<endl<<"======================================="<<endl;
        cout<<"1. Add Store"<<endl;
        cout<<"2. Remove Store"<<endl;
        cout<<"3. Display Store"<<endl;
        cout<<"4. Find Store by ID"<<endl;
        cout<<"5. Store Stats"<<endl;
        cout<<"0. Back to main menu"<<endl;
        cout<<"Enter your choice : ";
        cin>>option;
        switch (option) {
            case 1: {
                string name,category;
                int id;
                cout<<"Enter Store Name : ";
                cin.ignore();
                getline(cin, name);
                cout<<"Enter Category : ";
                getline(cin, category);
                cout<<"Enter ID : ";
                cin>>id;
                if (mall->getStoreByID(id) != nullptr) {
                    cout << "Store with ID " << id << " already exists!" << endl;
                } else {
                    Inventory inventory(id);
                    Store* store = new Store(id, name, category, inventory);  // allocate on heap
                    mall->setStore(store);  // pass a valid heap-allocated pointer
                }
                break;
            }
            case 2: {
                int removeStoreId;
                cout<<"Enter Store ID : ";
                cin>>removeStoreId;
                mall->removeStore(removeStoreId);
                break;
            }
            case 3: {
                mall->displayAllStores();
                break;
            }
            case 4: {
                int findStoreId;
                cout<<"Enter Store ID : ";
                cin>>findStoreId;
                Store *store1=mall->findStore(findStoreId);
                store1->displayInfo();
                break;
            }
            case 5: {
                StoreStats::showTotalStores(*mall);
                StoreStats::showProductsInEachStore(*mall);
            }
            case 0: {
                cout<<"Back to main menu!!"<<endl;
                break;
            }
            default:
                cout<<"Invalid Choice. Please Try again!!!"<<endl;
        }
    } while (option!=0);
}

void inventoryMenu(Mall *mall) {
    int option;
    do {
        cout << "\n===== INVENTORY OPERATIONS =====" << endl;
        cout<<endl<<"======================================="<<endl;
        cout << "1. Display Inventory" <<endl;
        cout << "2. Add Product" << endl;
        cout << "3. Remove Product" << endl;
        cout << "4. Update Stock" << endl;
        cout << "5. Check Product Availability" << endl;
        cout << "6. Stats of Store Inventory" << endl;
        cout << "7. Find Product with their ID" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin>>option;
        string storeName;
            cout << "Enter store name: ";
            cin.ignore();
            getline(cin, storeName);
            Store* store = mall->findStore(storeName);
            if (!store) {
                cout << "Store not found." << endl;
                continue;
            }

            Inventory& inventory = store->getInventory();

        switch (option) {
            case 1: {
                // Display Inventory
                inventory.displayInventory();
                break;
            }
            case 2: {
                // Add Product
                int productType;
                cout << "Select product type:" << endl;
                cout << "1. Regular Product" << endl;
                cout << "2. Perishable Product" << endl;
                cout << "3. Non-Perishable Product" << endl;
                cout << "Enter choice: ";
                cin >> productType;
                cin.ignore();
                int id, stockID, quantity;
                double price;
                string name, category;
                cout << "Enter product ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter product name: ";
                getline(cin, name);
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter stock ID: ";
                cin >> stockID;
                cout << "Enter quantity: ";
                cin >> quantity;
                cin.ignore();
                cout << "Enter category: ";
                getline(cin, category);

                Product* product = nullptr;

                switch (productType) {
                    case 1:
                        product = new Product(id, name, price, stockID, quantity, category);
                    break;
                    case 2: {
                        string expiryDate;
                        cout << "Enter expiry date (YYYY-MM-DD): ";
                        getline(cin, expiryDate);
                        product = new PerishableProduct(id, name, price, stockID, quantity, category, expiryDate);
                        break;
                    }
                    case 3: {
                        int warrantyPeriod;
                        cout << "Enter warranty period (months): ";
                        cin >> warrantyPeriod;
                        product = new NonPerishableProduct(id, name, price, stockID, quantity, category, warrantyPeriod);
                        break;
                    }
                    default:
                        cout << "Invalid product type." << std::endl;
                    continue;
                }
                inventory.addProduct(product);
                break;
            }
            case 3: {
                // Remove Product
                int productId;
                cout << "Enter product ID to remove: ";
                cin >> productId;
                inventory.removeProduct(productId);
                break;
            }
            case 4: {
                // Update Stock
                int productId, quantity;
                cout << "Enter product ID: ";
                cin >> productId;
                cout << "Enter new quantity: ";
                cin >> quantity;
                inventory.updateStock(productId, quantity);
                break;
            }
            case 5: {
                // Check Product Availability
                int productId;
                cout << "Enter product ID: ";
                cin >> productId;
                bool available = inventory.checkAvailability(productId);
                cout << "Product availability: " << (available ? "Available" : "Not available") << endl;
                break;
            }
            case 6: {
                StoreStockStats<double>* storeStockStats = StoreStockStats<double>::getInstance(&inventory);
                storeStockStats->calculateStockAmount();
                storeStockStats->display();
                storeStockStats->countProductInStore();
                break;
            }
            case 7: {
                int productId;
                cout << "Enter product ID: ";
                cin >> productId;
                Product *product=inventory.findProduct(productId);
                if (product!=nullptr) {
                    product->displayInfo();
                }
                else {
                    cout << "Product not found." << endl;
                }
                break;
            }
            case 0: {
                cout<<"Exiting"<<endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (option != 0);
}
//====================================================================================================//
//-------------------------------Main Menu------------------------------------------------------------//
//====================================================================================================//

void mainMenu(Mall *mall) {
    cout<<"Welcome to Mall!"<<endl;
    int option;
    do {
        cout<<"\n-----------------------Main Menu-------------------------------"<<endl;
        cout<<endl<<"======================================="<<endl;
        cout<<"1. Display Mall Information"<<endl;
        cout<<"2. Store Management System"<<endl;
        cout<<"3. Inventory & Product Management System"<<endl;
        cout<<"4. Employee Management System"<<endl;
        cout<<"5. Security System"<<endl;
        cout<<"6. Customer and Sales System"<<endl;
        cout<<"7. Event and Booking System"<<endl;
        cout<<"8. Parking System"<<endl;
        cout<<"9. Advertisement System"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>option;
        switch (option) {
            case 1: {
                mall->displayInfo();
                break;
            }
            case 2: {
                storeMenu(mall);
                break;
            }
            case 3: {
                inventoryMenu(mall);
                break;
            }
            case 4: {
                employeeMenu(mall);
                break;
            }
            case 5: {
                securityMenu(mall);
                break;
            }
            case 6: {
                customerAndSalesMenu(mall);
                break;
            }
            case 7: {
                eventAndBookingMenu(mall);
                break;
            }
        case 8: {
                    parkingMenu(mall);
                    break;
        }
        case 9: {
                    advertisementSystemMenu(mall);
                    break;
        }
            case 0: {
                cout<<"Exiting"<<endl;
                break;
            }
            default:
                cout<<"Invalid Choice. Please Try again!!!"<<endl<<endl;
        }
    }while(option!=0);
}



//=============================================================================

//BSSE24021 menu functions for display and mall member employee fun


//===========================================================================
void Mall::addEmployee(Employee* emp) {
        employees.push_back(emp);
        cout << "Employee " << emp->getName() << " added. "<< endl;
    }
vector<Employee*> &Mall::getAllEmployee() {
    return employees;
}

void Mall::showEmployees() const {
    cout << "\n=== Employees of Mall ===" << endl;
    if (employees.empty()) {
        cout << "No employees registered." << endl;
        return;
    }

    for (size_t i = 0; i < employees.size(); i++) {
        cout << "\nEmployee #" << (i + 1) << ":" << endl;
        employees[i]->displayInfo();
    }
}

    // Additional utility methods
int Mall::getEmployeeCount() const {
    return employees.size();
}

Employee* Mall::findEmployeeByName(const string& name) const {
    for (auto emp : employees) {
        if (emp->getName() == name) {
            return emp;
        }
    }
    return nullptr;
}

void Mall::removeEmployee(const string& name) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;
            employees.erase(it);
            cout << "Employee " << name << " removed from Mall " << endl;
            return;
        }
    }
    cout << "Employee " << name << " not found in Mall "  << endl;
}

    // JSON conversion methods
void Mall::saveEmployeeData(string filename) const {
    json j;
    j["mallName"] = name;
    j["employees"] = json::array();

    for (const auto& emp : employees) {
        j["employees"].push_back(emp->toJSON());
    }

    ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4); // Pretty printing with 4-space indent
        file.close();
        cout << "Data saved to " << filename << " successfully.\n";
    } else {
        cout << "Failed to open file for writing.\n";
    }
}

void Mall::loadEmployeeData(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File not found or couldn't be opened.\n";
        return;
    }

    json j;
    file >> j;
    file.close();
    name = j["mallName"];

    // Clear existing employees
    for (auto emp : employees) {
        delete emp;
    }
    employees.clear();

    // Load employees
    for (const auto& empJson : j["employees"]) {
        string type = empJson["type"];
        Employee* emp = nullptr;

        if (type == "Cashier") {
            emp = new Cashier();
        } else if (type == "Security") {
            emp = new Security();
        } else if (type == "Manager") {
            emp = new Manager();
        } else {
            emp = new Employee();
        }

        emp->fromJSON(empJson);
        employees.push_back(emp);
    }
}




void displayEmployeeMenu() {
    cout << "\n===== EMPLOYEE MANAGEMENT SYSTEM =====" << endl;
    cout << "1. Add Employee" << endl;
    cout << "2. Remove Employee" << endl;
    cout << "3. Display All Employees" << endl;
    cout << "4. Find Employee by Name" << endl;
    cout << "5. Calculate Employee Bonus" << endl;
    cout << "6. Display Employee Statistics" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
}

void displaySecurityMenu() {
    cout << "\n===== SECURITY SYSTEM =====" << endl;
    cout << "1. Grant Access to Employee" << endl;
    cout << "2. Log Security Event" << endl;
    cout << "3. Show Security Logs" << endl;
    cout << "4. Save Security Data to file" << endl;
    cout << "5. Load Security Data from File" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
}
void employeeMenu(Mall *mall) {
    int option;

    do {
        displayEmployeeMenu();
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1: { // Add Employee
                int empType;
                string name;
                double salary;
                int perfScore;

                cout << "\nSelect employee type:" << endl;
                cout << "1. Cashier" << endl;
                cout << "2. Security" << endl;
                cout << "3. Manager" << endl;
                cout << "Enter choice: ";
                cin >> empType;
                cin.ignore();

                cout << "Enter employee name: ";
                getline(cin, name);

                cout << "Enter salary: $";
                cin >> salary;

                cout << "Enter performance score (0-100): ";
                cin >> perfScore;

                Employee* emp = nullptr;

                switch (empType) {
                    case 1:
                        emp = new Cashier(name, salary, perfScore);
                        break;
                    case 2:
                        emp = new Security(name, salary, perfScore);
                        break;
                    case 3:
                        emp = new Manager(name, salary, perfScore);
                        break;
                    default:
                        cout << "Invalid employee type." << endl;
                        continue;
                }

                mall->addEmployee(emp);
                break;
            }
            case 2: { // Remove Employee
                string name;
                cout << "Enter employee name to remove: ";
                getline(cin, name);

                mall->removeEmployee(name);
                break;
            }
            case 3: { // Display All Employees
                mall->showEmployees();
                break;
            }
            case 4: { // Find Employee by Name
                string name;
                cout << "Enter employee name to find: ";
                getline(cin, name);

                Employee* emp = mall->findEmployeeByName(name);
                if (emp) {
                    emp->displayInfo();
                } else {
                    cout << "Employee not found." << endl;
                }
                break;
            }
            case 5: { // Calculate Employee Bonus
                string name;
                cout << "Enter employee name to calculate bonus: ";
                getline(cin, name);

                Employee* emp = mall->findEmployeeByName(name);
                if (emp) {
                    double bonus = emp->calculateBonus();
                    cout << emp->getName() << "'s bonus: $" << bonus << endl;
                } else {
                    cout << "Employee not found." << endl;
                }
                break;
            }
            case 6: { // Display Employee Statistics
                EmployeeStats<double> stats(&mall->getAllEmployee());
                stats.displayStats();
                break;
            }
            case 0: {
                cout << "Returning to main menu..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (option != 0);
}
SecuritySystem* SecuritySystem::instance = nullptr;
void securityMenu(Mall *mall) {
    SecuritySystem* securitySystem = SecuritySystem::getInstance();
    int option;

    do {
        displaySecurityMenu();
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1: { // Grant Access to Employee
                string name;
                cout << "Enter employee name to grant access: ";
                getline(cin, name);

                Employee* emp = mall->findEmployeeByName(name);
                if (emp) {
                    securitySystem->authorizeEmployee(emp);
                } else {
                    cout << "Employee not found." << endl;
                }
                break;
            }
            case 2: { // Log Security Event
                string event;
                cout << "Enter security event to log: ";
                getline(cin, event);

                securitySystem->logSecurityEvent(event);
                break;
            }
            case 3: { // Show Security Logs
                securitySystem->getLogManager().showLogs();
                break;
            }
            case 4: { // Save Security Data to File
                securitySystem->saveToFile("Security_Data.json");
                break;
            }
            case 5: { // Load Security Data from File

                securitySystem->loadFromFile("Security_Data.json");
                break;
            }
            case 0: {
                cout << "Returning to main menu..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (option != 0);
}
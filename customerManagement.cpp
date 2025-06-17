//
// Created by Bismillah Traders on 11/10/2024.

#include "customerManagement.h"
#include <iostream>
#include <fstream>
#include <string>
#include "SalesAndBillingSystem.h"
using namespace std;
void menuOfCustomer(Customer *&customer,int &customerCount){
    int choice;

        cout<<"\t\t\t\t\t---------------------------------------------"<<endl;
        cout<<"\t\t\t\t\t|--------CUSTOMER MANAGEMENT  SYSTEM--------|"<<endl;
        cout<<"\t\t\t\t\t---------------------------------------------"<<endl<<endl;
        cout<<"\t\t\t\t\t1- Add Customer\n";
        cout<<"\t\t\t\t\t2- View Customers\n";
        cout<<"\t\t\t\t\t3- View Customer History.\n";
        cout<<"\t\t\t\t\t4- View Loyalty Points.\n";
        cout<<"\t\t\t\t\t5- Analyze Customer Satisfaction\n";
        cout<<"\t\t\t\t\t6- Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch (choice) {
            case 1:
                system("clear");
                addCustomer(customer,customerCount);
            break;
            case 2:
                system("clear");
                viewCustomers();
            break;
            case 3:
                system("clear");
               viewCustomerHistory();
            break;
            case 4:
                system("clear");
                viewLoyaltyPoints();
            break;
            case 5:
                system("clear");
                viewCustomerAnalysis();
            break;
            case 6:
                system("clear");
                cout << "Exiting...\n";
            return ;
            default:
                system("clear");
                cout << "Invalid choice.\n";
        }
    menuOfCustomer(customer, customerCount);
    }

void addCustomer(Customer *&customer,int &customerCount) {
    char choice;
    do {
        Customer *temp=new Customer[customerCount+1];
        // Copy existing suppliers to new array
        for (int i=0;i<customerCount;i++) {
            temp[i]=customer[i];
        }
        delete[] customer;    // this is to delete old memory to avoid memory leakage
        customer=temp;
        cout<<"Enter Customer ID: ";
        cin>>temp[customerCount].id;
        fstream file("customers.txt");
        if (file.is_open()) {
            string name,line;int id;
            while (getline(file, line)) {
                id=stoi(line);           // this to read customer ID from the file
                getline(file, line);
                getline(file, line);
                getline(file, line);
                getline(file, line);
                if(id==temp[customerCount].id) {
                    cout<<"ID of Customer already added!"<<endl;
                    return;
                }
            }
            file.close();
        }
        else {
            cout<<"Unable to open file.\n";
            return;
        }
        cout<<"Enter Customer Name: ";
        cin.ignore();       // this allows spaces and clear buffers
        getline(cin, temp[customerCount].name);
        cout<<"Enter Customer Contact: ";
        getline(cin, temp[customerCount].contact);  // used to input line
        cout<<"Enter Customer Feedback: ";
        getline(cin, temp[customerCount].feedBack);
        temp[customerCount].loyaltyPoints=0;

        ofstream writeFile("customers.txt", ios::app);  //this allows to move around in the file,
        if (writeFile.is_open()) {
            writeFile<<temp[customerCount].id<<endl<<temp[customerCount].name<<endl<<temp[customerCount].contact<<endl<<temp[customerCount].loyaltyPoints<<endl<<temp[customerCount].feedBack<<endl;
            writeFile.close();
            cout<<"Customer added successfully!\n";
        }
        else {
            cout<<"Unable to open file.\n";
        }

        cout << "Do you want to add another customer? (y/n): ";
        cin >> choice;
        customerCount++;
    }while(choice=='y'||choice=='Y');
}
void viewCustomers() {
    ifstream file("customers.txt");
    if (file.is_open()) {
        cout<<"Customer List:\n";
        Customer customer;
        string name,line;
        while (getline(file, line)) {
            customer.id=stoi(line);
            getline(file, customer.name);
            getline(file, customer.contact);
            getline(file, line);
            customer.loyaltyPoints=stoi(line);
            getline(file, customer.feedBack);
            cout<<"ID: "<<customer.id<<endl;
            cout<<"Name: "<<customer.name<<endl;
            cout<<"Contact: "<<customer.contact<<endl;
            cout<<"Loyalty Points: "<<customer.loyaltyPoints<<endl;
            cout<<"Feed Back: "<<customer.feedBack<<endl;
            cout<<"-------------------------------------------------"<<endl;
        }
        file.close();
    }
    else {
        cout<<"Unable to open file.\n";
    }
}
int manageLoyaltyPoints(int customerId) {
    int updatedLoyaltyPoints;
    ifstream file("customers.txt");
    Customer customer;
    ofstream tempFile("temp.txt");
    if (file.is_open() && tempFile.is_open()) {
        string line;
        while (getline(file, line)) {
            customer.id=stoi(line);
            getline(file,customer.name);
            getline(file,customer.contact);
            getline(file, line);
            customer.loyaltyPoints=stoi(line);
            getline(file, customer.feedBack);
            if(customer.id==customerId) {
                customer.loyaltyPoints+=10;
                updatedLoyaltyPoints = customer.loyaltyPoints;
            }
            tempFile<<customer.id<<endl<<customer.name<<endl<<customer.contact<<endl<<customer.loyaltyPoints<<endl<<customer.feedBack<<endl;
        }
        file.close();
        tempFile.close();
        remove("customers.txt");
        rename("temp.txt", "customers.txt");
    }
    else {
        cout<<"Unable to open file.\n";
    }
    return updatedLoyaltyPoints ;
}
void viewLoyaltyPoints() {
    int id;
    cout<<"Enter Customer ID to view loyalty Points: ";
    cin>>id;
    ifstream file("customers.txt");
    Customer customer;
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            customer.id=stoi(line);
            getline(file,customer.name);
            getline(file,customer.contact);
            getline(file, line);
            customer.loyaltyPoints=stoi(line);
            getline(file, customer.feedBack);
            if(customer.id==id) {
                cout<<"ID: "<<customer.id<<endl;
                cout<<"Name: "<<customer.name<<endl;
                cout<<"Contact: "<<customer.contact<<endl;
                cout<<"Loyalty Points: "<<customer.loyaltyPoints<<endl;
                cout<<"Feed Back: "<<customer.feedBack<<endl;
            }
        }
        file.close();
    }
    else {
        cout<<"Unable to open file.\n";
    }
}
void viewCustomerHistory() {
    int id;
    cout<<"Enter Customer ID to view history: ";
    cin>>id;
    fstream file("purchase.txt");
    if (file.is_open()) {
        string line, vehicleId, quantity, totalAmount, discount, netAmount;
        int saleCount = 0;
        cout<<"\t\t\t\t\t-------------------------------------" << endl;
        cout<<"\t\t\t\t\t|-------CUSTOMER SALE HISTORY-------|" << endl;
        cout<<"\t\t\t\t\t-------------------------------------" << endl << endl;
        while (getline(file,line)) {
            int customerId=stoi(line);
            getline(file, vehicleId);
            getline(file, quantity);
            getline(file, totalAmount);
            getline(file, discount);
            getline(file, netAmount);
            saleCount++;
            if (id==customerId) {
                cout << "Sale #" << saleCount << endl;
                cout << "Customer ID: " << customerId << endl;
                cout << "Vehicle ID: " << vehicleId << endl;
                cout << "Quantity: " << quantity << endl;
                cout << "Total Cost: $" << totalAmount << endl;
                cout << "Discount: " << discount << "%" << endl;
                cout << "Final Amount: $" << netAmount << endl;
                cout << "---------------------------" << endl;
            }
        }
        file.close();
    }
    else {
        cout<<"Unable to open file.\n";
    }
}
void viewCustomerAnalysis(){
    cout<<"\t\t\t\t\t------------------------------------------" << endl;
    cout<<"\t\t\t\t\t|-------CUSTOMER FEEDBACK ANALYSIS-------|" << endl;
    cout<<"\t\t\t\t\t------------------------------------------" << endl << endl;
    int id;
    cout<<"Enter Customer ID to view history: ";
    cin>>id;
    ifstream file("customers.txt");
    Customer customer;
    string line;
    if (file.is_open()) {
        bool found=false;
        while (getline(file, line)) {
            customer.id=stoi(line);
            getline(file,customer.name);
            getline(file,customer.contact);
            getline(file, line);
            customer.loyaltyPoints=stoi(line);
            getline(file, customer.feedBack);
            if(customer.id==id) {
                cout<<"ID: "<<customer.id<<endl;
                cout<<"Name: "<<customer.name<<endl;
                cout<<"Feed Back: "<<customer.feedBack<<endl;
                found=true;
            }
        }
        file.close();
        if(!found) {
            cout<<"No id found.\n";
        }
    }
    else {
        cout<<"Unable to open file.\n";
    }
}
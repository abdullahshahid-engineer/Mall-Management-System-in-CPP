//
// Created by dell on 11/10/2024.
//

#include "SalesAndBillingSystem.h"   // header file for sale and billing system
#include<iostream>
#include<fstream>// fstream library for file handling

using namespace std;

#include "ProductAndInventoryManagement.h"    // header for product and inventory management
#include "customerManagement.h"       // header file for the customer management

// this is the function for displaying  the menu
void menuofSalesAndBillingSystem(Vehicles *&vehicle,const int &vehiclesCount,Sale &sale) {

    int choice;   // declare to variable to store the user choicce


        // display the menu of the sales and billing system
        cout<<"\t\t\t\t\t\t-------------------------------------------"<<endl;
        cout<<"\t\t\t\t\t\t|--------SALES AND BILLING SYSTEM---------|"<<endl;
        cout<<"\t\t\t\t\t\t-------------------------------------------"<<endl;
        cout<<"\t\t\t\t\t\t1- Display all the Vehicles."<<endl;
        cout<<"\t\t\t\t\t\t2- Sell the Vehicle."<<endl;
        cout<<"\t\t\t\t\t\t3- Generate Receipt"<<endl;
        cout<<"\t\t\t\t\t\t4- View History"<<endl;
        cout<<"\t\t\t\t\t\t5- Exit"<<endl;

        cout<<"Enter your choice: ";

    // base condition which get true then it enter under if condition
    if (!(cin >> choice)) {

   cout << "Invalid input. Please enter a number.\n";

        menuofSalesAndBillingSystem(vehicle, vehiclesCount, sale); // Retry menu

        return;
    }

        switch (choice) {
            case 1:
                system("clear");   // command to clear the terminal and used in linux
                viewAllVehicles(vehicle,vehiclesCount);   // function call that show all the vehicles
            break;
            case 2:
                system("clear");
                vehicleSelectionAndQuantity(vehicle,vehiclesCount,sale);   // function that done the sale process
            break;
            case 3:
                system("clear");
                generateReceipt(sale);   // function that generate the receipt of the sale
            break;
            case 4:
                system("clear");
            viewSaleHistory();   // function to view the history
            break;
            case 5:
                system("clear");
                cout<<"Exit"<<endl;     // Exiting the menu
                  return ;
            default:
                system("clear");
                cout<<"Invalid choice. Please try again.\n";
        }

    //  use the function for the recursive call and menu shows again and again until user want to
    //   exit.
    menuofSalesAndBillingSystem (vehicle ,vehiclesCount ,sale );


    }     // loops run until the user chooses to exit


// This is the function that is used to specify the quantity and sell the vehicle
void vehicleSelectionAndQuantity(Vehicles *&vehicles,const int &vehicleCount,Sale &sale) {

    cout<<"\t\t\t\t\t\t-------------------------------------"<<endl;
    cout<<"\t\t\t\t\t\t|--------SELECT THE VEHICLE---------|"<<endl;
    cout<<"\t\t\t\t\t\t-------------------------------------"<<endl;

// input customer ID for sale
    cout<<"Enter Customer ID: ";
    cin>>sale.customerId;

    //  open the file " customer.txt" to check whether the customer exists or not.
    fstream file("customers.txt");
    if (file.is_open()) {
        string line;
        int id;
        bool found = false;
        while (getline(file, line)) {       // Read each line  in the file

            // convert line to the integer(customer ID).
            id=stoi(line);

      /*When the code finds a matching customer ID (id == sale.customerId)
         then it reads four lines and skip over them*/
            getline(file, line);
            getline(file, line);
            getline(file, line);
            getline(file, line);
            if (id==sale.customerId) {
                found = true;   // customer found true
            }
        }
        // closing the file
        file.close();
        // If customer not found then display the following message under if statement
        if (!found) {
            cout<<"Customer not found"<<endl;
            return;
        }
    }

    cout<<"Enter Vehicle ID to purchase: ";
    // Input vehicle id for the purchase
    cin>>sale.vehicleId;
    int index = findVehicleIndex(vehicles, vehicleCount, sale.vehicleId);   // Find the vehicle index
    // If vehicle not found then display the message under if statement
    if (index==-1) {
        cout<<"Vehicle not found!"<<endl;
        return;
    }
    // functiom that display the vehicle information
    outputOfVehiclesFromArray(vehicles,index);

    // Input quantity for the sale
    cout<<"Enter quantity: ";
    cin>>sale.quantity;

    // Check if stock is available for the stock or not
    if (sale.quantity>vehicles[index].stock) {
        cout<<"Not enough stock available!"<<endl;
        return ;
    }
    // set the sale price
    sale.price=vehicles[index].price;

    // Calculate the total amount
    sale.totalAmount=vehicles[index].price*sale.quantity;

    // Update the stocks
    vehicles[index].stock-=sale.quantity;

    // Update the inventory in the system
    openFileAndWriteVehiclesToFile(vehicles,vehicleCount);
}

// This is the function to apply discount and tax to the sale
double applyDiscountAndTax(Sale &sale) {

    // Get the customer loyalty point
    int points=manageLoyaltyPoints(sale.customerId);

    // Check if the points is greater than or equal to 20 then apply 10% discount
    if(points>=20) {
        sale.discount = 10.0;   // Apply 10% discount
    }

    else {
        sale.discount=0;    // No discount applicable
    }

    //  Calculate the discount amount
    double discount = ( sale.totalAmount * sale.discount ) / 100;

    // Calculate the amount after the discount
    sale.netAmount = sale.totalAmount - discount;

    // Set tax percentage to 7%
    double tax ;

    // Calculate tax amount
    double taxAmount=(sale.netAmount *7 )/100;

    // Add tax to the net amount
    sale.netAmount+=taxAmount;

    // Return the final amount
    return sale.netAmount;
}

// Function that generate reciept of the sale
void generateReceipt(Sale &sale) {

    applyDiscountAndTax(sale);  // Apply discount and tax to the sale

    // Display the Receipt details
    cout<<"\t\t\t\t\t-------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------Receipt--------|"<<endl;
    cout<<"\t\t\t\t\t-------------------------"<<endl<<endl;
    cout<<"Customer ID: "<<sale.customerId<<endl;
    cout<<"Vehicle ID: " << sale.vehicleId<<endl;
    cout<<"Quantity: " << sale.quantity<<endl;
    cout<<"Total Cost: $" << sale.totalAmount<<endl;
    cout<<"Discount: " << sale.discount<<"%"<<endl;
    cout<<"Tax: 7%"<<endl;
    cout<<"Final Amount: $"<<sale.netAmount<<endl;

    // Write receipt details to the file
    ofstream writeFile("purchase.txt", ios::app);
    if (writeFile.is_open()) {
        writeFile<<sale.customerId<<endl<<sale.vehicleId<<endl<<sale.quantity<<endl<<sale.totalAmount<<endl<<sale.discount<<endl<<sale.netAmount<<endl;

        // close the file
        writeFile.close();
        cout<<"Receipt Generated successfully!\n";   // message display if receipt generate successfully
    }

    else {

        cout<<"Unable to open file.\n";            // message displays if file cant open due to some error
    }
}

// Function to view sale history from file
void viewSaleHistory() {

    // Open the file to read the history from the file
    ifstream readFile("purchase.txt");
    if (readFile.is_open()) {

        string customerId, vehicleId, quantity, totalAmount, discount, netAmount;
        int saleCount = 1;      // Sale count start with 1 and increment with each sale

        cout << "\t\t\t\t\t----------------------------" << endl;
        cout << "\t\t\t\t\t|-------SALE HISTORY-------|" << endl;
        cout << "\t\t\t\t\t----------------------------" << endl << endl;

        // Read and displays all sales records
        while (getline(readFile, customerId)) {
            getline(readFile, vehicleId);
            getline(readFile, quantity);
            getline(readFile, totalAmount);
            getline(readFile, discount);
            getline(readFile, netAmount);
            cout << "Sale #" << saleCount++ << endl;
            cout << "Customer ID: " << customerId << endl;
            cout << "Vehicle ID: " << vehicleId << endl;
            cout << "Quantity: " << quantity << endl;
            cout << "Total Cost: $" << totalAmount << endl;
            cout << "Discount: " << discount << "%" << endl;
            cout << "Final Amount: $" << netAmount << endl;
            cout << "---------------------------" << endl;
        }
          // Close the file
        readFile.close();
    } else
        {

        cout << "Unable to open file.\n" ;  // Message displays when if file cant be opened due to some error
    }
}
#include <iostream>
#include <cstdlib>
#include "customerManagement.h"
using namespace std;
#include "ProductAndInventoryManagement.h"
#include "registrationAndLoginSystem.h"
#include "employeeManagement.h"
#include "SupplierManagement.h"
#include "SalesAndBillingSystem.h"
int main()
{
    system("clear");
    User user;
    Sale sale;
    Vehicles *vehicles=nullptr; //making array of vehicles by pointer using nullptr
    Supplier *supplier=nullptr;
    Customer *customer=nullptr;
    int customerCount=0;
    int supplierCount=0;
    int vehicleCount=0; //initilaize with 0
    backupVehicles(vehicles,vehicleCount);
    backupSuppliers(supplier,supplierCount);
    int otp=0,choice=0;
    do {
        // Display main menu options for the system
        cout<<"\t\t\t\t\t----------------------------------------------"<<endl;
        cout<<"\t\t\t\t\t|--------SHOWROOM  MANAGEMENT  SYSTEM--------|"<<endl;
        cout<<"\t\t\t\t\t----------------------------------------------"<<endl<<endl;
        cout<<"\t\t\t\t\t1- Register User."<<endl;
        cout<<"\t\t\t\t\t2- Login User."<<endl;
        cout<<"\t\t\t\t\t3- Forgot Password."<<endl;
        cout<<"\t\t\t\t\t4- Exit"<<endl<<endl;
        cout<<"Enter choice : ";
        cin>>otp;
        // Process user's choice from the main menu
        switch (otp) {
            case 1:
                system("clear"); //to clear the screen linx command
                registerUser();
            break;
            case 2:
                system("clear");
            // If login is successful, display additional options for logged-in users
            if(loginUser(user)) {
                do {
                    cout<<"\t\t\t\t\t----------------------------------------------"<<endl;
                    cout<<"\t\t\t\t\t|--------SHOWROOM  MANAGEMENT  SYSTEM--------|"<<endl;
                    cout<<"\t\t\t\t\t----------------------------------------------"<<endl<<endl;
                    // Display options based on user role
                    if(user.role=="admin" || user.role=="employee") {
                        cout<<"\t\t\t\t\t1-  Employee Management."<<endl;
                        cout<<"\t\t\t\t\t2-  Product and Inventory Management."<<endl;
                        cout<<"\t\t\t\t\t3-  Customer Relationship Management."<<endl;
                        cout<<"\t\t\t\t\t4-  Sales and Billing System."<<endl;
                        cout<<"\t\t\t\t\t5-  Supplier Management."<<endl;
                        cout<<"\t\t\t\t\t6-  Exit the Program."<<endl<<endl;
                    }
                    cout<<"Enter your choice :  ";
                    cin>>choice;
                    // Process user's choice in the logged-in menu
                    switch(choice) {
                        case 1:
                            system("clear"); ////to clear the screen linx command
                            if(user.role=="admin") {
                                menuOfEmployeeSystem();
                            }
                            else {
                                cout<<"You have no Access to this module.It is only for admins."<<endl;
                            }
                        break;
                        case 2:
                            system("clear");  //to clear the screen linx command
                            menuOfProductAndInventoryManagement(vehicles,vehicleCount);
                        break;
                        case 3:
                            system("clear");
                            menuOfCustomer(customer,customerCount);
                        break;
                        case 4:
                            system("clear");
                            menuofSalesAndBillingSystem(vehicles,vehicleCount,sale);
                        break;
                        case 5:
                            system("clear");
                            menuOfSuplierManagement(supplier,supplierCount,vehicles,vehicleCount);
                        break;
                        case 6://exit program
                            system("clear");
                        cout<<"Back."<<endl;
                        break;
                        default:
                            system("clear");
                        cout<<"\t\t\t\t\tInvalid Choice!!!!!"<<endl;
                    }
                }while(choice!=6);// Loop until user selects exit.
            }
            break;
            case 3:
                system("clear"); //to clear the screen linx command
                forgotPassword();
            break;
            case 4:
                system("clear"); //to clear the screen linx command
                cout<<"Exiting Program!!!!!"<<endl;
            break;
            default:
                cout<<"Invalid choice. Please try again."<<endl;
        }
    }while(otp!=4);
    delete[] vehicles; //delete the vehicle to avoid memory leaking
    // Deallocate dynamic memory used by vehicles array
    delete[] supplier;
    delete[] customer;
    return 0;
}

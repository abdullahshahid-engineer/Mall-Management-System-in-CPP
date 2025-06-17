

#include "SupplierManagement.h"
#include "ProductAndInventoryManagement.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
void menuOfSuplierManagement(Supplier *&suppliers,int supplierCount,Vehicles *&vehicles,int &vehiclesCount) {
    int choice, id;

        cout<<"\t\t\t\t\t----------------------------------------------"<<endl;
        cout<<"\t\t\t\t\t|--------SUPPLIER  MANAGEMENT  SYSTEM--------|"<<endl;
        cout<<"\t\t\t\t\t----------------------------------------------"<<endl<<endl;
        cout<<"\t\t\t\t\t1. Add Supplier."<<endl; //For adding supplier
        cout<<"\t\t\t\t\t2. Display All Suppliers."<<endl; //to diplay all suppliers
        cout<<"\t\t\t\t\t3. Rate Supplier."<<endl; //for rating
        cout<<"\t\t\t\t\t4. Display Supplier Rating."<<endl; //to display rating
        cout<<"\t\t\t\t\t5. Update Supplier Data."<<endl; //to update data
        cout<<"\t\t\t\t\t6. Delete Any Supplier."<<endl; //delete the wanted supplier
        cout<<"\t\t\t\t\t7. Add Supplier Supply Record."<<endl;
        cout<<"\t\t\t\t\t8. View Supplier Record."<<endl;
        cout<<"\t\t\t\t\t9. Back"<<endl; //back to main menu
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice) {
            case 1:
                system("clear"); //this command clears the previous display of the project
                addSupplier(suppliers, supplierCount);
            break;
            case 2:
                system("clear"); //this command clears the previous display of the project
                displaySuppliers(suppliers,supplierCount);
            break;
            case 3:
                system("clear"); //this command clears the previous display of the project
                cout << "Enter Supplier ID to rate: ";
                cin>>id;
                rateSupplier(suppliers, supplierCount, id);
            break;
            case 4:
                system("clear"); //this command clears the previous display of the project
                cout<<"Enter Supplier ID to display rating: ";
                cin>>id;
                displaySupplierRating(suppliers, supplierCount, id);
            break;
            case 5:
                system("clear"); //this command clears the previous display of the project
                cout<<"Enter Supplier ID to update: ";
                cin>>id;
                updateSuppliers(suppliers, supplierCount, id);
            break;
            case 6:
                system("clear"); //this command clears the previous display of the project
                cout<<"Enter Supplier ID to delete: ";
                cin>>id;
                deleteSupplier(suppliers, supplierCount, id);
            break;
            case 7:
              system("clear");
              addProductFromSuppliers(suppliers, supplierCount,vehicles, vehiclesCount);
              break;
            case 8:
              system("clear");
              viewSupplierRecord(suppliers, supplierCount);
              break;
            case 9:
              system("clear"); //this command clears the previous display of the project
              cout<<"Back! "<<endl;
              return; // Recursion
            default:
              system("clear"); //this command clears the previous display of the project
                cout<<"Invalid choice! Please try again.\n";
        }
    menuOfSuplierManagement(suppliers,supplierCount,vehicles,vehiclesCount);
}
// This function adds a new supplier
void addSupplier(Supplier *&suppliers, int &supplierCount) {
    Supplier* newSuppliers = new Supplier[supplierCount+1];
    // This loop adds the existing suppliers to the new array
    for (int i=0;i<supplierCount;i++) {
        newSuppliers[i]=suppliers[i];
    }
    delete[] suppliers;
    suppliers = newSuppliers;
    // now "suppliers" points towards newsupliers
    // ---------Add new supplier details
    cout<<"Enter Supplier ID: ";
    cin>>newSuppliers[supplierCount].id;
    cin.ignore();
    // to use getline function afetrwards
    cout<<"Enter Supplier Name: ";
    getline(cin,newSuppliers[supplierCount].name);
    cout<<"Enter Contact Number: ";
    getline(cin,newSuppliers[supplierCount].contact);
    cout<<"Enter Address: ";
    getline(cin,newSuppliers[supplierCount].address);
    cout<<"Enter Email: ";
    getline(cin,newSuppliers[supplierCount].email);
    // Initialize ratings to zero so all the suppliers have 0 rating at the beginning
    newSuppliers[supplierCount].rating=0;
    supplierCount++;
    // prevoiusly [supplierCount [0] + 1]
    // now [supplierCount [1]
    writeSuppliers(suppliers,supplierCount);
    // This function adds the new supplier to file
}
void writeSuppliers(Supplier *&suppliers, int &supplierCount) {
    // ---------write supplier data to file
    ofstream file("suppliersData.txt");
    if (file.is_open()) {
        for (int i=0;i<supplierCount;i++)
      // this loop writes the data of supplier to file one by one
      // till all the suppliers data
      {
            file<<suppliers[i].id<<endl;
            file<<suppliers[i].name<<endl;
            file<<suppliers[i].contact<<endl;
            file<<suppliers[i].address<<endl;
            file<<suppliers[i].email<<endl;
            file<<suppliers[i].rating<<endl;
        }
        file.close();
    }
    else {
        cout<<"Unable to open file."<<endl;
    }
}
void backupSuppliers(Supplier *&suppliers, int &supplierCount)
// copy data into array from file data
{
    ifstream suppliersDataFile("suppliersData.txt");
    if (!suppliersDataFile.is_open()) {
        cout<<"Error: Unable to open file 'suppliersData.txt'."<<endl;
        return;
    }
    string line;
    int lineCount = 0;

    while (getline(suppliersDataFile, line)) // loop to get line and count line
    {
        lineCount++;
    }
    suppliersDataFile.clear(); // Clear EOF flag (eof buffer clear)
    suppliersDataFile.seekg(0, ios::beg); // move to the file beginning
    // Each supplier has 6 lines of data
    supplierCount=lineCount/6;
    Supplier *temp=new Supplier[supplierCount];
    int index = 0;
    while (index<supplierCount && getline(suppliersDataFile, line)) {
        // Make sure each line has data before accessing it
        temp[index].id = stoi(line);
        if (!getline(suppliersDataFile, temp[index].name)) break;
        if (!getline(suppliersDataFile, temp[index].contact)) break;
        if (!getline(suppliersDataFile, temp[index].address)) break;
        if (!getline(suppliersDataFile, temp[index].email)) break;
        if (!getline(suppliersDataFile, line)) break;
        temp[index].rating=stoi(line);  // Use stod for double conversion
        index++;
    }
    suppliersDataFile.close();
    // Delete any existing suppliers array before reassigning
    if (suppliers!=nullptr) {
        delete[] suppliers;
    }
    suppliers=temp;
}
// Function to display all suppliers
void displaySuppliers(Supplier *suppliers,int supplierCount) {
    cout<<"\t\t\t\t\t-------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------ALL SUPPLIERS--------|"<<endl;
    cout<<"\t\t\t\t\t-------------------------------"<<endl<<endl;
    if(supplierCount==0){
      cout<<"No Supplier Found"<<endl;
      }
    for(int i=0;i<supplierCount;i++)
      // this loop displays the data of all the suplliers one by one
      {
        cout<<"ID : "<<suppliers[i].id<<endl;
        cout<<"Name : "<<suppliers[i].name<<endl;
        cout<<"Contact : "<<suppliers[i].contact<<endl;
        cout<<"Address : "<<suppliers[i].address<<endl;
        cout<<"Email : "<<suppliers[i].email<<endl;
        cout<<"------------------------------------------------------"<<endl<<endl;
    }
}
void deleteSupplier(Supplier *&suppliers, int &supplierCount,int id) {
    cout << "\t\t\t\t\t---------------------------------" << endl;
    cout << "\t\t\t\t\t|--------DELETE SUPPLIER--------|" << endl;
    cout << "\t\t\t\t\t---------------------------------" << endl << endl;
    int index=findSupplierIndex(suppliers, supplierCount, id);
    if (index==-1) // checking index from index function
    {
        cout<<"Supplier not found."<<endl;
        return;
    }
    Supplier *newSuppliers = new Supplier[supplierCount - 1]; // new array and remove previuos supplier data
    int j=0;
    for (int i=0; i < supplierCount; i++) {
        if (i!=index) {
            newSuppliers[j++]=suppliers[i]; // Copy all suppliers except the deleted one
        }
    }
    delete[] suppliers; // Delete old memory
    suppliers=newSuppliers; // Point suppliers to new array
    supplierCount--;
    cout<<"Supplier deleted successfully."<<endl;
    writeSuppliers(suppliers, supplierCount);
}
int findSupplierIndex(Supplier *&suppliers, int supplierCount, int id)
// this function is used in the function for deleteing supplier
    // and also for updating suppliers data
{
    for (int i = 0; i < supplierCount; i++) {
        if (suppliers[i].id == id) {
            return i;
        }
    }
    return -1;
    // Return -1 if the supplier with the given ID is not found
}
void updateSuppliers(Supplier *&suppliers, int supplierCount,int id) {
    cout<<"\t\t\t\t\t---------------------------------" << endl;
    cout<<"\t\t\t\t\t|--------UPDATE SUPPLIER--------|" << endl;
    cout<<"\t\t\t\t\t---------------------------------" << endl << endl;
    int index = findSupplierIndex(suppliers, supplierCount, id);
    if (index == -1)
    // from previous function
    // it checks whether the suppliers ID are in our record
    {
        cout<<"Supplier not found."<<endl;
        return;
    }
    cout<<"Enter New Name of Supplier: ";
    cin.ignore();
    getline(cin, suppliers[index].name);
    cout<<"Enter New Contact: ";
    getline(cin, suppliers[index].contact);
    cout << "Enter New Address: ";
    getline(cin, suppliers[index].address);
    cout<<"Enter New Email address: ";
    getline(cin, suppliers[index].email);
    cout << "Updated Supplier data successfully." << endl;
    // to add new information in file
    writeSuppliers(suppliers, supplierCount);
}
// Function to rate a supplier
void rateSupplier(Supplier*& suppliers, int count, int id) {
    bool found = false;
    //check for suppliers id
    for (int i = 0; i < count; i++) {
        if (suppliers[i].id == id) {
            found = true;
            // ID found
            cout << "Enter a rating for supplier " << suppliers[i].name << " (1 to 5): ";
            cin >> suppliers[i].rating;
            while (suppliers[i].rating<1 || suppliers[i].rating>5)
            //  loop for valid rating
            {
                cout << "Invalid rating! Please enter a rating between 1 and 5: ";
                cin >> suppliers[i].rating;
            }
            break;
        }
    }
    if (!found) {
        cout << "Supplier ID not found.\n";
    }
}
// Function to display rating of a supplier
void displaySupplierRating(Supplier* suppliers, int count, int id) {
    bool found = false;
    // to check if suppliers ID was found or not
    for (int i = 0; i < count; i++) {
        if (suppliers[i].id == id)
      // to check if ID matches
       {
            found = true; // means ID found
            if (suppliers[i].rating>0)
            // checking for rating
            {
                cout<<"Rating for supplier "<<suppliers[i].name<<": "<<suppliers[i].rating<<" out of 5."<<endl;
            } else // if it does not have any rating
            {
                cout << "No ratings for supplier " << suppliers[i].name << endl;
            }
            break;
        }
    }
    if (!found)
    // if suppliers ID not found then it shows the error
    {
        cout << "Supplier ID not found.\n";
    }
}
void addProductFromSuppliers(Supplier *&suppliers, int supplierCount,Vehicles *&vehicles,int &vehiclesCount) {
    int supplierid;
    cout<<"Enter Supplier ID: ";
    cin>>supplierid;
    bool found=false;
    for (int i = 0; i < supplierCount; i++) {
        if (suppliers[i].id == supplierid) {
            found = true;
        }
    }
    if(found) {
        addVehicles(vehicles, vehiclesCount);
        openFileAndWriteVehiclesToFile(vehicles,vehiclesCount);
    } else {
        cout<<"Supplier ID not found.\n";
        return;
    }
    ofstream supplierRecordfile("supplierRecord.txt",ios::app);
    supplierRecordfile<<supplierid<<endl<<vehicles[vehiclesCount-1].id<<endl<<vehicles[vehiclesCount-1].name<<endl;
    supplierRecordfile<<vehicles[vehiclesCount-1].model<<endl<<vehicles[vehiclesCount-1].company<<endl<<vehicles[vehiclesCount-1].stock<<endl;
    supplierRecordfile<<vehicles[vehiclesCount-1].price<<endl;
    supplierRecordfile.close(); // -1 in vehicle count is due to that the array index starts from 0
}
void viewSupplierRecord(Supplier *&suppliers, int supplierCount) {
    int supplierid;
    cout<<"Enter Supplier ID: ";
    cin>>supplierid;
    bool found=false;
    string line;
    int id;
    fstream supplierRecordfile("supplierRecord.txt");
    if(supplierRecordfile.is_open()) {
        while (getline(supplierRecordfile, line)) {
            id=stoi(line);
            if(id==supplierid) {
                cout<<"Supplier ID: "<<id<<endl;
                getline(supplierRecordfile, line);
                cout<<"Vehicle ID: "<<line<<endl;
                getline(supplierRecordfile, line);
                cout<<"Name: "<<line<<endl;
                getline(supplierRecordfile, line);
                cout<<"Model: "<<line<<endl;
                getline(supplierRecordfile, line);
                cout<<"Company: "<<line<<endl;
                getline(supplierRecordfile, line);
                cout<<"Stock: "<<line<<endl;
                getline(supplierRecordfile, line);
                cout<<"Price: $"<<line<<endl;
                cout << "---------------------------" << endl;
                found=true;
            }
            else { // skip lines if ID does not match to the required ID
                getline(supplierRecordfile, line);
                getline(supplierRecordfile, line);
                getline(supplierRecordfile, line);
                getline(supplierRecordfile, line);
                getline(supplierRecordfile, line);
                getline(supplierRecordfile, line);
            }
        }
        supplierRecordfile.close();
    }
    if(!found) {
        cout<<"Supplier ID not found.\n";
}
}

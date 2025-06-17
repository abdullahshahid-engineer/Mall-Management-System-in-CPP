#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;
#include "ProductAndInventoryManagement.h"
int choice=0;
void menuOfProductAndInventoryManagement(Vehicles *&vehicles,int &vehicleCount) {
    do {
        cout<<"\t\t\t\t\t--------------------------------------------------"<<endl;
        cout<<"\t\t\t\t\t|--------VEHICLE AND INVENTORY MANAGEMENT--------|"<<endl;
        cout<<"\t\t\t\t\t--------------------------------------------------"<<endl<<endl;
        cout<<"\t\t\t\t\t1-  Vehicle Management."<<endl;
        cout<<"\t\t\t\t\t2-  Inventory Control and Stock Management."<<endl;
        cout<<"\t\t\t\t\t3-  Inventory Reporting and Analysis."<<endl;
        cout<<"\t\t\t\t\t4-  Back."<<endl<<endl;
        cout<<"Enter your choice :  ";
        cin>>choice;
        switch(choice) {
            case 1:
                system("clear");   //to clear the screen linx command
                menuOfProductManager(vehicles,vehicleCount);  //menu of product manage
            break;
            case 2:
                system("clear");
                menuOfInventoryControlAndStockManagement(vehicles,vehicleCount);  //menu of stock
            break;
            case 3:
                system("clear");
            salesInventoryAnalysis(vehicles,vehicleCount);    //analysis of inventory
            break;
            case 4:
              system("clear");
              cout<<"Back!!"<<endl;
              break;
            break;
            default:
                system("clear");
            cout<<"\t\t\t\t\tInvalid Choice!!!!!"<<endl;
        }

    }while(choice!=4); //loop for repetivly show menu and exit at back
}
//menu of product manager
void menuOfProductManager(Vehicles *&vehicles,int &vehicleCount) {
    int choices=0;
    do {   //Display of menu list
        cout<<"\t\t\t\t\t------------------------------------"<<endl;
        cout<<"\t\t\t\t\t|--------VEHICLE Management--------|"<<endl;
        cout<<"\t\t\t\t\t------------------------------------"<<endl<<endl;
        cout<<"\t\t\t\t\t1-  Add New Vehicles."<<endl;
        cout<<"\t\t\t\t\t2-  Update Vehicles Details."<<endl;
        cout<<"\t\t\t\t\t3-  Delete Vehicles."<<endl;
        cout<<"\t\t\t\t\t4-  View All Vehicles."<<endl;
        cout<<"\t\t\t\t\t5-  Display Vehicles By Applying Filters."<<endl;
        cout<<"\t\t\t\t\t6-  Sort Vehicles By Price."<<endl;
        cout<<"\t\t\t\t\t7-  Back."<<endl<<endl;
        cout<<"Enter your choice :  ";
        cin>>choices;
        switch(choices) {
            case 1:
                system("clear");
                addVehicles(vehicles,vehicleCount); //function to add vehicle
                openFileAndWriteVehiclesToFile(vehicles,vehicleCount); //write vehicle to file
            break;
            case 2:
                system("clear");
                updateVehicles(vehicles,vehicleCount);  //update data of vehicle
            break;
            case 3:
                system("clear");
                deleteVehicle(vehicles,vehicleCount); //Delete any vehicle
            break;
            case 4:
                system("clear");
                viewAllVehicles(vehicles,vehicleCount); //view all vehicles
            break;
            case 5:
                system("clear");
                menuOfDisplayVehiclesByFilters(vehicles,vehicleCount);  //menu of filters
            break;
            case 6:
                system("clear");
                sortVehiclesByPrice(vehicles,vehicleCount);
            break;
            case 7:
              system("clear");
              cout<<"Back!!"<<endl;
              break;
            default:
                system("clear");
                cout<<"\t\t\t\t\tInvalid Choice!!!!!"<<endl;
        }
    }while(choices!=7);
}
//make new array by using DMA to store vehicles 
void makingNewArray(Vehicles *&vehicles,int &vehicleCount,int n) {
    Vehicles *temp=new Vehicles[vehicleCount+n]; //create new array
    for(int i=0;i<vehicleCount;i++) {
        if(vehicles!=nullptr) { //check the previous vehicle is null or not
            temp[i]=vehicles[i];
        }
    }
    if(vehicles!=nullptr) {
        delete [] vehicles;  //delete the vehicle
    }
    vehicles=temp;
}
//Add vehicles from user
void addVehicles(Vehicles *&vehicles,int &vehicleCount) {
    cout<<"\t\t\t\t\t-----------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------ADD VEHICLE--------|"<<endl;
    cout<<"\t\t\t\t\t-----------------------------"<<endl<<endl;
    makingNewArray(vehicles,vehicleCount,1);  //new array make greter 1 time then previous array
    cout<<"Enter Vehicle Unique ID : ";
    cin>>vehicles[vehicleCount].id;
    for(int i=0;i<vehicleCount;i++) {
        if(vehicles[vehicleCount].id==vehicles[i].id) {
            cout<<"ERROR!!!!!"<<endl;
            cout<<"You entered wrong or same ID."<<endl;
            cout<<"Your Vehicle was not added to the system."<<endl;
            cout<<"Please try again."<<endl;
            return;  //exit program in case of id is not unique
        }
    }
    getInputVehicles(vehicles,vehicleCount); //take input vehicle data
    vehicleCount++;
}
//take input values from users
void getInputVehicles(Vehicles *&vehicles,int index) {
    cout<<"Enter Vehicle Name : ";
    cin.ignore();
    getline(cin,vehicles[index].name);
    cout<<"Enter Vehicle Model : ";
    getline(cin,vehicles[index].model);
    cout<<"Enter Vehicle Category : ";
    getline(cin,vehicles[index].category);
    cout<<"Enter Vehicle Company : ";
    getline(cin,vehicles[index].company);
    cout<<"Enter Vehicle Colour : ";
    getline(cin,vehicles[index].color);
    cout<<"Enter Vehicle Fuel Consumption (L/100km) \\ Battery Timing (on full Charge) : ";
    cin>>vehicles[index].fuelConsumption;
    cout<<"Enter Vehicle Horse Power (HP) : ";
    cin>>vehicles[index].horsePower;
    cout<<"Enter Vehicle Price : $";
    cin>>vehicles[index].price;
    cout<<"Enter Vehicle Quantity : ";
    cin>>vehicles[index].stock;
}
//write all vehicles to file to store
void writeVehiclesToFile(ofstream &vehiclesDataFile,Vehicles *vehicles,int vehicleCount) {
    for(int i=0;i<vehicleCount;i++) {
        vehiclesDataFile<<vehicles[i].id<<endl;
        vehiclesDataFile<<vehicles[i].name<<endl;
        vehiclesDataFile<<vehicles[i].model<<endl;
        vehiclesDataFile<<vehicles[i].category<<endl;
        vehiclesDataFile<<vehicles[i].company<<endl;
        vehiclesDataFile<<vehicles[i].color<<endl;
        vehiclesDataFile<<vehicles[i].fuelConsumption<<endl;
        vehiclesDataFile<<vehicles[i].horsePower<<endl;
        vehiclesDataFile<<vehicles[i].price<<endl;
        vehiclesDataFile<<vehicles[i].stock<<endl;
    }
}
//open file and call write function
void openFileAndWriteVehiclesToFile(Vehicles *vehicles,int vehicleCount) {
    ofstream vehiclesDataFile("vehiclesData.txt");  //open file
    if (!vehiclesDataFile.is_open()) { //check file is open or not
        cout<<"Error: Unable to open file 'vehiclesData.txt'."<<endl;
        return; //exit if file is not open
    }
    writeVehiclesToFile(vehiclesDataFile,vehicles,vehicleCount);
    vehiclesDataFile.close();
}
//backup vehicles in array from file
void backupVehicles(Vehicles *&vehicles,int &vehicleCount) {
    ifstream vehiclesDataFile("vehiclesData.txt");
    if (!vehiclesDataFile.is_open()) {
        cout<<"Error: Unable to open file 'vehiclesData.txt'." << endl;
        return; //exit if file is not open
    }
    lineCountFromFile(vehiclesDataFile,vehicleCount);  //count the all lines
    vehiclesDataFile.clear(); //Clear EOF flag
    vehiclesDataFile.seekg(0, ios::beg); //Rewind file to beginning
    makingNewArray(vehicles,vehicleCount,0);
    getDataFromFile(vehiclesDataFile,vehicles,vehicleCount); //get data from file to array
    vehiclesDataFile.close();
}
//count the line for making new array of the size
void lineCountFromFile(ifstream &vehiclesDataFile,int &vehicleCount) {
    string line;
    int lineCount=0;
    while (getline(vehiclesDataFile, line)) {  //get every line from file
        lineCount++;
    }
    vehicleCount=(lineCount/10);
}
//Get data from file and store in array
void getDataFromFile(ifstream &vehiclesDataFile,Vehicles *&vehicles,int &vehicleCount) {
    int index=0; string line;
    //index is less than the vehiclecount
    while (index<vehicleCount && getline(vehiclesDataFile,line)) {
        vehicles[index].id=stoi(line);  //Use stoi for integer conversion
        if (!getline(vehiclesDataFile,vehicles[index].name)) break;
        if (!getline(vehiclesDataFile,vehicles[index].model)) break;
        if (!getline(vehiclesDataFile,vehicles[index].category)) break;
        if (!getline(vehiclesDataFile,vehicles[index].company)) break;
        if (!getline(vehiclesDataFile,vehicles[index].color)) break;
        if (!getline(vehiclesDataFile,line)) break;
        vehicles[index].fuelConsumption=stod(line); //Use stod for double conversion
        if (!getline(vehiclesDataFile,line)) break;
        vehicles[index].horsePower=stoi(line);   //Use stoi for integer conversion
        if (!getline(vehiclesDataFile,line)) break;
        vehicles[index].price=stod(line);
        if (!getline(vehiclesDataFile,line)) break;
        vehicles[index].stock=stoi(line);
        index++;
    }
}
//find index of id
int findVehicleIndex(Vehicles *&vehicles,int vehicleCount,int id) {
    for(int i=0;i<vehicleCount;i++) {
        if(vehicles[i].id==id) {  //check the id
            return i; //return index where id match
        }
    }
    return -1;
}
//delete any vehicle
void deleteVehicle(Vehicles *&vehicles, int &vehicleCount) {
    cout<<"\t\t\t\t\t--------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------DELETE VEHICLE--------|"<<endl;
    cout<<"\t\t\t\t\t--------------------------------"<<endl<<endl;
    int id;
    cout<<"Enter Vehicle ID to delete: ";
    cin>>id;
    int index=findVehicleIndex(vehicles, vehicleCount, id); //check the id of vehicle
    if (index==-1) {
        cout<<"Vehicle not found."<<endl;
        return;
    }
    Vehicles *newVehicles = new Vehicles[vehicleCount - 1]; //make new array
    int j=0;
    for(int i=0; i<vehicleCount;i++) {
        if (i != index) {
            newVehicles[j++]=vehicles[i]; //Copy all vehicles except the deleted one
        }
    }
    delete[] vehicles; // Delete old memory
    vehicles=newVehicles; // Point vehicles to new array
    vehicleCount--;
    cout<<"Vehicle deleted successfully."<<endl;
    openFileAndWriteVehiclesToFile(vehicles, vehicleCount); //write new array to file
}
//Output vehicle data of given index
void outputOfVehiclesFromArray(Vehicles *vehicles,const int &index) {
    //Displaying data
    cout<<" ID : "<<vehicles[index].id<<endl;
    cout<<" Name : "<<vehicles[index].name<<endl;
    cout<<" Model : "<<vehicles[index].model<<endl;
    cout<<" Category : "<<vehicles[index].category<<endl;
    cout<<" Company : "<<vehicles[index].company<<endl;
    cout<<" Color : "<<vehicles[index].color<<endl;
    if(vehicles[index].category=="Electric") {
        cout<<" Battery Timing : "<<vehicles[index].fuelConsumption<<"Km (On Full Charge)"<<endl;
    }else {
        cout<<" Fuel Consumption : "<<vehicles[index].fuelConsumption<<" L/100km "<<endl;
    }
    cout<<" Horse Power : "<<vehicles[index].horsePower<<" HP"<<endl;
    cout<<" Price : $"<<vehicles[index].price<<endl;
    cout<<" Stock : "<<vehicles[index].stock<<endl;
}
//view all vehicles to user
void viewAllVehicles(Vehicles *vehicles,const int &vehicleCount) {
    cout<<"\t\t\t\t\t------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------ALL VEHICLES--------|"<<endl;
    cout<<"\t\t\t\t\t------------------------------"<<endl<<endl;
    if(vehicleCount==0) { //check vehicle in system of array
        cout<<"No Vehicle to Display."<<endl;
        return; //exit if no vehicle found
    }
    for(int i=0;i<vehicleCount;i++){
        outputOfVehiclesFromArray(vehicles,i); //call function to output of vehicle
        cout<<"----------------------------------------"<<endl;
    }
}
//Update the vehicles by its id
void updateVehicles(Vehicles *&vehicles,const int &vehicleCount) {
    cout<<"\t\t\t\t\t--------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------UPDATE VEHICLE--------|"<<endl;
    cout<<"\t\t\t\t\t--------------------------------"<<endl<<endl;
    cout<<"Enter Vehicle ID to update : ";
    int id;
    cin>>id;
    int index=findVehicleIndex(vehicles,vehicleCount,id); //check id is exsist or not
    if(index==-1) { //check index
        cout<<"Vehicle not found."<<endl;
        return; //exit if index is not occur
    }
    getInputVehicles(vehicles,index);  //input vehicle values
    cout<<"Updated Vehicle data Successfully"<<endl;
    openFileAndWriteVehiclesToFile(vehicles, vehicleCount); //write updated data in file
    cout<<"Here is the updated vehicle."<<endl;
    outputOfVehiclesFromArray(vehicles, index); //show the update data of vehicle
}
//menu of different filters
void menuOfDisplayVehiclesByFilters(Vehicles *vehicles,const int &vehicleCount) {
    int choices=0;
    do {
        cout<<"\t\t\t\t\t------------------------------------------" << endl;
        cout<<"\t\t\t\t\t|--------DISPLAY VEHICLES BY FILTER------|" << endl;
        cout<<"\t\t\t\t\t------------------------------------------" << endl << endl;
        cout<<"\t\t\t\t\t1- Filter by Price Range."<<endl;
        cout<<"\t\t\t\t\t2- Filter by Fuel Consumption/Battery Timing."<<endl;
        cout<<"\t\t\t\t\t3- Filter by Horse Power."<<endl;
        cout<<"\t\t\t\t\t4- Combined Filter."<<endl;
        cout<<"\t\t\t\t\t5- Back"<<endl<<endl;
        cout<<"Enter your choice: ";
        cin>>choices;
        switch(choices){
            case 1:
                system("clear");
                applyFiltersOnPrice(vehicles, vehicleCount);
            break;
            case 2:
                system("clear");
                applyFiltersOnFuelConsumption(vehicles, vehicleCount);
            break;
            case 3:
                system("clear");
                applyFiltersOnHorsePower(vehicles, vehicleCount);
            break;
            case 4:
                system("clear");
                applyCombinedFilters(vehicles, vehicleCount);
            break;
            case 5:
                system("clear");
            cout<<"Back"<<endl;
            break;
            default:
                cout<<"Invalid Choice!"<<endl;
        }
    } while (choices!=5); //loop for repetivly show menu and exit at back
}
//filter on price
void applyFiltersOnPrice(Vehicles *vehicles, const int &vehicleCount) {
    cout<<"\t\t\t\t\t---------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------FILTER ON PRICE--------|"<<endl;
    cout<<"\t\t\t\t\t---------------------------------"<<endl<<endl;
    double minPrice, maxPrice;
    cout<<"Enter minimum price: $";
    cin>>minPrice;
    cout<<"Enter maximum price: $";
    cin>>maxPrice;
    cout<<endl<<"\t\t\tVehicles in price range $"<<minPrice<<" - $"<<maxPrice<<"!"<<endl<<endl;
    bool found = false;
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i].price>=minPrice && vehicles[i].price<=maxPrice) { //check vehicles in price range
            outputOfVehiclesFromArray(vehicles,i);
            cout<<"----------------------------------------"<<endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No vehicles found in the specified price range." << endl;
    }
}
//apply filter on fuel
void applyFiltersOnFuelConsumption(Vehicles *vehicles, const int &vehicleCount) {
    cout<<"\t\t\t\t\t-------------------------------------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------FILTER ON FUEL CONSUMPTION / BATTERY TIMING--------|"<<endl;
    cout<<"\t\t\t\t\t-------------------------------------------------------------"<<endl<<endl;
    double fuelConsumption;
    cout<<"Enter Maximum Fuel consumption (L/100km) or Battery timing (Km On Full Charge) to filter by: ";
    cin>>fuelConsumption;
    cout<<endl<<"\t\t\tVehicles less than fuel consumption/battery timing of "<<fuelConsumption<<"!"<<endl<<endl;
    bool found = false;
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i].fuelConsumption<=fuelConsumption) { //check vehicles related to less than fuel range
            outputOfVehiclesFromArray(vehicles,i);
            cout<<"----------------------------------------"<<endl;
            found = true;
        }
    }
    if (!found) {
        cout<<"No vehicles found with the specified fuel consumption or battery timing."<<endl;
    }
}
//apply filter on horsepower
void applyFiltersOnHorsePower(Vehicles *vehicles, const int &vehicleCount) {
    cout<<"\t\t\t\t\t---------------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------FILTER ON HORSE POWER--------|"<<endl;
    cout<<"\t\t\t\t\t---------------------------------------"<<endl<<endl;
    int minHP, maxHP;
    cout<<"Enter minimum horsepower: ";
    cin>>minHP;
    cout<<"Enter maximum horsepower: ";
    cin>>maxHP;
    cout<<endl<<"\t\t\tVehicles with horsepower in range "<<minHP<<" - "<<maxHP<<"!"<<endl<<endl;
    bool found=false;
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i].horsePower >= minHP && vehicles[i].horsePower <= maxHP) { //check vehicle in range
            outputOfVehiclesFromArray(vehicles, i);
            cout<<"----------------------------------------"<<endl;
            found=true;
        }
    }
    if (!found) {
        cout<<"No vehicles found in the specified horsepower range."<<endl;
    }
}
//apply combine filters
void applyCombinedFilters(Vehicles *vehicles, const int &vehicleCount) {
    string company,category;
    double minPrice,maxPrice,fuelConsumption;
    int minHP,maxHP;
    cout<<"\t\t\t\t\t---------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------COMBINED FILTER--------|"<<endl;
    cout<<"\t\t\t\t\t---------------------------------"<<endl<<endl;
    cout<<"Enter minimum price : $";
    cin>>minPrice;
    cout<<"Enter maximum price : $";
    cin>>maxPrice;
    cout<<"Enter Maximum fuel consumption/battery timing : ";
    cin>>fuelConsumption;
    cout<<"Enter minimum horsepower : ";
    cin>>minHP;
    cout<<"Enter maximum horsepower : ";
    cin>>maxHP;
    bool found=false;
    cout<<endl<<endl<<"\t\t\t\tVehicles matching the combined filters!"<<endl<<endl;
    for (int i=0;i<vehicleCount;i++) {
        if(vehicles[i].fuelConsumption<=fuelConsumption &&
            vehicles[i].price>=minPrice && vehicles[i].price<=maxPrice &&
            vehicles[i].horsePower>=minHP &&
            vehicles[i].horsePower<=maxHP) { //check all the ranges and get vehicle
            outputOfVehiclesFromArray(vehicles,i);
            cout<<"----------------------------------------"<<endl;
            found=true;
        }
    }
    if(!found){ //if vehicle is not found
        cout<<"No vehicles found matching the specified filters."<<endl;
    }
}
//sort vehicles by their prices
void sortVehiclesByPrice(Vehicles *vehicles,const int &vehicleCount) {
    for (int i=0;i<vehicleCount-1;i++) {
        for (int j=0;j<vehicleCount-i-1;j++) {
            if (vehicles[j].price>vehicles[j+1].price) {
                //Swap vehicles[j] and vehicles[j+1]
                Vehicles temp=vehicles[j];
                vehicles[j]=vehicles[j+1];
                vehicles[j+1]=temp;
            }
        }
    }
    viewAllVehicles(vehicles,vehicleCount);
}
//menu of stock management
void menuOfInventoryControlAndStockManagement(Vehicles *&vehicles,int &vehicleCount) {
    int choices=0;
    do {
        cout<<"\t\t\t\t\t--------------------------------------------------------"<<endl;
        cout<<"\t\t\t\t\t|--------INVENTORY CONTROL AND STOCK MANAGEMENT--------|"<<endl;
        cout<<"\t\t\t\t\t--------------------------------------------------------"<<endl<<endl;
        cout<<"\t\t\t\t\t1-  Stock Updates."<<endl;
        cout<<"\t\t\t\t\t2-  Low Stock Vehicles."<<endl;
        cout<<"\t\t\t\t\t3-  Back."<<endl<<endl;
        cout<<"Enter your choice :  ";
        cin>>choices;
        switch(choices) {
            case 1:
                system("clear");
            stockUpdates(vehicles,vehicleCount); //update stock of vehicle
            break;
            case 2:
                system("clear");
            lowStockVehicles(vehicles,vehicleCount); //show the low stock vehicle
            break;
            case 3:
                system("clear");
            cout<<"Back"<<endl;
            break;
            default:
                system("clear");
            cout<<"\t\t\t\t\tInvalid Choice!!!!!"<<endl;
        }
    }while(choices!=3);
}
//update stock
void stockUpdates(Vehicles *&vehicles,const int &vehicleCount) {
    cout<<"\t\t\t\t\t------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------UPDATE STOCK--------|"<<endl;
    cout<<"\t\t\t\t\t------------------------------"<<endl<<endl;
    cout<<"Enter Vehicle ID to update : ";
    int id;
    cin>>id;
    int index=findVehicleIndex(vehicles, vehicleCount, id); //check id exsist and find index
    if(index==-1) { 
        cout<<"Vehicle not found."<<endl;
        return; //exit if index not found
    }
    cout<<"Current Stock : "<<vehicles[index].stock<<endl;
    cout<<"Enter New Stock : ";
    cin>>vehicles[index].stock;
    cout<<"Updated Stock data Successfully"<<endl;
    openFileAndWriteVehiclesToFile(vehicles, vehicleCount); //write updated data in file
}
void lowStockVehicles(Vehicles *vehicles,const int &vehicleCount) {
    static int i=0;  //Static variable help to change index
    static bool found=false;
    if (i>=vehicleCount) { //if index reach to count than exit
        if(!found) { //if no vehicles found
            cout<<"No vehicles found."<<endl;
        }
        i=0; found=false; //Reset the static variable for future calls
        return; //exit function
    }
    if (i==0) { //display only one time
        cout<<"\t\t\t\t\t------------------------------------"<<endl;
        cout<<"\t\t\t\t\t|--------LOW STOCK VEHICLES--------|"<<endl;
        cout<<"\t\t\t\t\t------------------------------------"<<endl<<endl;
    }
    if (vehicles[i].stock<5) { //Check if the current vehicle has stock less than 5
        outputOfVehiclesFromArray(vehicles, i);  //Show the data of the vehicle with low stock
        found=true;
        cout<<"---------------------------------------------"<<endl;
    }
    i++; //Increment index and call the function recursively
    lowStockVehicles(vehicles, vehicleCount);
}
void salesInventoryAnalysis(Vehicles *vehicles,const int &vehicleCount) {
    double totalValue=0;
    int totalStock=0;
    for (int i=0;i<vehicleCount;i++) {
        totalValue += vehicles[i].price * vehicles[i].stock; //store all vehicle price of stock
        totalStock += vehicles[i].stock; //store all stock
    }
    cout<<"\t\t\t\t\t------------------------------------------"<<endl;
    cout<<"\t\t\t\t\t|--------SALES-INVENTORY ANALYSIS--------|"<<endl;
    cout<<"\t\t\t\t\t------------------------------------------"<<endl;
    cout<<"Total Vehicles in Stock: "<<totalStock<<endl;
    cout<<"Total Inventory Value: $"<<totalValue<<endl;
}
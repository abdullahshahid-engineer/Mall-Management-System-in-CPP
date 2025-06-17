//
// Created by dell on 11/1/2024.
//

#ifndef PRODUCTANDINVENTORYMANAGEMENT_H
#define PRODUCTANDINVENTORYMANAGEMENT_H
#include<iostream>
using namespace std;
struct Vehicles {
    int id;
    string name;
    string model;
    string category;
    string company;
    string color;
    double fuelConsumption;
    int horsePower;
    double price;
    int stock;
};
void menuOfProductAndInventoryManagement(Vehicles *&vehicles,int &vehicleCount);
void menuOfProductManager(Vehicles *&vehicles,int &vehicleCount);
void menuOfInventoryControlAndStockManagement(Vehicles *&vehicles,int &vehicleCount);
void makingNewArray(Vehicles *&vehicles,int &vehicleCount);
void addVehicles(Vehicles *&vehicles,int &vehicleCount);
void getInputVehicles(Vehicles *&vehicles,int index);
void writeVehiclesToFile(ofstream &vehilesDataFile,Vehicles *vehicles,int vehicleCount);
void openFileAndWriteVehiclesToFile(Vehicles *vehicles,int vehicleCount);
void lineCountFromFile(ifstream &vehiclesDataFile,int &vehicleCount);
void getDataFromFile(ifstream &vehiclesDataFile,Vehicles *&vehicles,int &vehicleCount);
int findVehicleIndex(Vehicles *&vehicles,int vehicleCount,int id);
void deleteVehicle(Vehicles *&vehicles, int &vehicleCount);
void outputOfVehiclesFromArray(Vehicles *vehicles,const int &index);
void viewAllVehicles(Vehicles *vehicles,const int &vehicleCount);
void backupVehicles(Vehicles *&vehicles,int &vehicleCount);
void updateVehicles(Vehicles *&vehicles,const int &vehicleCount);
void menuOfDisplayVehiclesByFilters(Vehicles *vehicles,const int &vehicleCount);
void applyFiltersOnPrice(Vehicles *vehicles,const int &vehicleCount);
void applyFiltersOnFuelConsumption(Vehicles *vehicles,const int &vehicleCount);
void applyFiltersOnHorsePower(Vehicles *vehicles,const int &vehicleCount);
void applyCombinedFilters(Vehicles *vehicles, const int &vehicleCount);
void sortVehiclesByPrice(Vehicles *vehicles,const int &vehicleCount);
void stockUpdates(Vehicles *&vehicles,const int &vehicleCount);
void lowStockVehicles(Vehicles *vehicles,const int &vehicleCount);
void salesInventoryAnalysis(Vehicles *vehicles,const int &vehicleCount);
#endif //PRODUCTANDINVENTORYMANAGEMENT_H

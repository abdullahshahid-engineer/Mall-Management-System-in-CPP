
#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class Vehicle {
private:
    string licensePlate;
    string vehicleType;

public:
    Vehicle(const string& plate = "", const string& type = "Car");

    string getLicensePlate() const;
    string getVehicleType() const;

    void setLicensePlate(const string& plate);
    void setVehicleType(const string& type);

    void displayInfo() const;

    // Operator overloading
    bool operator==(const Vehicle& other) const;

    json toJSON() const;

    void fromJSON(const json& j);
};



#endif //VEHICLE_H

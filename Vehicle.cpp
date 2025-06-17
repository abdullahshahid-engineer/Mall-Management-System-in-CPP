
#include "Vehicle.h"
Vehicle::Vehicle(const string& plate, const string& type )
        : licensePlate(plate), vehicleType(type) {}

string Vehicle::getLicensePlate() const { return licensePlate; }
string Vehicle::getVehicleType() const { return vehicleType; }

void Vehicle::setLicensePlate(const string& plate) { licensePlate = plate; }
void Vehicle::setVehicleType(const string& type) { vehicleType = type; }

void Vehicle::displayInfo() const {
    cout << "License Plate: " << licensePlate << endl;
    cout << "Vehicle Type: " << vehicleType << endl;
}

// Operator overloading
bool Vehicle::operator==(const Vehicle& other) const {
    return licensePlate == other.licensePlate;
}

json Vehicle::toJSON() const {
    json j;
    j["licensePlate"] = licensePlate;
    j["vehicleType"] = vehicleType;
    return j;
}

void Vehicle::fromJSON(const json& j) {
    licensePlate = j["licensePlate"];
    vehicleType = j["vehicleType"];
}
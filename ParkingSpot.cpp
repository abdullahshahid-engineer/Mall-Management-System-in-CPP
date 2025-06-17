
#include "ParkingSpot.h"
ParkingSpot::ParkingSpot(int id, bool occupied, const string& loc )
        : spotId(id), isOccupied(occupied), location(loc) {}

ParkingSpot::~ParkingSpot() {}

int ParkingSpot::getSpotId() const { return spotId; }
bool ParkingSpot::getIsOccupied() const { return isOccupied; }
string ParkingSpot::getLocation() const { return location; }

void ParkingSpot::setSpotId(int id) { spotId = id; }
void ParkingSpot::setIsOccupied(bool occupied) { isOccupied = occupied; }
void ParkingSpot::setLocation(const string& loc) { location = loc; }


double ParkingSpot::getRate() const { return 2.0; } // Default hourly rate

void ParkingSpot::displayInfo() const {
    cout << "Parking Spot ID: " << spotId << endl;
    cout << "Location: " << location << endl;
    cout << "Status: " << (isOccupied ? "Occupied" : "Available") << endl;
}

// Operator overloading
bool ParkingSpot::operator==(const ParkingSpot& other) const {
    return spotId == other.spotId;
}

// For JSON serialization
json ParkingSpot::toJSON() const {
    json j;
    j["spotId"] = spotId;
    j["isOccupied"] = isOccupied;
    j["location"] = location;
    return j;
}

void ParkingSpot::fromJSON(const json& j) {
    spotId = j["spotId"];
    isOccupied = j["isOccupied"];
    location = j["location"];
}
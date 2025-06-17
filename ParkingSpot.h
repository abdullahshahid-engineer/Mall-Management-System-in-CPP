
#ifndef PARKINGSPOT_H
#define PARKINGSPOT_H
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class ParkingSpot {
protected:
    int spotId;
    bool isOccupied;
    string location;

public:
    ParkingSpot(int id = 0, bool occupied = false, const string& loc = "");

    virtual ~ParkingSpot();

    int getSpotId() const;
    bool getIsOccupied() const;
    string getLocation() const;

    void setSpotId(int id);
    void setIsOccupied(bool occupied) ;
    void setLocation(const string& loc);

    double getRate() const;

    void displayInfo() const;

    // Operator overloading
    bool operator==(const ParkingSpot& other) const;

    // For JSON serialization
    json toJSON() const;

    void fromJSON(const json& j);
};


#endif //PARKINGSPOT_H

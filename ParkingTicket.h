
#ifndef PARKINGTICKET_H
#define PARKINGTICKET_H
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
class ParkingTicket {
private:
    int ticketId;
    string entryTime;
    string exitTime;
    double amountPaid;
    int spotId;
    string licensePlate;
    bool active;

public:
    ParkingTicket(int id = 0, const string& entry = "", const string& exit = "",
                 double amount = 0.0, int spot = 0, const string& plate = "", bool isActive = true);

    int getTicketId() const;
    string getEntryTime() const;
    string getExitTime() const;
    double getAmountPaid() const;
    int getSpotId() const;
    string getLicensePlate() const;
    bool isActive() const;

    void setTicketId(int id);
    void setEntryTime(const string& time);
    void setExitTime(const string& time);
    void setAmountPaid(double amount);
    void setSpotId(int id);
    void setLicensePlate(const string& plate);
    void setActive(bool isActive);

    void displayInfo() const;

    json toJSON() const;

    void fromJSON(const json& j) ;
};



#endif //PARKINGTICKET_H

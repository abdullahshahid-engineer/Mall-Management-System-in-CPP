
#include "ParkingTicket.h"
ParkingTicket::ParkingTicket(int id , const string& entry , const string& exit ,
                 double amount, int spot, const string& plate , bool isActive)
        : ticketId(id), entryTime(entry), exitTime(exit),
          amountPaid(amount), spotId(spot), licensePlate(plate), active(isActive) {}

int ParkingTicket::getTicketId() const { return ticketId; }
string ParkingTicket::getEntryTime() const { return entryTime; }
string ParkingTicket::getExitTime() const { return exitTime; }
double ParkingTicket::getAmountPaid() const { return amountPaid; }
int ParkingTicket::getSpotId() const { return spotId; }
string ParkingTicket::getLicensePlate() const { return licensePlate; }
bool ParkingTicket::isActive() const { return active; }

void ParkingTicket::setTicketId(int id) { ticketId = id; }
void ParkingTicket::setEntryTime(const string& time) { entryTime = time; }
void ParkingTicket::setExitTime(const string& time) { exitTime = time; }
void ParkingTicket::setAmountPaid(double amount) { amountPaid = amount; }
void ParkingTicket::setSpotId(int id) { spotId = id; }
void ParkingTicket::setLicensePlate(const string& plate) { licensePlate = plate; }
void ParkingTicket::setActive(bool isActive) { active = isActive; }

void ParkingTicket::displayInfo() const {
    cout << "Ticket ID: " << ticketId << endl;
    cout << "Spot ID: " << spotId << endl;
    cout << "License Plate: " << licensePlate << endl;
    cout << "Entry Time: " << entryTime << endl;
    if (!exitTime.empty()) {
        cout << "Exit Time: " << exitTime << endl;
    }
    cout << "Amount Paid: $" << fixed << setprecision(2) << amountPaid << endl;
    cout << "Status: " << (active ? "Active" : "Closed") << endl;
}

json ParkingTicket::toJSON() const {
    json j;
    j["ticketId"] = ticketId;
    j["entryTime"] = entryTime;
    j["exitTime"] = exitTime;
    j["amountPaid"] = amountPaid;
    j["spotId"] = spotId;
    j["licensePlate"] = licensePlate;
    j["active"] = active;
    return j;
}

void ParkingTicket::fromJSON(const json& j) {
    ticketId = j["ticketId"];
    entryTime = j["entryTime"];
    exitTime = j["exitTime"];
    amountPaid = j["amountPaid"];
    spotId = j["spotId"];
    licensePlate = j["licensePlate"];
    active = j["active"];
}
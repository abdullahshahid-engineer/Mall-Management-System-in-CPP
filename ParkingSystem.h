
#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "ParkingSpot.h"
#include "ParkingTicket.h"
#include "Vehicle.h"
#include "json.hpp"
class Mall;
using namespace std;
using json = nlohmann::json;

class ParkingSystem {
private:
    vector<ParkingSpot*> parkingSpots;
    vector<Vehicle*> vehicles;
    vector<ParkingTicket*> tickets;
    Mall* mall;

    // Singleton pattern implementation
    static ParkingSystem* instance;
    ParkingSystem() {} // Private constructor

public:
    static ParkingSystem* getInstance() {
        if (!instance) {
            instance = new ParkingSystem();
        }
        return instance;
    }

    ~ParkingSystem() ;

    // Parking spot management
    void addParkingSpot(ParkingSpot* spot) ;

    ParkingSpot* findParkingSpotById(int id);

    void displayAllParkingSpots() const;

    vector<ParkingSpot*>& getParkingSpots();

    // Vehicle management
    void addVehicle(Vehicle* vehicle);

    Vehicle* findVehicleByLicensePlate(const string& plate);

    void displayAllVehicles() const;

    vector<Vehicle*>& getVehicles() ;

    // Ticket management
    void addTicket(ParkingTicket* ticket) ;

    ParkingTicket* findTicketById(int id) ;

    ParkingTicket* findActiveTicketByLicensePlate(const string& plate);

    void displayAllTickets() const ;

    vector<ParkingTicket*>& getTickets();

    // Find available parking spot of a specific type
    ParkingSpot* findAvailableSpot();

    // JSON serialization
    void saveParkingDataToFile(const string& filename);

    void loadParkingDataFromFile(const string& filename);
};


void ticketMenu(Mall* mall, ParkingSystem* system);
void vehicleMenu(Mall* mall, ParkingSystem* system);
void parkingMenu(Mall* mall);
#endif //PARKINGSYSTEM_H

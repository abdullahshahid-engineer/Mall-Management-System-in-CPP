
#include "ParkingSystem.h"
#include "Mall.h"
// Initialize static instance
ParkingSystem* ParkingSystem::instance = nullptr;


ParkingSystem::~ParkingSystem() {
    for (auto spot : parkingSpots) {
        delete spot;
    }
    for (auto vehicle : vehicles) {
        delete vehicle;
    }
    for (auto ticket : tickets) {
        delete ticket;
    }

    parkingSpots.clear();
    vehicles.clear();
    tickets.clear();
}

    // Parking spot management
void ParkingSystem::addParkingSpot(ParkingSpot* spot) {
    parkingSpots.push_back(spot);
}

ParkingSpot* ParkingSystem::findParkingSpotById(int id) {
    for (auto spot : parkingSpots) {
        if (spot->getSpotId() == id) {
            return spot;
        }
    }
    return nullptr;
}

void ParkingSystem::displayAllParkingSpots() const {
    cout << "\n=== Parking Spots List ===" << endl;
    for (const auto& spot : parkingSpots) {
        spot->displayInfo();
        cout << "--------------------" << endl;
    }
}

vector<ParkingSpot*>& ParkingSystem::getParkingSpots() {
    return parkingSpots;
}

    // Vehicle management
void ParkingSystem::addVehicle(Vehicle* vehicle) {
    vehicles.push_back(vehicle);
}

Vehicle* ParkingSystem::findVehicleByLicensePlate(const string& plate) {
    for (auto vehicle : vehicles) {
        if (vehicle->getLicensePlate() == plate) {
            return vehicle;
        }
    }
    return nullptr;
}

void ParkingSystem::displayAllVehicles() const {
    cout << "\n=== Vehicles List ===" << endl;
    for (const auto& vehicle : vehicles) {
        vehicle->displayInfo();
        cout << "--------------------" << endl;
    }
}

vector<Vehicle*>& ParkingSystem::getVehicles() {
    return vehicles;
}

    // Ticket management
void ParkingSystem::addTicket(ParkingTicket* ticket) {
    tickets.push_back(ticket);
}

ParkingTicket* ParkingSystem::findTicketById(int id) {
    for (auto ticket : tickets) {
        if (ticket->getTicketId() == id) {
            return ticket;
        }
    }
    return nullptr;
}

ParkingTicket* ParkingSystem::findActiveTicketByLicensePlate(const string& plate) {
    for (auto ticket : tickets) {
        if (ticket->getLicensePlate() == plate && ticket->isActive()) {
            return ticket;
        }
    }
    return nullptr;
}

void ParkingSystem::displayAllTickets() const {
    cout << "\n=== Parking Tickets List ===" << endl;
    for (const auto& ticket : tickets) {
        ticket->displayInfo();
        cout << "--------------------" << endl;
    }
}

vector<ParkingTicket*>& ParkingSystem::getTickets() {
    return tickets;
}

    // Find available parking spot of a specific type
ParkingSpot* ParkingSystem::findAvailableSpot() {
    for (auto spot : parkingSpots) {
        if (!spot->getIsOccupied() ) {
            return spot;
        }
    }
    return nullptr;
}

    // JSON serialization
void ParkingSystem::saveParkingDataToFile(const string& filename) {
    try {
        json j;

        j["parkingSpots"] = json::array();
        for (const auto& spot : parkingSpots) {
            j["parkingSpots"].push_back(spot->toJSON());
        }

        j["vehicles"] = json::array();
        for (const auto& vehicle : vehicles) {
            j["vehicles"].push_back(vehicle->toJSON());
        }

        j["tickets"] = json::array();
        for (const auto& ticket : tickets) {
            j["tickets"].push_back(ticket->toJSON());
        }

        ofstream file(filename);
        if (file.is_open()) {
            file << j.dump(4); // Pretty printing with 4-space indent
            file.close();
            cout << "Parking data saved to " << filename << " successfully." << endl;
        } else {
            cout << "Failed to open file for writing." << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error saving data: " << e.what() << endl;
    }
}

void ParkingSystem::loadParkingDataFromFile(const string& filename) {
    try {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File not found or couldn't be opened." << endl;
            return;
        }

        json j;
        file >> j;
        file.close();

        // Clear existing data
        for (auto spot : parkingSpots) delete spot;
        for (auto vehicle : vehicles) delete vehicle;
        for (auto ticket : tickets) delete ticket;

        parkingSpots.clear();
        vehicles.clear();
        tickets.clear();

        // Load parking spots
        for (auto& el : j["parkingSpots"]) {
            ParkingSpot* spot = nullptr;
            spot = new ParkingSpot();

            if (spot) {
                spot->fromJSON(el);
                parkingSpots.push_back(spot);
            }
        }

        // Load vehicles
        for (auto& el : j["vehicles"]) {
            Vehicle* vehicle = new Vehicle();
            vehicle->fromJSON(el);
            vehicles.push_back(vehicle);
        }

        // Load tickets
        for (auto& el : j["tickets"]) {
            ParkingTicket* ticket = new ParkingTicket();
            ticket->fromJSON(el);
            tickets.push_back(ticket);
        }

        cout << "Parking data loaded from " << filename << " successfully." << endl;
    }
    catch (const exception& e) {
        cerr << "Error loading data: " << e.what() << endl;
    }
}

void parkingSpotMenu(Mall* mall, ParkingSystem* system) {
    cout << endl << "Parking Spot Management" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. Add Parking Spot" << endl;
        cout << "2. Display All Parking Spots" << endl;
        cout << "3. Find Parking Spot by ID" << endl;
        cout << "4. Update Parking Spot Status" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                int id;
                string location;
                int type;

                cout << "Enter Parking Spot ID: ";
                cin >> id;
                if (system->findParkingSpotById(id)) {
                    cout << "Parking spot with this ID already exists." << endl;
                    break;
                }
                cin.ignore();
                cout << "Enter Location (e.g., Level 1, North): ";
                getline(cin, location);

                ParkingSpot* spot = nullptr;
                spot= new ParkingSpot(id,false,location);

                system->addParkingSpot(spot);
                cout << "Parking spot added successfully!" << endl;
                break;
            }
            case 2: {
                system->displayAllParkingSpots();
                break;
            }
            case 3: {
                int id;
                cout << "Enter Parking Spot ID: ";
                cin >> id;

                ParkingSpot* spot = system->findParkingSpotById(id);
                if (spot) {
                    spot->displayInfo();
                } else {
                    cout << "Parking spot not found." << endl;
                }
                break;
            }
            case 4: {
                int id;
                bool status;
                cout << "Enter Parking Spot ID: ";
                cin >> id;

                ParkingSpot* spot = system->findParkingSpotById(id);
                if (spot) {
                    cout << "Current Status: " << (spot->getIsOccupied() ? "Occupied" : "Available") << endl;
                    cout << "New Status (1: Occupied, 0: Available): ";
                    cin >> status;
                    spot->setIsOccupied(status);
                    cout << "Parking spot status updated successfully!" << endl;
                } else {
                    cout << "Parking spot not found." << endl;
                }
                break;
            }
            case 0: {
                cout << "Returning to Main Menu" << endl;
                break;
            }
            default:
                cout << "Invalid Choice. Please Try again!!!" << endl;
        }
    } while (option != 0);
}

void vehicleMenu(Mall* mall, ParkingSystem* system) {
    cout << endl << "Vehicle Management" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. Register Vehicle" << endl;
        cout << "2. Display All Vehicles" << endl;
        cout << "3. Find Vehicle by License Plate" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                string plate, type;

                cin.ignore();
                cout << "Enter License Plate: ";
                getline(cin, plate);

                if (system->findVehicleByLicensePlate(plate)) {
                    cout << "Vehicle with this license plate already exists." << endl;
                    break;
                }

                cout << "Enter Vehicle Type (Car, SUV, Truck, etc.): ";
                getline(cin, type);

                Vehicle* vehicle = new Vehicle(plate, type);
                system->addVehicle(vehicle);
                cout << "Vehicle registered successfully!" << endl;
                break;
            }
            case 2: {
                system->displayAllVehicles();
                break;
            }
            case 3: {
                string plate;
                cin.ignore();
                cout << "Enter License Plate: ";
                getline(cin, plate);

                Vehicle* vehicle = system->findVehicleByLicensePlate(plate);
                if (vehicle) {
                    vehicle->displayInfo();
                } else {
                    cout << "Vehicle not found." << endl;
                }
                break;
            }
            case 0: {
                cout << "Returning to Main Menu" << endl;
                break;
            }
            default:
                cout << "Invalid Choice. Please Try again!!!" << endl;
        }
    } while (option != 0);
}

void ticketMenu(Mall* mall, ParkingSystem* system) {
    cout << endl << "Parking Ticket Management" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. Issue Parking Ticket" << endl;
        cout << "2. Process Exit and Payment" << endl;
        cout << "3. Display All Tickets" << endl;
        cout << "4. Find Ticket by ID" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                int ticketId;
                string plate,  entryTime;

                cout << "Enter Ticket ID: ";
                cin >> ticketId;

                if (system->findTicketById(ticketId)) {
                    cout << "Ticket with this ID already exists." << endl;
                    break;
                }

                cin.ignore();
                cout << "Enter License Plate: ";
                getline(cin, plate);

                // Check if vehicle exists, register if not
                Vehicle* vehicle = system->findVehicleByLicensePlate(plate);
                if (!vehicle) {
                    string type;
                    cout << "Vehicle not registered. Enter Vehicle Type (Car, SUV, Truck, etc.): ";
                    getline(cin, type);
                    vehicle = new Vehicle(plate, type);
                    system->addVehicle(vehicle);
                    cout << "Vehicle registered." << endl;
                }

                // Check if vehicle already has active ticket
                if (system->findActiveTicketByLicensePlate(plate)) {
                    cout << "This vehicle already has an active parking ticket." << endl;
                    break;
                }

                int spotId;
                cout << "Enter Parking Spot ID to assign: ";
                cin >> spotId;

                ParkingSpot* spot = system->findParkingSpotById(spotId);
                if (!spot) {
                    cout << "Parking spot not found." << endl;
                    break;
                }

                if (spot->getIsOccupied()) {
                    cout << "Parking spot is currently occupied. Please choose another." << endl;
                    break;
                }
                cin.ignore();
                cout << "Enter Entry Time (YYYY-MM-DD HH:MM): ";
                getline(cin, entryTime);

                // Mark spot as occupied
                spot->setIsOccupied(true);

                // Create ticket
                ParkingTicket* ticket = new ParkingTicket(ticketId, entryTime, "", 0.0, spot->getSpotId(), plate);
                system->addTicket(ticket);

                cout << "Parking ticket issued successfully!" << endl;
                cout << "Assigned to Spot #" << spot->getSpotId() << " (" << spot->getLocation() << ")" << endl;
                break;
            }
            case 2: {
                int ticketId;
                string exitTime;
                double hoursParked;

                cout << "Enter Ticket ID: ";
                cin >> ticketId;

                ParkingTicket* ticket = system->findTicketById(ticketId);
                if (!ticket || !ticket->isActive()) {
                    cout << "Ticket not found or already processed." << endl;
                    break;
                }

                cin.ignore();
                cout << "Enter Exit Time (YYYY-MM-DD HH:MM): ";
                getline(cin, exitTime);

                cout << "Enter Hours Parked: ";
                cin >> hoursParked;

                // Find the spot to calculate rate
                ParkingSpot* spot = system->findParkingSpotById(ticket->getSpotId());
                if (!spot) {
                    cout << "Error: Spot not found." << endl;
                    break;
                }

                // Calculate amount
                double rate = spot->getRate();
                double amount = rate * hoursParked;

                // Update ticket
                ticket->setExitTime(exitTime);
                ticket->setAmountPaid(amount);
                ticket->setActive(false);

                // Mark spot as available
                spot->setIsOccupied(false);

                cout << "Payment processed successfully!" << endl;
                cout << "Amount charged: $" << fixed << setprecision(2) << amount << endl;
                break;
            }
            case 3: {
                system->displayAllTickets();
                break;
            }
            case 4: {
                int id;
                cout << "Enter Ticket ID: ";
                cin >> id;

                ParkingTicket* ticket = system->findTicketById(id);
                if (ticket) {
                    ticket->displayInfo();
                } else {
                    cout << "Ticket not found." << endl;
                }
                break;
            }
            case 0: {
                cout << "Returning to Main Menu" << endl;
                break;
            }
            default:
                cout << "Invalid Choice. Please Try again!!!" << endl;
        }
    } while (option != 0);
}
void parkingMenu(Mall* mall) {
    ParkingSystem* system = ParkingSystem::getInstance();

    cout << "Welcome to Parking Management System!" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. Parking Spot Management" << endl;
        cout << "2. Vehicle Management" << endl;
        cout << "3. Ticket Management" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                parkingSpotMenu(mall, system);
                break;
            }
            case 2: {
                vehicleMenu(mall, system);
                break;
            }
            case 3: {
                ticketMenu(mall, system);
                break;
            }
            case 0: {
                cout << "Returning to Main Menu" << endl;
                break;
            }
            default:
                cout << "Invalid Choice. Please Try again!!!" << endl;
        }
    } while (option != 0);
}

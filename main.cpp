//
// Created by dell on 4/17/2025.
//
#include "Mall.h"
#include "CustomerSalesSystem.h"
#include "EventManager.h"
#include "OnlineBookingSystem.h"
#include "ParkingSystem.h"
#include "AdvertisementSystem.h"
int main() {

    Mall *mall=Mall::getInstance();
    ParkingSystem* parkingSystem = ParkingSystem::getInstance();
    AdvertisementSystem* advertisementSystem = AdvertisementSystem::getInstance();
    CustomerSalesSystem* system = CustomerSalesSystem::getInstance();
    EventManager* eventManager = EventManager::getInstance();
    OnlineBookingSystem* bookingSystem = OnlineBookingSystem::getInstance();
    mall->initialize("ITU","Nishtar Town");
    mall->loadStoreDataFromFile("Mall_Store_Data.json");
    mall->loadEmployeeData("Employee_Data.json");
    system->loadCustomerDataFromFile("CustomerSalesSystem.json");
    eventManager->loadEventsFromFile("EventManager.json");
    bookingSystem->loadBookingsFromFile("OnlineBookingSystem.json");
    parkingSystem->loadParkingDataFromFile("ParkingSystem.json");
    advertisementSystem->loadAdvertisementDataFromFile("AdvertisementSystem.json");
    mainMenu(mall);
    mall->saveStoreDataToFile("Mall_Store_Data.json");
    mall->saveEmployeeData("Employee_Data.json");
    system->saveCustomerDataToFile("CustomerSalesSystem.json");
    eventManager->saveEventsToFile("EventManager.json");
    bookingSystem->saveBookingsToFile("OnlineBookingSystem.json");
    parkingSystem->saveParkingDataToFile("ParkingSystem.json");
    advertisementSystem->saveAdvertisementDataToFile("AdvertisementSystem.json");
    return 0;
}
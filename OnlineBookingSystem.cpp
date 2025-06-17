

#include "OnlineBookingSystem.h"
#include "Mall.h"
// Initialize static instance
OnlineBookingSystem* OnlineBookingSystem::instance = nullptr;
void bookingManagementMenu() {
    OnlineBookingSystem* bookingSystem = OnlineBookingSystem::getInstance();
    EventManager* eventManager = EventManager::getInstance();
    int choice;

    do {
        cout << "\n===== BOOKING MANAGEMENT MENU =====" << endl;
        cout << "1. Create New Booking" << endl;
        cout << "2. Cancel Booking" << endl;
        cout << "3. Process Payment" << endl;
        cout << "4. Display All Bookings" << endl;
        cout << "5. Display Customer Bookings" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Create new booking
                int customerId, eventId, numTickets;
                CustomerSalesSystem* system = CustomerSalesSystem::getInstance();
                cout << "\nEnter Customer ID: ";
                cin >> customerId;
                Customer* customer = system->findCustomerById(customerId);
                if(!customer) {
                    cout << "Customer not found" << endl;
                    break;
                }

                // Display available events
                eventManager->displayAllEvents();

                cout << "Enter Event ID: ";
                cin >> eventId;

                // Check if event exists
                Event* event = eventManager->getEventById(eventId);
                if (!event) {
                    cout << "Event not found." << endl;
                    break;
                }

                cout << "Enter Number of Tickets: ";
                cin >> numTickets;

                string currentDate = getCurrentDate();
                bookingSystem->createBooking(customerId, eventId, numTickets, currentDate);
                break;
            }
            case 2: {
                // Cancel booking
                int bookingId;
                cout << "\nEnter Booking ID to cancel: ";
                cin >> bookingId;

                bookingSystem->cancelBooking(bookingId);
                break;
            }
            case 3: {
                // Process payment
                int bookingId;
                cout << "\nEnter Booking ID to process payment: ";
                cin >> bookingId;

                bookingSystem->processPayment(bookingId);
                break;
            }
            case 4:
                // Display all bookings
                    bookingSystem->displayAllBookings();
            break;
            case 5: {
                // Display customer bookings
                int customerId;
                cout << "\nEnter Customer ID: ";
                cin >> customerId;

                bookingSystem->displayCustomerBookings(customerId);
                break;
            }
            case 0:
                cout << "Returning to main menu..." << endl;
            break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void eventAndBookingMenu(Mall* mall) {
    EventManager* eventManager = EventManager::getInstance();
    OnlineBookingSystem* bookingSystem = OnlineBookingSystem::getInstance();
    int choice;

    do {
        cout << "\n===== ENTERTAINMENT & BOOKING SYSTEM =====" << endl;
        cout << "1. Event Management" << endl;
        cout << "2. Online Booking Management" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                eventManagementMenu();
            break;
            case 2:
                bookingManagementMenu();
            break;
            case 0:
                cout << "Returning to main menu..." << endl;
            break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

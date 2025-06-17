
#include "AdvertisementSystem.h"
#include "Mall.h"
// Initialize static instance
AdvertisementSystem* AdvertisementSystem::instance = nullptr;
AdvertisementSystem::~AdvertisementSystem() {
    for (auto ad : advertisements) {
        delete ad;
    }
    for (auto advertiser : advertisers) {
        delete advertiser;
    }

    advertisements.clear();
    advertisers.clear();
}

    // Advertisement management
void AdvertisementSystem::addAdvertisement(Advertisement* ad) {
    advertisements.push_back(ad);
}

Advertisement* AdvertisementSystem::findAdvertisementById(int id) {
    for (auto ad : advertisements) {
        if (ad->getAdId() == id) {
            return ad;
        }
    }
    return nullptr;
}

void AdvertisementSystem::displayAllAdvertisements() const {
    cout << "\n=== Advertisement List ===" << endl;
    for (const auto& ad : advertisements) {
        ad->displayInfo();
        cout << "--------------------" << endl;
    }
}

vector<Advertisement*>& AdvertisementSystem::getAdvertisements() {
    return advertisements;
}

    // Advertiser management
void AdvertisementSystem::addAdvertiser(Advertiser* advertiser) {
    advertisers.push_back(advertiser);
}

Advertiser* AdvertisementSystem::findAdvertiserById(int id) {
    for (auto advertiser : advertisers) {
        if (advertiser->getAdvertiserId() == id) {
            return advertiser;
        }
    }
    return nullptr;
}

void AdvertisementSystem::displayAllAdvertisers() const {
    cout << "\n=== Advertiser List ===" << endl;
    for (const auto& advertiser : advertisers) {
        advertiser->displayInfo();
        cout << "--------------------" << endl;
    }
}

vector<Advertiser*>& AdvertisementSystem::getAdvertisers() {
    return advertisers;
}

    // JSON serialization
void AdvertisementSystem::saveAdvertisementDataToFile(const string& filename) {
    try {
        json j;

        j["advertisements"] = json::array();
        for (const auto& ad : advertisements) {
            j["advertisements"].push_back(ad->toJSON());
        }

        j["advertisers"] = json::array();
        for (const auto& advertiser : advertisers) {
            j["advertisers"].push_back(advertiser->toJSON());
        }

        ofstream file(filename);
        if (file.is_open()) {
            file << j.dump(4); // Pretty printing with 4-space indent
            file.close();
            cout << "Advertisement data saved to " << filename << " successfully." << endl;
        } else {
            cout << "Failed to open file for writing." << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error saving data: " << e.what() << endl;
    }
}

void AdvertisementSystem::loadAdvertisementDataFromFile(const string& filename) {
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
        for (auto ad : advertisements) delete ad;
        for (auto advertiser : advertisers) delete advertiser;

        advertisements.clear();
        advertisers.clear();

        // Load advertisers first
        for (auto& el : j["advertisers"]) {
            Advertiser* advertiser = new Advertiser();
            advertiser->fromJSON(el);
            advertisers.push_back(advertiser);
        }

        // Load advertisements
        for (auto& el : j["advertisements"]) {
            Advertisement* ad = nullptr;
            string type = el["type"];

            if (type == "Digital") {
                ad = new DigitalAd();
            } else if (type == "Print") {
                ad = new PrintAd();
            } else {
                ad = new Advertisement();
            }

            if (ad) {
                ad->fromJSON(el);
                advertisements.push_back(ad);
            }
        }

        cout << "Advertisement data loaded from " << filename << " successfully." << endl;
    }
    catch (const exception& e) {
        cerr << "Error loading data: " << e.what() << endl;
    }
}
void advertiserMenu(Mall* mall, AdvertisementSystem* system) {
    cout << endl << "Advertiser Management" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. Add Advertiser" << endl;
        cout << "2. Display All Advertisers" << endl;
        cout << "3. Find Advertiser by ID" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                int id;
                string name, contactPerson, email, phone;

                cout << "Enter Advertiser ID: ";
                cin >> id;
                if (system->findAdvertiserById(id)) {
                    cout << "Advertiser with this ID already exists." << endl;
                    break;
                }
                cin.ignore();
                cout << "Enter Company Name: ";
                getline(cin, name);
                cout << "Enter Contact Person: ";
                getline(cin, contactPerson);
                cout << "Enter Email: ";
                getline(cin, email);
                cout << "Enter Phone: ";
                getline(cin, phone);

                Advertiser* advertiser = new Advertiser(id, name, contactPerson, email, phone);
                system->addAdvertiser(advertiser);
                cout << "Advertiser added successfully!" << endl;
                break;
            }
            case 2: {
                system->displayAllAdvertisers();
                break;
            }
            case 3: {
                int id;
                cout << "Enter Advertiser ID: ";
                cin >> id;

                Advertiser* advertiser = system->findAdvertiserById(id);
                if (advertiser) {
                    advertiser->displayInfo();
                } else {
                    cout << "Advertiser not found." << endl;
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

void advertisementMenu(Mall* mall, AdvertisementSystem* system) {
    cout << endl << "Advertisement Management" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. Create Advertisement" << endl;
        cout << "2. Display All Advertisements" << endl;
        cout << "3. Find Advertisement by ID" << endl;
        cout << "4. Update Advertisement Status" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                int id, type;
                string title, description, startDate, endDate;
                double costPerDay;

                cout << "Enter Advertisement ID: ";
                cin >> id;
                if (system->findAdvertisementById(id)) {
                    cout << "Advertisement with this ID already exists." << endl;
                    break;
                }
                cin.ignore();
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter Description: ";
                getline(cin, description);
                cout << "Enter Cost Per Day: $";
                cin >> costPerDay;
                cin.ignore();
                cout << "Enter Start Date (YYYY-MM-DD): ";
                getline(cin, startDate);
                cout << "Enter End Date (YYYY-MM-DD): ";
                getline(cin, endDate);

                cout << "Advertisement Type (1: Digital, 2: Print): ";
                cin >> type;

                Advertisement* ad = nullptr;
                if (type == 1) {
                    string screenLocation;
                    int duration;
                    cin.ignore();
                    cout << "Enter Screen Location: ";
                    getline(cin, screenLocation);
                    cout << "Enter Duration in Seconds: ";
                    cin >> duration;
                    ad = new DigitalAd(id, title, description, costPerDay, startDate, endDate, true, screenLocation, duration);
                } else if (type == 2) {
                    string location, size;
                    cin.ignore();
                    cout << "Enter Location: ";
                    getline(cin, location);
                    cout << "Enter Size (e.g., A4, Billboard): ";
                    getline(cin, size);
                    ad = new PrintAd(id, title, description, costPerDay, startDate, endDate, true, location, size);
                } else {
                    cout << "Invalid advertisement type selected." << endl;
                    continue;
                }
                system->addAdvertisement(ad);
                cout << "Advertisement created successfully!" << endl;
                break;
            }
            case 2: {
                system->displayAllAdvertisements();
                break;
            }
            case 3: {
                int id;
                cout << "Enter Advertisement ID: ";
                cin >> id;
                Advertisement* ad = system->findAdvertisementById(id);
                if (ad) {
                    ad->displayInfo();
                } else {
                    cout << "Advertisement not found." << endl;
                }
                break;
            }
            case 4: {
                int id;
                bool status;
                cout << "Enter Advertisement ID: ";
                cin >> id;

                Advertisement* ad = system->findAdvertisementById(id);
                if (ad) {
                    cout << "Current Status: " << (ad->getIsActive() ? "Active" : "Inactive") << endl;
                    cout << "New Status (1: Active, 0: Inactive): ";
                    cin >> status;
                    ad->setIsActive(status);
                    cout << "Advertisement status updated successfully!" << endl;
                } else {
                    cout << "Advertisement not found." << endl;
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

void adStatsMenu(Mall* mall, AdvertisementSystem* system) {
    cout << endl << "Advertisement Statistics and Reports" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. View Overall Advertisement Statistics" << endl;
        cout << "2. Calculate Daily Revenue" << endl;
        cout << "3. Count Active Advertisements" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                AdvertisementStats<double>* stats = AdvertisementStats<double>::getInstance(
                    &system->getAdvertisements(), &system->getAdvertisers());
                stats->displayStatistics();
                break;
            }
            case 2: {
                AdvertisementStats<double>* stats = AdvertisementStats<double>::getInstance(
                    &system->getAdvertisements(), &system->getAdvertisers());
                double revenue = stats->calculateAverageRevenue();
                cout << "Daily Revenue from Advertisements: $" << fixed << setprecision(2) << revenue << endl;
                break;
            }
            case 3: {
                AdvertisementStats<double>* stats = AdvertisementStats<double>::getInstance(
                    &system->getAdvertisements(), &system->getAdvertisers());
                stats->countActiveAds();
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

void advertisementSystemMenu(Mall* mall) {
    AdvertisementSystem* system = AdvertisementSystem::getInstance();

    cout << "Welcome to Advertisement Management System!" << endl;
    int option;
    do {
        cout << endl << "=======================================" << endl;
        cout << "1. Advertiser Management" << endl;
        cout << "2. Advertisement Management" << endl;
        cout << "3. Statistics and Reports" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                advertiserMenu(mall, system);
                break;
            }
            case 2: {
                advertisementMenu(mall, system);
                break;
            }
            case 3: {
                adStatsMenu(mall, system);
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

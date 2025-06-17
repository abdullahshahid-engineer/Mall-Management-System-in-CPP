
#ifndef ADVERTISEMENTSYSTEM_H
#define ADVERTISEMENTSYSTEM_H
#include <string>
#include <iostream>
#include <fstream>
#include "Advertisement.h"
#include "Advertiser.h"
#include "DigitalAd.h"
#include "PrintAd.h"
#include <iomanip>
#include "AdvertisementStats.h"
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
class Mall;

class AdvertisementSystem {
private:
    vector<Advertisement*> advertisements;
    vector<Advertiser*> advertisers;
    Mall* mall;
    // Singleton pattern implementation
    static AdvertisementSystem* instance;
    AdvertisementSystem() {} // Private constructor

public:
    static AdvertisementSystem* getInstance() {
        if (!instance) {
            instance = new AdvertisementSystem();
        }
        return instance;
    }

    ~AdvertisementSystem() ;

    // Advertisement management
    void addAdvertisement(Advertisement* ad);

    Advertisement* findAdvertisementById(int id);

    void displayAllAdvertisements() const;

    vector<Advertisement*>& getAdvertisements();

    // Advertiser management
    void addAdvertiser(Advertiser* advertiser);

    Advertiser* findAdvertiserById(int id);

    void displayAllAdvertisers() const;

    vector<Advertiser*>& getAdvertisers();

    // JSON serialization
    void saveAdvertisementDataToFile(const string& filename);

    void loadAdvertisementDataFromFile(const string& filename);
};

void advertiserMenu(Mall* mall, AdvertisementSystem* system);
void advertisementMenu(Mall* mall, AdvertisementSystem* system);
void adStatsMenu(Mall* mall, AdvertisementSystem* system);
void advertisementSystemMenu(Mall* mall);




#endif //ADVERTISEMENTSYSTEM_H

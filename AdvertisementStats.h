
#ifndef ADVERTISEMENTSTATS_H
#define ADVERTISEMENTSTATS_H
#include <string>
#include <iostream>
#include <fstream>
#include "Advertisement.h"
#include "Advertiser.h"
#include <iomanip>
using namespace std;


template<typename T>
class AdvertisementStats {
private:
    vector<Advertisement*>* ads;
    vector<Advertiser*>* advertisers;

    // Singleton pattern implementation
    static AdvertisementStats<T>* instance;

    AdvertisementStats(vector<Advertisement*>* a = nullptr, vector<Advertiser*>* adv = nullptr) : ads(a), advertisers(adv) {}

public:
    static AdvertisementStats<T>* getInstance(vector<Advertisement*>* a = nullptr, vector<Advertiser*>* adv = nullptr) {
        if (!instance) {
            instance = new AdvertisementStats<T>(a, adv);
        }
        return instance;
    }

    void setData(vector<Advertisement*>* a, vector<Advertiser*>* adv) {
        ads = a;
        advertisers = adv;
    }

    T calculateAverageRevenue() {
        if (!ads || ads->empty()) return 0;

        T totalRevenue = 0;
        for (const auto& ad : *ads) {
            totalRevenue += ad->getCostPerDay();
        }

        return totalRevenue;
    }

    void displayStatistics() {
        cout << "\n=== Advertisement Statistics ===" << endl;
        cout << "Total Advertisements: " << (ads ? ads->size() : 0) << endl;
        cout << "Daily Revenue from Ads: $" << fixed << setprecision(2) << calculateAverageRevenue() << endl;
        cout << "Total Advertisers: " << (advertisers ? advertisers->size() : 0) << endl;

        // Count by type
        int digitalCount = 0, printCount = 0, eventCount = 0, otherCount = 0;
        if (ads) {
            for (const auto& ad : *ads) {
                string type = ad->getAdType();
                if (type == "Digital") digitalCount++;
                else if (type == "Print") printCount++;
                else if (type == "Event") eventCount++;
                else otherCount++;
            }
        }

        cout << "Digital Ads: " << digitalCount << endl;
        cout << "Print Ads: " << printCount << endl;
        cout << "Event Ads: " << eventCount << endl;
        cout << "Other Ads: " << otherCount << endl;
    }

    int countActiveAds() {
        if (!ads) return 0;

        int active = 0;
        for (const auto& ad : *ads) {
            if (ad->getIsActive()) active++;
        }

        cout << "Active Advertisements: " << active << endl;
        return active;
    }
};

// Initialize static instance
template<typename T>
AdvertisementStats<T>* AdvertisementStats<T>::instance = nullptr;



#endif //ADVERTISEMENTSTATS_H

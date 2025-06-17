
#ifndef DIGITALAD_H
#define DIGITALAD_H
#include <string>
#include <iostream>
#include <fstream>
#include "Advertisement.h"
#include <iomanip>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;


class DigitalAd : public Advertisement {
private:
    string screenLocation;
    int durationInSeconds;

public:
    DigitalAd(int id = 0, const string& t = "", const string& desc = "",
             double cost = 0.0, const string& start = "", const string& end = "",
             bool active = true, const string& loc = "", int duration = 30);

    string getScreenLocation() const ;
    int getDurationInSeconds() const;

    void setScreenLocation(const string& loc);
    void setDurationInSeconds(int duration);

    string getAdType() const override;

    void displayInfo() const override;

    json toJSON() const override;

    void fromJSON(const json& j) override;
};



#endif //DIGITALAD_H

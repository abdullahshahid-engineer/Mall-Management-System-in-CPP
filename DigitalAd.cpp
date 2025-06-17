
#include "DigitalAd.h"
DigitalAd::DigitalAd(int id , const string& t , const string& desc ,
             double cost , const string& start , const string& end ,
             bool active , const string& loc, int duration )
        : Advertisement(id, t, desc, cost, start, end, active),
          screenLocation(loc), durationInSeconds(duration) {}

string DigitalAd::getScreenLocation() const { return screenLocation; }
int DigitalAd::getDurationInSeconds() const { return durationInSeconds; }

void DigitalAd::setScreenLocation(const string& loc) { screenLocation = loc; }
void DigitalAd::setDurationInSeconds(int duration) { durationInSeconds = duration; }

string DigitalAd::getAdType() const  { return "Digital"; }

void DigitalAd::displayInfo() const  {
    Advertisement::displayInfo();
    cout << "Ad Type: Digital" << endl;
    cout << "Screen Location: " << screenLocation << endl;
    cout << "Duration: " << durationInSeconds << " seconds" << endl;
}

json DigitalAd::toJSON() const  {
    json j = Advertisement::toJSON();
    j["screenLocation"] = screenLocation;
    j["durationInSeconds"] = durationInSeconds;
    return j;
}

void DigitalAd::fromJSON(const json& j)  {
    Advertisement::fromJSON(j);
    screenLocation = j["screenLocation"];
    durationInSeconds = j["durationInSeconds"];
}
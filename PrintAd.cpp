
#include "PrintAd.h"
string PrintAd::getLocation() const { return location; }
string PrintAd::getSize() const { return size; }

void PrintAd::setLocation(const string& loc) { location = loc; }
void PrintAd::setSize(const string& sz) { size = sz; }

string PrintAd::getAdType() const  { return "Print"; }

void PrintAd::displayInfo() const {
    Advertisement::displayInfo();
    cout << "Ad Type: Print" << endl;
    cout << "Location: " << location << endl;
    cout << "Size: " << size << endl;
}

json PrintAd::toJSON() const {
    json j = Advertisement::toJSON();
    j["location"] = location;
    j["size"] = size;
    return j;
}

void PrintAd::fromJSON(const json& j) {
    Advertisement::fromJSON(j);
    location = j["location"];
    size = j["size"];
}
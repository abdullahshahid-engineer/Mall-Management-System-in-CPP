
#ifndef PRINTAD_H
#define PRINTAD_H

#include <string>
#include <iostream>
#include <fstream>
#include "Advertisement.h"
#include <iomanip>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class PrintAd : public Advertisement {
private:
    string location;
    string size;

public:
    PrintAd(int id = 0, const string& t = "", const string& desc = "",
           double cost = 0.0, const string& start = "", const string& end = "",
           bool active = true, const string& loc = "", const string& sz = "")
        : Advertisement(id, t, desc, cost, start, end, active),
          location(loc), size(sz) {}

    string getLocation() const;
    string getSize() const;

    void setLocation(const string& loc);
    void setSize(const string& sz);

    string getAdType() const override;

    void displayInfo() const override;

    json toJSON() const override ;

    void fromJSON(const json& j) override;
};



#endif //PRINTAD_H

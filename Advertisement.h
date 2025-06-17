
#ifndef ADVERTISEMENT_H
#define ADVERTISEMENT_H
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
class Advertisement {
protected:
    int adId;
    string title;
    string description;
    double costPerDay;
    string startDate;
    string endDate;
    bool isActive;

public:
    Advertisement(int id = 0, const string& t = "", const string& desc = "",
                 double cost = 0.0, const string& start = "", const string& end = "", bool active = true);

    virtual ~Advertisement();

    int getAdId() const;
    string getTitle() const;
    string getDescription() const;
    double getCostPerDay() const;
    string getStartDate() const;
    string getEndDate() const;
    bool getIsActive() const;

    void setAdId(int id);
    void setTitle(const string& t);
    void setDescription(const string& desc);
    void setCostPerDay(double cost);
    void setStartDate(const string& date);
    void setEndDate(const string& date);
    void setIsActive(bool active);

    virtual string getAdType() const ;

    virtual void displayInfo() const;

    // Operator overloading
    bool operator==(const Advertisement& other) const;

    // For JSON serialization
    virtual json toJSON() const;

    virtual void fromJSON(const json& j);
};






#endif //ADVERTISEMENT_H

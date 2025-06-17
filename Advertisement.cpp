#include "Advertisement.h"
Advertisement::Advertisement(int id, const string& t , const string& desc ,
                 double cost , const string& start , const string& end , bool active)
        : adId(id), title(t), description(desc), costPerDay(cost),
          startDate(start), endDate(end), isActive(active) {}

Advertisement::~Advertisement() {}

int Advertisement::getAdId() const { return adId; }
string Advertisement::getTitle() const { return title; }
string Advertisement::getDescription() const { return description; }
double Advertisement::getCostPerDay() const { return costPerDay; }
string Advertisement::getStartDate() const { return startDate; }
string Advertisement::getEndDate() const { return endDate; }
bool Advertisement::getIsActive() const { return isActive; }

void Advertisement::setAdId(int id) { adId = id; }
void Advertisement::setTitle(const string& t) { title = t; }
void Advertisement::setDescription(const string& desc) { description = desc; }
void Advertisement::setCostPerDay(double cost) { costPerDay = cost; }
void Advertisement::setStartDate(const string& date) { startDate = date; }
void Advertisement::setEndDate(const string& date) { endDate = date; }
void Advertisement::setIsActive(bool active) { isActive = active; }

string Advertisement::getAdType() const { return "Generic"; }

void Advertisement::displayInfo() const {
    cout << "Ad ID: " << adId << endl;
    cout << "Title: " << title << endl;
    cout << "Description: " << description << endl;
    cout << "Cost per Day: $" << fixed << setprecision(2) << costPerDay << endl;
    cout << "Start Date: " << startDate << endl;
    cout << "End Date: " << endDate << endl;
    cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
}

    // Operator overloading
bool Advertisement::operator==(const Advertisement& other) const {
    return adId == other.adId;
}

    // For JSON serialization
json Advertisement::toJSON() const {
    json j;
    j["adId"] = adId;
    j["title"] = title;
    j["description"] = description;
    j["costPerDay"] = costPerDay;
    j["startDate"] = startDate;
    j["endDate"] = endDate;
    j["isActive"] = isActive;
    j["type"] = getAdType();
    return j;
}

void Advertisement::fromJSON(const json& j) {
    adId = j["adId"];
    title = j["title"];
    description = j["description"];
    costPerDay = j["costPerDay"];
    startDate = j["startDate"];
    endDate = j["endDate"];
    isActive = j["isActive"];
}
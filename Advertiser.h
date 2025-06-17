
#ifndef ADVERTISER_H
#define ADVERTISER_H
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
class Advertiser {
private:
    int advertiserId;
    string name;
    string contactPerson;
    string email;
    string phone;

public:
    Advertiser(int id = 0, const string& n = "", const string& contact = "",
              const string& em = "", const string& ph = "");

    int getAdvertiserId() const;
    string getName() const ;
    string getContactPerson() const;
    string getEmail() const;
    string getPhone() const;

    void setAdvertiserId(int id);
    void setName(const string& n) ;
    void setContactPerson(const string& contact);
    void setEmail(const string& em);
    void setPhone(const string& ph);

    void displayInfo() const;

    // Operator overloading
    bool operator==(const Advertiser& other) const;

    json toJSON() const;

    void fromJSON(const json& j);
};






#endif //ADVERTISER_H

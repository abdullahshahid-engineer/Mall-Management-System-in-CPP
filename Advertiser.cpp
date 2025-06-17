
#include "Advertiser.h"
Advertiser::Advertiser(int id, const string& n , const string& contact ,
              const string& em , const string& ph )
        : advertiserId(id), name(n), contactPerson(contact), email(em), phone(ph) {}

int Advertiser::getAdvertiserId() const { return advertiserId; }
string Advertiser::getName() const { return name; }
string Advertiser::getContactPerson() const { return contactPerson; }
string Advertiser::getEmail() const { return email; }
string Advertiser::getPhone() const { return phone; }

void Advertiser::setAdvertiserId(int id) { advertiserId = id; }
void Advertiser::setName(const string& n) { name = n; }
void Advertiser::setContactPerson(const string& contact) { contactPerson = contact; }
void Advertiser::setEmail(const string& em) { email = em; }
void Advertiser::setPhone(const string& ph) { phone = ph; }

void Advertiser::displayInfo() const {
    cout << "Advertiser ID: " << advertiserId << endl;
    cout << "Name: " << name << endl;
    cout << "Contact Person: " << contactPerson << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
}

// Operator overloading
bool Advertiser::operator==(const Advertiser& other) const {
    return advertiserId == other.advertiserId;
}

json Advertiser::toJSON() const {
    json j;
    j["advertiserId"] = advertiserId;
    j["name"] = name;
    j["contactPerson"] = contactPerson;
    j["email"] = email;
    j["phone"] = phone;
    return j;
}

void Advertiser::fromJSON(const json& j) {
    advertiserId = j["advertiserId"];
    name = j["name"];
    contactPerson = j["contactPerson"];
    email = j["email"];
    phone = j["phone"];
}
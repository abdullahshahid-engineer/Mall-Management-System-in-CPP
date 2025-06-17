
#include "Customer.h"
Customer::Customer()
        : customerId(0), name(""), membershipStatus("Regular") {}

Customer::Customer(int id, const string& n, const string& status )
        : customerId(id), name(n), membershipStatus(status) {}

Customer::~Customer() {
    for (auto feedback : feedbacks) {
        delete feedback;
    }
    feedbacks.clear();
}
vector<Feedback*>& Customer::getFeedbacks() {
    return feedbacks;
}
int Customer::getCustomerId() const { return customerId; }
string Customer::getName() const { return name; }
string Customer::getMembershipStatus() const { return membershipStatus; }

void Customer::setCustomerId(int id) {
    customerId = id;
}
void Customer::setName(const string& n) { name = n; }
void Customer::setMembershipStatus(const string& status) { membershipStatus = status; }


void Customer::addFeedback(Feedback* feedback) {
    feedbacks.push_back(feedback);
}


void Customer::displayInfo() const {
    cout << "Customer ID: " << customerId << endl;
    cout << "Name: " << name << endl;
    cout << "Membership Status: " << membershipStatus << endl;
}

json Customer::toJSON() const {
    json j;
    j["customerId"] = customerId;
    j["name"] = name;
    j["membershipStatus"] = membershipStatus;
    j["type"] = "regular";

    j["feedbacks"] = json::array();
    for (const auto& feedback : feedbacks) {
        j["feedbacks"].push_back(feedback->toJSON());
    }
    return j;
}

void Customer::fromJSON(const json& j) {
    customerId = j["customerId"];
    name = j["name"];
    membershipStatus=j["membershipStatus"];
    if (j.contains("feedbacks") && j["feedbacks"].is_array()) {
        for (const auto& feedbackJson : j["feedbacks"]) {
            Feedback* feedback = new Feedback();
            feedback->fromJSON(feedbackJson, this);  // 'this' is the Customer*
            addFeedback(feedback);
        }
    }
}
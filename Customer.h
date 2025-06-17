

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<iostream>
#include "Feedback.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class Customer {
protected:
    int customerId;
    string name;
    string membershipStatus;
    vector<Feedback*> feedbacks;

public:
    Customer();

    Customer(int id, const string& n, const string& status = "Regular");

    virtual ~Customer();

    int getCustomerId() const;
    string getName() const;
    string getMembershipStatus() const;
    vector<Feedback*>& getFeedbacks();
    void setCustomerId(int id);
    void setName(const string& n);
    void setMembershipStatus(const string& status) ;


    void addFeedback(Feedback* feedback);


    virtual void displayInfo() const ;

    virtual json toJSON() const ;
    virtual void fromJSON(const json& j) ;
};





#endif //CUSTOMER_H

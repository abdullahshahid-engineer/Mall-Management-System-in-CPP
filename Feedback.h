

#ifndef FEEDBACK_H
#define FEEDBACK_H
#include<iostream>

#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class Customer;

class Feedback {
private:
    int feedbackId;
    Customer* customer;
    string content;

public:
    Feedback() ;
    Feedback(int id, Customer* cust, const string& cont);

    int getFeedbackId() const;
    Customer* getCustomer() const ;
    string getContent() const ;

    void setFeedbackId(int id);
    void setCustomer(Customer* cust);
    void setContent(const string& cont) ;

    void submitFeedback() ;

    json toJSON() const ;

    void fromJSON(const json& j, Customer* cust = nullptr);
};


#endif //FEEDBACK_H

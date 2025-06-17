

#include "Feedback.h"
#include "Customer.h"
Feedback::Feedback() : feedbackId(0), customer(nullptr), content("") {}
Feedback::Feedback(int id, Customer* cust, const string& cont)
    : feedbackId(id), customer(cust), content(cont) {}

int Feedback::getFeedbackId() const { return feedbackId; }
Customer* Feedback::getCustomer() const { return customer; }
string Feedback::getContent() const { return content; }

void Feedback::setFeedbackId(int id) { feedbackId = id; }
void Feedback::setCustomer(Customer* cust) { customer = cust; }
void Feedback::setContent(const string& cont) { content = cont; }

void Feedback::submitFeedback() {
    cout << "Feedback submitted by " << customer->getName() << ":" << endl;
    cout << content << endl;
    if (customer != nullptr) {
        customer->addFeedback(this);
    }
}


json Feedback::toJSON() const {
    json j;
    j["feedbackId"] = feedbackId;
    j["content"] = content;
    if (customer) {
        j["customerId"] = customer->getCustomerId();
    } else {
        j["customerId"] = -1;
    }
    return j;
}

void Feedback::fromJSON(const json& j, Customer* cust ) {
    feedbackId = j["feedbackId"];
    content = j["content"];
    customer = cust; // Customer association needs to be resolved elsewhere
}
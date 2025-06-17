

#ifndef ACCESSCONTROLLER_H
#define ACCESSCONTROLLER_H
#include "iostream"
#include "json.hpp"
#include "Employee.h"
using json = nlohmann::json;
using namespace std;


class AccessController {
public:
    AccessController();

    void grantAccess(Employee* emp) const ;

    // JSON conversion methods
    json toJSON() const;

    void fromJSON(const json& j);
};



#endif //ACCESSCONTROLLER_H

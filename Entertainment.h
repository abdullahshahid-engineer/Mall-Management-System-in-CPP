

#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H
#include <iostream>
#include "json.hpp"
#include "Event.h"
using namespace std;
using json = nlohmann::json;
class Entertainment : public Event {
private:
    string entertainmentType;  // e.g., Concert, Movie, Play, etc.
    string artist;             // Performer or artist name
    int duration;              // Duration in minutes
    string genre;              // Genre of entertainment

public:
    Entertainment();

    Entertainment(int id, const string& name, const string& desc, const string& dt,
                  const string& tm, const string& loc, double price, int cap,
                  const string& type, const string& art, int dur, const string& gen);

    // Getters
    string getEntertainmentType() const;
    string getArtist() const;
    int getDuration() const;
    string getGenre() const ;

    // Setters
    void setEntertainmentType(const string& type);
    void setArtist(const string& art);
    void setDuration(int dur);
    void setGenre(const string& gen);

    // Override display method
    void displayInfo() const override;

    // Override getEventType method
    string getEventType() const override;

    // Override JSON serialization
    json toJSON() const override;

    // Override JSON deserialization
    void fromJSON(const json& j) override;
};

#endif //ENTERTAINMENT_H



#include "Entertainment.h"
Entertainment::Entertainment()
        : Event(), entertainmentType(""), artist(""), duration(0), genre("") {}

Entertainment::Entertainment(int id, const string& name, const string& desc, const string& dt,
                  const string& tm, const string& loc, double price, int cap,
                  const string& type, const string& art, int dur, const string& gen)
        : Event(id, name, desc, dt, tm, loc, price, cap),
          entertainmentType(type), artist(art), duration(dur), genre(gen) {}

    // Getters
string Entertainment::getEntertainmentType() const { return entertainmentType; }
string Entertainment::getArtist() const { return artist; }
int Entertainment::getDuration() const { return duration; }
string Entertainment::getGenre() const { return genre; }

    // Setters
void Entertainment::setEntertainmentType(const string& type) { entertainmentType = type; }
void Entertainment::setArtist(const string& art) { artist = art; }
void Entertainment::setDuration(int dur) { duration = dur; }
void Entertainment::setGenre(const string& gen) { genre = gen; }

    // Override display method
void Entertainment::displayInfo() const {
    Event::displayInfo(); // Call base class display method
    cout << "Entertainment Type: " << entertainmentType << endl;
    cout << "Artist/Performer: " << artist << endl;
    cout << "Duration: " << duration << " minutes" << endl;
    cout << "Genre: " << genre << endl;
}

    // Override getEventType method
string Entertainment::getEventType() const { return "Entertainment"; }

    // Override JSON serialization
json Entertainment::toJSON() const  {
    json j = Event::toJSON(); // Get base class JSON
    j["entertainmentType"] = entertainmentType;
    j["artist"] = artist;
    j["duration"] = duration;
    j["genre"] = genre;
    return j;
}

    // Override JSON deserialization
void Entertainment::fromJSON(const json& j) {
    Event::fromJSON(j); // Call base class deserialization
    entertainmentType = j["entertainmentType"];
    artist = j["artist"];
    duration = j["duration"];
    genre = j["genre"];
}
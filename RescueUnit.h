#ifndef RESCUEUNIT_H
#define RESCUEUNIT_H

#include <string>
using namespace std;

class RescueUnit {
private:
    int id;
    string location;
    string type;
    bool available;
    int currentEmergency;
    double speedFactor;

public:
    RescueUnit(int i, string loc, string t, double speed = 1.0);

    int getId()               { return id; }
    string getLocation()      { return location; }
    string getType()          { return type; }
    bool isAvailable()        { return available; }
    int getCurrentEmergency() { return currentEmergency; }
    double getSpeedFactor()   { return speedFactor; }

    void setLocation(string loc);
    void setAvailable(bool avail);
    void assignToEmergency(int emergencyId);
    void completeEmergency();
    bool canHandle(string emergencyType);
};

#endif
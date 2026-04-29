#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <vector>
#include <fstream>

#include "Graph.h"
#include "Emergency.h"
#include "RescueUnit.h"
#include "EmergencyRequirement.h"

using namespace std;

class Dispatcher {
private:
    Graph cityMap;
    vector<Emergency> emergencies;
    vector<RescueUnit> rescueUnits;
    int emergencyCounter;

    void initializeCity();
    void initializeRescueUnits();

    struct UnitAssignment {
        int unitId;
        int distance;
        int eta;
        vector<string> path;
        string unitType;
    };

    UnitAssignment findBestUnitForType(string unitType, string emergencyLocation);

public:
    Dispatcher();

    void addEmergency(string location, int severity, string type);
    void allocateResources();
    void completeEmergency(int emergencyId);
    void displayStatus();
    void showMenu();
    void viewLocations();
    void viewCityMap();
    void exportToJSON();
    void run();
};

#endif
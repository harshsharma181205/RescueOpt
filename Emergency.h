#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <string>
#include <vector>
using namespace std;

class Emergency {
private:
    int id;
    string location;
    int severity;
    string type;
    bool assigned;
    int assignedUnit;
    vector<int> assignedUnits;
    bool fullyAssigned;
    
public:
    Emergency(int i, string loc, int sev, string t);

    int    getId()           { return id; }
    string getLocation()     { return location; }
    int    getSeverity()     { return severity; }
    string getType()         { return type; }
    bool   isAssigned()      { return assigned; }
    int    getAssignedUnit() { return assignedUnit; }
    vector<int> getAssignedUnits() { return assignedUnits; }
    bool   isFullyAssigned() { return fullyAssigned; }

    void   assign(int unitId);
    void   addAssignedUnit(int unitId);
    void   markFullyAssigned() { fullyAssigned = true; }
    string getSeverityString();
    string getTypeString();
};

#endif
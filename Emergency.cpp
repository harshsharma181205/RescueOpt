#include "Emergency.h"

Emergency::Emergency(int i, string loc, int sev, string t) {
    id          = i;
    location    = loc;
    severity    = sev;
    type        = t;
    assigned    = false;
    assignedUnit = -1;
    fullyAssigned = false;
}

void Emergency::assign(int unitId) {
    assigned     = true;
    assignedUnit = unitId;
    assignedUnits.push_back(unitId);
}

void Emergency::addAssignedUnit(int unitId) {
    assignedUnits.push_back(unitId);
    if (assignedUnit == -1) assignedUnit = unitId;
    assigned = true;
}

string Emergency::getSeverityString() {
    if (severity == 1) return "LOW";
    if (severity == 2) return "MEDIUM";
    if (severity == 3) return "HIGH";
    return "CRITICAL";
}

string Emergency::getTypeString() {
    if (type == "fire") return " Fire";
    if (type == "medical") return " Medical Emergency";
    if (type == "flood") return " Flood";
    if (type == "earthquake") return " Earthquake";
    if (type == "landslide") return " Landslide";
    if (type == "building_collapse") return " Building Collapse";
    if (type == "road_accident") return " Road Accident";
    if (type == "gas_leak") return " Gas Leak";
    if (type == "electrocution") return " Electrocution";
    if (type == "drowning") return " Drowning";
    if (type == "animal_attack") return " Animal Attack";
    if (type == "avalanche") return " Avalanche";
    if (type == "storm_damage") return " Storm Damage";
    return " General Emergency";
}
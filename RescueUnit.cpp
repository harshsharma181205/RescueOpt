#include "RescueUnit.h"
#include <algorithm>
using namespace std;

RescueUnit::RescueUnit(int i, string loc, string t, double speed) {
    id              = i;
    location        = loc;
    type            = t;
    available       = true;
    currentEmergency = -1;
    speedFactor     = speed;
}

void RescueUnit::setLocation(string loc) {
    location = loc;
}

void RescueUnit::setAvailable(bool avail) {
    available = avail;
}

void RescueUnit::assignToEmergency(int emergencyId) {
    available        = false;
    currentEmergency = emergencyId;
}

void RescueUnit::completeEmergency() {
    available        = true;
    currentEmergency = -1;
}

bool RescueUnit::canHandle(string emergencyType) {
    transform(emergencyType.begin(), emergencyType.end(),
              emergencyType.begin(), ::tolower);

    // Helicopter - Universal Responder
    if (type == "helicopter") return true;

    // Fire Truck Capabilities
    if (type == "fire_truck") {
        if (emergencyType == "fire") return true;
        if (emergencyType == "gas_leak") return true;
        if (emergencyType == "building_collapse") return true;
        if (emergencyType == "storm_damage") return true;
        if (emergencyType == "general") return true;
        return false;
    }

    // Ambulance Capabilities
    if (type == "ambulance") {
        if (emergencyType == "medical") return true;
        if (emergencyType == "road_accident") return true;
        if (emergencyType == "drowning") return true;
        if (emergencyType == "electrocution") return true;
        if (emergencyType == "building_collapse") return true;
        if (emergencyType == "landslide") return true;
        if (emergencyType == "animal_attack") return true;
        if (emergencyType == "general") return true;
        return false;
    }

    // Rescue Team Capabilities
    if (type == "rescue_team") {
        if (emergencyType == "flood") return true;
        if (emergencyType == "earthquake") return true;
        if (emergencyType == "landslide") return true;
        if (emergencyType == "building_collapse") return true;
        if (emergencyType == "avalanche") return true;
        if (emergencyType == "drowning") return true;
        if (emergencyType == "animal_attack") return true;
        if (emergencyType == "storm_damage") return true;
        if (emergencyType == "road_accident") return true;
        if (emergencyType == "gas_leak") return true;
        if (emergencyType == "electrocution") return true;
        if (emergencyType == "general") return true;
        return false;
    }

    return false;
}
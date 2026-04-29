#ifndef EMERGENCY_REQUIREMENTS_H
#define EMERGENCY_REQUIREMENTS_H

#include <vector>
#include <string>
using namespace std;

class EmergencyRequirements {
public:
    // Returns the list of unit types needed for an emergency
    static vector<string> getRequiredUnits(string emergencyType) {
        vector<string> units;
        
        if (emergencyType == "fire") {
            units.push_back("fire_truck");
            units.push_back("ambulance");
        }
        else if (emergencyType == "medical") {
            units.push_back("ambulance");
        }
        else if (emergencyType == "flood") {
            units.push_back("rescue_team");
            units.push_back("ambulance");
            units.push_back("helicopter");
        }
        else if (emergencyType == "earthquake") {
            units.push_back("rescue_team");
            units.push_back("ambulance");
            units.push_back("fire_truck");
            units.push_back("helicopter");
        }
        else if (emergencyType == "landslide") {
            units.push_back("rescue_team");
            units.push_back("ambulance");
            units.push_back("helicopter");
        }
        else if (emergencyType == "building_collapse") {
            units.push_back("rescue_team");
            units.push_back("fire_truck");
            units.push_back("ambulance");
            units.push_back("helicopter");
        }
        else if (emergencyType == "road_accident") {
            units.push_back("ambulance");
            units.push_back("fire_truck");
            units.push_back("rescue_team");
        }
        else if (emergencyType == "gas_leak") {
            units.push_back("fire_truck");
            units.push_back("ambulance");
            units.push_back("rescue_team");
        }
        else if (emergencyType == "electrocution") {
            units.push_back("ambulance");
            units.push_back("rescue_team");
        }
        else if (emergencyType == "drowning") {
            units.push_back("rescue_team");
            units.push_back("ambulance");
            units.push_back("helicopter");
        }
        else if (emergencyType == "animal_attack") {
            units.push_back("ambulance");
            units.push_back("rescue_team");
        }
        else if (emergencyType == "avalanche") {
            units.push_back("rescue_team");
            units.push_back("ambulance");
            units.push_back("helicopter");
        }
        else if (emergencyType == "storm_damage") {
            units.push_back("rescue_team");
            units.push_back("fire_truck");
            units.push_back("ambulance");
            units.push_back("helicopter");
        }
        else if (emergencyType == "general") {
            units.push_back("ambulance");
            units.push_back("rescue_team");
        }
        
        return units;
    }
    
    // For LOW severity - only essential unit
    static vector<string> getRequiredUnitsLow(string emergencyType) {
        vector<string> units;
        
        if (emergencyType == "fire" || emergencyType == "gas_leak" || emergencyType == "storm_damage") {
            units.push_back("fire_truck");
        }
        else if (emergencyType == "medical" || emergencyType == "road_accident" || 
                 emergencyType == "electrocution" || emergencyType == "animal_attack") {
            units.push_back("ambulance");
        }
        else if (emergencyType == "flood" || emergencyType == "earthquake" || 
                 emergencyType == "landslide" || emergencyType == "building_collapse" ||
                 emergencyType == "drowning" || emergencyType == "avalanche") {
            units.push_back("rescue_team");
        }
        else {
            units.push_back("ambulance");
        }
        
        return units;
    }
    
    // Get multiplier based on severity
    static int getSeverityMultiplier(int severity) {
        switch(severity) {
            case 4: return 3;  // CRITICAL: 3x units
            case 3: return 2;  // HIGH: 2x units
            case 2: return 1;  // MEDIUM: 1x units
            case 1: return 0;  // LOW: 0x (only 1 unit total)
            default: return 1;
        }
    }
    
    // Get unit count needed for an emergency type at given severity
    static int getRequiredUnitCount(string emergencyType, int severity) {
        if (severity == 1) return 1;  // LOW: only 1 unit
        
        int baseCount = getRequiredUnits(emergencyType).size();
        int multiplier = getSeverityMultiplier(severity);
        
        return baseCount * multiplier;
    }
};

#endif
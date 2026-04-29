#include "Dispatcher.h"
#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>
#include <iomanip>
using namespace std;

Dispatcher::Dispatcher() {
    emergencyCounter = 1;
    initializeCity();
    initializeRescueUnits();
}

//  FIND BEST UNIT FOR SPECIFIC TYPE 
Dispatcher::UnitAssignment Dispatcher::findBestUnitForType(string unitType, string emergencyLocation) {
    UnitAssignment result;
    result.unitId = -1;
    result.distance = INT_MAX;
    result.eta = INT_MAX;
    
    for (RescueUnit& unit : rescueUnits) {
        if (unit.isAvailable() && unit.getType() == unitType) {
            auto [path, distance] = cityMap.shortestPath(unit.getLocation(), emergencyLocation);
            
            if (distance < result.distance) {
                result.distance = distance;
                result.unitId = unit.getId();
                result.path = path;
                result.unitType = unit.getType();
                result.eta = (int)(distance / unit.getSpeedFactor());
            }
        }
    }
    
    return result;
}

// INITIALIZE CITY WITH 30+ LOCATIONS 
void Dispatcher::initializeCity() {
    // LOCATION 1-10: EMERGENCY SERVICES
    cityMap.addLocation("Central_Hospital");
    cityMap.addLocation("City_Hospital_North");
    cityMap.addLocation("City_Hospital_South");
    cityMap.addLocation("City_Hospital_East");
    cityMap.addLocation("Trauma_Center");
    cityMap.addLocation("Children_Hospital");
    
    cityMap.addLocation("Fire_Station_1");
    cityMap.addLocation("Fire_Station_2");
    cityMap.addLocation("Fire_Station_3");
    cityMap.addLocation("Fire_Station_4");
    cityMap.addLocation("Fire_Station_Central");
    
    cityMap.addLocation("Police_Station");
    cityMap.addLocation("Police_Station_North");
    cityMap.addLocation("Police_Station_South");
    
    // LOCATION 11-20: COMMERCIAL AREAS 
    cityMap.addLocation("Market_Area");
    cityMap.addLocation("Mall");
    cityMap.addLocation("Shopping_Complex");
    cityMap.addLocation("Business_District");
    cityMap.addLocation("IT_Park");
    cityMap.addLocation("Food_Court");
    cityMap.addLocation("Movie_Theater");
    cityMap.addLocation("Convention_Center");
    
    // LOCATION 21-25: RESIDENTIAL AREAS 
    cityMap.addLocation("Residential_Area");
    cityMap.addLocation("Green_Colony");
    cityMap.addLocation("Lake_View_Apartments");
    cityMap.addLocation("Staff_Quarters");
    cityMap.addLocation("Farm_House_Area");
    
    //LOCATION 26-30: INDUSTRIAL & TRANSPORT 
    cityMap.addLocation("Industrial_Area");
    cityMap.addLocation("Factory_Zone");
    cityMap.addLocation("Warehouse_District");
    cityMap.addLocation("Airport");
    cityMap.addLocation("Railway_Station");
    cityMap.addLocation("Bus_Depot");
    
    // LOCATION 31-35: EDUCATIONAL & RECREATION 
    cityMap.addLocation("School");
    cityMap.addLocation("University");
    cityMap.addLocation("Engineering_College");
    cityMap.addLocation("Central_Park");
    cityMap.addLocation("Sports_Complex");
    cityMap.addLocation("Swimming_Pool");
    
    //  LOCATION 36-40: HIGHWAY & OTHER 
    cityMap.addLocation("Main_Chowk");
    cityMap.addLocation("Flyover_Junction");
    cityMap.addLocation("Toll_Plaza");
    cityMap.addLocation("Helipad_Central");
    cityMap.addLocation("SDRF_Base");
    
    // ROADS WITH REALISTIC DISTANCES (IN KM) 
    
    // Hospital to Fire Station connections
    cityMap.addRoad("Central_Hospital", "Fire_Station_Central", 2);
    cityMap.addRoad("City_Hospital_North", "Fire_Station_1", 3);
    cityMap.addRoad("City_Hospital_South", "Fire_Station_2", 3);
    cityMap.addRoad("City_Hospital_East", "Fire_Station_3", 4);
    cityMap.addRoad("Trauma_Center", "Fire_Station_4", 2);
    
    // Hospital to Police Station connections
    cityMap.addRoad("Central_Hospital", "Police_Station", 2);
    cityMap.addRoad("City_Hospital_North", "Police_Station_North", 2);
    cityMap.addRoad("City_Hospital_South", "Police_Station_South", 3);
    
    // Fire Stations to each other
    cityMap.addRoad("Fire_Station_1", "Fire_Station_2", 8);
    cityMap.addRoad("Fire_Station_2", "Fire_Station_3", 7);
    cityMap.addRoad("Fire_Station_3", "Fire_Station_4", 6);
    cityMap.addRoad("Fire_Station_4", "Fire_Station_Central", 5);
    cityMap.addRoad("Fire_Station_Central", "Fire_Station_1", 4);
    
    // Commercial area connections
    cityMap.addRoad("Market_Area", "Central_Hospital", 5);
    cityMap.addRoad("Market_Area", "Fire_Station_1", 3);
    cityMap.addRoad("Market_Area", "Police_Station", 4);
    cityMap.addRoad("Market_Area", "Mall", 3);
    cityMap.addRoad("Mall", "Shopping_Complex", 4);
    cityMap.addRoad("Shopping_Complex", "Business_District", 5);
    cityMap.addRoad("Business_District", "IT_Park", 6);
    cityMap.addRoad("IT_Park", "Airport", 8);
    cityMap.addRoad("Food_Court", "Mall", 2);
    cityMap.addRoad("Movie_Theater", "Shopping_Complex", 3);
    cityMap.addRoad("Convention_Center", "Business_District", 4);
    
    // Residential connections
    cityMap.addRoad("Residential_Area", "Central_Hospital", 8);
    cityMap.addRoad("Residential_Area", "Market_Area", 6);
    cityMap.addRoad("Green_Colony", "Residential_Area", 4);
    cityMap.addRoad("Lake_View_Apartments", "Green_Colony", 3);
    cityMap.addRoad("Staff_Quarters", "Police_Station", 4);
    cityMap.addRoad("Farm_House_Area", "Airport", 10);
    
    // Industrial connections
    cityMap.addRoad("Industrial_Area", "Fire_Station_2", 7);
    cityMap.addRoad("Industrial_Area", "Factory_Zone", 5);
    cityMap.addRoad("Factory_Zone", "Warehouse_District", 4);
    cityMap.addRoad("Warehouse_District", "Fire_Station_3", 6);
    cityMap.addRoad("Industrial_Area", "Airport", 10);
    
    // Educational connections
    cityMap.addRoad("School", "Fire_Station_2", 6);
    cityMap.addRoad("School", "Residential_Area", 4);
    cityMap.addRoad("University", "School", 5);
    cityMap.addRoad("University", "Central_Park", 4);
    cityMap.addRoad("Engineering_College", "University", 3);
    cityMap.addRoad("Engineering_College", "IT_Park", 5);
    
    // Recreation connections
    cityMap.addRoad("Central_Park", "Mall", 5);
    cityMap.addRoad("Sports_Complex", "University", 6);
    cityMap.addRoad("Swimming_Pool", "Sports_Complex", 3);
    cityMap.addRoad("Central_Park", "Lake_View_Apartments", 4);
    
    // Transportation connections
    cityMap.addRoad("Airport", "Helipad_Central", 2);
    cityMap.addRoad("Railway_Station", "Bus_Depot", 3);
    cityMap.addRoad("Railway_Station", "Market_Area", 5);
    cityMap.addRoad("Bus_Depot", "Industrial_Area", 7);
    
    // Highway connections
    cityMap.addRoad("Main_Chowk", "Market_Area", 3);
    cityMap.addRoad("Main_Chowk", "Police_Station", 4);
    cityMap.addRoad("Flyover_Junction", "Business_District", 4);
    cityMap.addRoad("Toll_Plaza", "Airport", 7);
    cityMap.addRoad("Toll_Plaza", "Industrial_Area", 8);
    
    // SDRF Base connections
    cityMap.addRoad("SDRF_Base", "Fire_Station_Central", 5);
    cityMap.addRoad("SDRF_Base", "Helipad_Central", 3);
    cityMap.addRoad("SDRF_Base", "Police_Station", 6);
    
    // Cross connections for better routing
    cityMap.addRoad("Central_Hospital", "Trauma_Center", 4);
    cityMap.addRoad("Fire_Station_1", "Market_Area", 3);
    cityMap.addRoad("Fire_Station_2", "Industrial_Area", 7);
    cityMap.addRoad("Fire_Station_3", "Warehouse_District", 5);
    cityMap.addRoad("Fire_Station_4", "City_Hospital_East", 3);
    cityMap.addRoad("Police_Station_North", "City_Hospital_North", 2);
    cityMap.addRoad("Police_Station_South", "City_Hospital_South", 2);
    
    // More cross connections
    cityMap.addRoad("Green_Colony", "School", 5);
    cityMap.addRoad("Lake_View_Apartments", "Mall", 6);
    cityMap.addRoad("University", "Central_Park", 4);
    cityMap.addRoad("IT_Park", "Business_District", 5);
    cityMap.addRoad("Factory_Zone", "Fire_Station_2", 6);
    cityMap.addRoad("Warehouse_District", "Fire_Station_3", 5);
    cityMap.addRoad("Helipad_Central", "Central_Hospital", 4);
    cityMap.addRoad("Central_Hospital", "Market_Area", 5);
    cityMap.addRoad("Farm_House_Area", "Airport", 10);
}

// INITIALIZE RESCUE UNITS (MORE UNITS FOR CRITICAL SITUATIONS) 
void Dispatcher::initializeRescueUnits() {
    //  FIRE TRUCKS (7 units for large fires) 
    rescueUnits.push_back(RescueUnit(1,  "Fire_Station_1",        "fire_truck"));
    rescueUnits.push_back(RescueUnit(2,  "Fire_Station_2",        "fire_truck"));
    rescueUnits.push_back(RescueUnit(3,  "Fire_Station_3",        "fire_truck"));
    rescueUnits.push_back(RescueUnit(4,  "Fire_Station_4",        "fire_truck"));
    rescueUnits.push_back(RescueUnit(5,  "Fire_Station_Central",  "fire_truck"));
    rescueUnits.push_back(RescueUnit(6,  "Industrial_Area",       "fire_truck"));
    rescueUnits.push_back(RescueUnit(7,  "Airport",               "fire_truck"));
    
    //  AMBULANCES (8 units for mass casualties)
    rescueUnits.push_back(RescueUnit(8,  "Central_Hospital",      "ambulance"));
    rescueUnits.push_back(RescueUnit(9,  "Central_Hospital",      "ambulance"));
    rescueUnits.push_back(RescueUnit(10, "City_Hospital_North",   "ambulance"));
    rescueUnits.push_back(RescueUnit(11, "City_Hospital_North",   "ambulance"));
    rescueUnits.push_back(RescueUnit(12, "City_Hospital_South",   "ambulance"));
    rescueUnits.push_back(RescueUnit(13, "City_Hospital_East",    "ambulance"));
    rescueUnits.push_back(RescueUnit(14, "Trauma_Center",         "ambulance"));
    rescueUnits.push_back(RescueUnit(15, "Children_Hospital",     "ambulance"));
    
    // RESCUE TEAMS (6 units for floods/earthquakes) 
    rescueUnits.push_back(RescueUnit(16, "Police_Station",        "rescue_team"));
    rescueUnits.push_back(RescueUnit(17, "Police_Station_North",  "rescue_team"));
    rescueUnits.push_back(RescueUnit(18, "Police_Station_South",  "rescue_team"));
    rescueUnits.push_back(RescueUnit(19, "Fire_Station_1",        "rescue_team"));
    rescueUnits.push_back(RescueUnit(20, "SDRF_Base",             "rescue_team"));
    rescueUnits.push_back(RescueUnit(21, "SDRF_Base",             "rescue_team"));
    
    // HELICOPTERS (4 units for fast response) 
    rescueUnits.push_back(RescueUnit(22, "Helipad_Central",       "helicopter", 2.0));
    rescueUnits.push_back(RescueUnit(23, "Airport",               "helicopter", 2.0));
    rescueUnits.push_back(RescueUnit(24, "SDRF_Base",             "helicopter", 2.0));
    rescueUnits.push_back(RescueUnit(25, "Helipad_Central",       "helicopter", 2.0));
}

// ADD EMERGENCY 
void Dispatcher::addEmergency(string location, int severity, string type) {
    if(!cityMap.locationExistsCheck(location)) {
        cout << "\n❌ Location '" << location << "' does not exist!\n";
        cout << "   Use option 6 to see all valid locations.\n";
        return;
    }
    
    if (severity < 1 || severity > 4) {
        cout << "\n❌ Severity must be between 1 and 4!\n";
        return;
    }
    
    vector<string> validTypes = {"fire", "medical", "flood", "earthquake", "landslide", 
                                  "building_collapse", "road_accident", "gas_leak", 
                                  "electrocution", "drowning", "animal_attack", 
                                  "avalanche", "storm_damage", "general"};
    
    bool validType = false;
    for(string t : validTypes) {
        if(t == type) { validType = true; break; }
    }
    
    if(!validType) {
        cout << "\n❌ Invalid emergency type! Available types:\n";
        for(string t : validTypes) cout << "   - " << t << "\n";
        return;
    }
    
    emergencies.push_back(Emergency(emergencyCounter, location, severity, type));
    Emergency temp(emergencyCounter, location, severity, type);
    
    cout << "\n✅ EMERGENCY #" << emergencyCounter << " ADDED SUCCESSFULLY!\n";
    cout << "   ┌─────────────────────────────────────────┐\n";
    cout << "   │ 📍 Location: " << location << "\n";
    cout << "   │ ⚠️  Severity: " << temp.getSeverityString() << "\n";
    cout << "   │ 🚨 Type: " << temp.getTypeString() << "\n";
    cout << "   └─────────────────────────────────────────┘\n";
    emergencyCounter++;
    exportToJSON();
}

// ========== ALLOCATE RESOURCES ==========
void Dispatcher::allocateResources() {
    if (emergencies.empty()) {
        cout << "\n⚠️  No emergencies to allocate!\n";
        return;
    }
    
    cout << "\n╔══════════════════════════════════════════════════════════════════╗\n";
    cout << "║              MULTI-UNIT RESOURCE ALLOCATION SYSTEM                ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════╝\n";
    
    vector<Emergency*> pendingEmergencies;
    for (auto& e : emergencies) {
        if (!e.isFullyAssigned()) {
            pendingEmergencies.push_back(&e);
        }
    }
    
    if (pendingEmergencies.empty()) {
        cout << "\n✅ All emergencies are fully staffed!\n";
        return;
    }
    
    sort(pendingEmergencies.begin(), pendingEmergencies.end(),
         [](Emergency* a, Emergency* b) {
             if (a->getSeverity() != b->getSeverity())
                 return a->getSeverity() > b->getSeverity();
             return a->getId() < b->getId();
         });
    
    int totalAssigned = 0;
    
    for (Emergency* emergency : pendingEmergencies) {
        cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
        cout << "│ 📢 EMERGENCY #" << emergency->getId()
             << " [" << emergency->getSeverityString() << "]"
             << " " << emergency->getTypeString() << "\n";
        cout << "│ 📍 Location: " << emergency->getLocation() << "\n";
        cout << "└─────────────────────────────────────────────────────────────────┘\n";
        
        vector<string> requiredUnits;
        int severity = emergency->getSeverity();
        
        if (severity == 1) {
            requiredUnits = EmergencyRequirements::getRequiredUnitsLow(emergency->getType());
            cout << "\n   📋 LOW SEVERITY - Assigning only essential unit:\n";
        } else {
            requiredUnits = EmergencyRequirements::getRequiredUnits(emergency->getType());
            int multiplier = EmergencyRequirements::getSeverityMultiplier(severity);
            cout << "\n   📋 Required Units: ";
            for (string u : requiredUnits) cout << u << " ";
            cout << " (x" << multiplier << " for " << emergency->getSeverityString() << " severity)\n";
        }
        
        int unitsAssigned = 0;
        
        for (string unitType : requiredUnits) {
            int neededCount = 1;
            if (severity >= 3 && (unitType == "ambulance" || unitType == "rescue_team")) {
                neededCount = (severity == 4) ? 3 : 2;
            }
            if (severity == 4 && unitType == "fire_truck") neededCount = 2;
            
            for (int i = 0; i < neededCount; i++) {
                UnitAssignment assignment = findBestUnitForType(unitType, emergency->getLocation());
                
                if (assignment.unitId != -1) {
                    for (RescueUnit& unit : rescueUnits) {
                        if (unit.getId() == assignment.unitId) {
                            unit.assignToEmergency(emergency->getId());
                            emergency->addAssignedUnit(assignment.unitId);
                            unitsAssigned++;
                            totalAssigned++;
                            
                            cout << "\n   ✅ ASSIGNED: " << unitType;
                            if (unitType == "fire_truck") cout << " ";
                            else if (unitType == "ambulance") cout << " ";
                            else if (unitType == "rescue_team") cout << " ";
                            else if (unitType == "helicopter") cout << " ";
                            cout << " #" << assignment.unitId << "\n";
                            cout << "      📍 From: " << unit.getLocation() << "\n";
                            cout << "      📏 DISTANCE: " << assignment.distance << " KM\n";
                            cout << "      ⏱️  ETA: " << assignment.eta << " minutes";
                            if (unit.getSpeedFactor() == 2.0) cout << " (2x speed - helicopter)";
                            cout << "\n";
                            cout << "      🗺️  Route: ";
                            for (size_t j = 0; j < assignment.path.size(); j++) {
                                cout << assignment.path[j];
                                if (j + 1 < assignment.path.size()) cout << " → ";
                            }
                            cout << "\n";
                            break;
                        }
                    }
                } else {
                    cout << "\n   ⚠️  No available " << unitType << " found";
                    if (i < neededCount - 1) cout << " (need " << (neededCount - i) << " more)";
                    cout << "!\n";
                }
            }
        }
        
        if (unitsAssigned > 0) {
            cout << "\n   ┌─────────────────────────────────────────────────────────┐\n";
            cout << "   │ ✅ Assigned " << unitsAssigned << " unit(s) to Emergency #" << emergency->getId() << "\n";
            
            bool fullyStaffed = true;
            vector<string> required = (severity == 1) ? 
                EmergencyRequirements::getRequiredUnitsLow(emergency->getType()) :
                EmergencyRequirements::getRequiredUnits(emergency->getType());
            
            for (string req : required) {
                bool found = false;
                for (int uid : emergency->getAssignedUnits()) {
                    for (RescueUnit& u : rescueUnits) {
                        if (u.getId() == uid && u.getType() == req) {
                            found = true;
                            break;
                        }
                    }
                    if (found) break;
                }
                if (!found) {
                    fullyStaffed = false;
                    break;
                }
            }
            
            if (fullyStaffed) {
                emergency->markFullyAssigned();
                cout << "   │  Emergency #" << emergency->getId() << " is FULLY STAFFED!\n";
                cout << "   └─────────────────────────────────────────────────────────┘\n";
            } else {
                cout << "   │  Still needs more units. Will retry next allocation.\n";
                cout << "   └─────────────────────────────────────────────────────────┘\n";
            }
        } else {
            cout << "\n    NO UNITS AVAILABLE for this emergency!\n";
            cout << "    Complete some emergencies (Option 4) to free up units.\n";
        }
    }
    
    cout << "\n╔══════════════════════════════════════════════════════════════════╗\n";
    cout << "║                    ALLOCATION COMPLETE                           ║\n";
    cout << "║                    Total Units Assigned: " << totalAssigned << "\n";
    cout << "╚══════════════════════════════════════════════════════════════════╝\n";
    exportToJSON();
}

//COMPLETE EMERGENCY 
void Dispatcher::completeEmergency(int emergencyId) {
    for (auto it = emergencies.begin(); it != emergencies.end(); ++it) {
        if (it->getId() == emergencyId && it->isAssigned()) {
            for (int unitId : it->getAssignedUnits()) {
                for (RescueUnit& u : rescueUnits) {
                    if (u.getId() == unitId) {
                        u.completeEmergency();
                        cout << "\n   🔓 Unit #" << unitId << " (" << u.getType() << ") is now AVAILABLE";
                        if (u.getType() == "helicopter") cout << " 🚁";
                        cout << "\n";
                        break;
                    }
                }
            }
            cout << "\n✅ EMERGENCY #" << emergencyId << " COMPLETED AND CLOSED!\n";
            emergencies.erase(it);
            
            bool hasPending = false;
            for (auto& e : emergencies) {
                if (!e.isFullyAssigned()) {
                    hasPending = true;
                    break;
                }
            }
            if (hasPending) {
                cout << "\n🔄 Pending emergencies detected. Running auto-allocation...\n";
                allocateResources();
            }
            exportToJSON();
            return;
        }
    }
    cout << "\n❌ Emergency #" << emergencyId << " not found or not assigned!\n";
}

//  DISPLAY STATUS 
void Dispatcher::displayStatus() {
    cout << "\n╔══════════════════════════════════════════════════════════════════╗\n";
    cout << "║                     CURRENT STATUS REPORT                        ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════╝\n";
    
    cout << "\n📋 ACTIVE EMERGENCIES:\n";
    if (emergencies.empty()) {
        cout << "   ✅ No active emergencies\n";
    } else {
        for (Emergency& e : emergencies) {
            cout << "\n   ┌─────────────────────────────────────────────────────────┐\n";
            cout << "   │ #" << e.getId() << " | " << e.getLocation();
            cout << " | Severity: " << e.getSeverityString();
            cout << " | Type: " << e.getTypeString() << "\n";
            if (e.isAssigned()) {
                cout << "   │ ✅ Assigned Units: ";
                for (int uid : e.getAssignedUnits()) {
                    for (RescueUnit& u : rescueUnits) {
                        if (u.getId() == uid) {
                            cout << "#" << uid << " (" << u.getType() << ") ";
                            break;
                        }
                    }
                }
                cout << "\n";
                if (e.isFullyAssigned()) {
                    cout << "   │ 🎯 Status: FULLY STAFFED\n";
                } else {
                    cout << "   │ ⏳ Status: PARTIALLY STAFFED (needs more units)\n";
                }
            } else {
                cout << "   │ ⏳ Status: PENDING\n";
            }
            cout << "   └─────────────────────────────────────────────────────────┘\n";
        }
    }
    
    cout << "\n🚑 RESCUE UNITS STATUS:\n";
    
    cout << "\n    FIRE TRUCKS (7 units):\n";
    for (RescueUnit& u : rescueUnits) {
        if (u.getType() == "fire_truck") {
            cout << "      Unit #" << u.getId() << " @ " << u.getLocation();
            if (u.isAvailable()) cout << "  ✅ AVAILABLE\n";
            else cout << "  🔴 BUSY → Emergency #" << u.getCurrentEmergency() << "\n";
        }
    }
    
    cout << "\n   🚑 AMBULANCES (8 units):\n";
    for (RescueUnit& u : rescueUnits) {
        if (u.getType() == "ambulance") {
            cout << "      Unit #" << u.getId() << " @ " << u.getLocation();
            if (u.isAvailable()) cout << "  ✅ AVAILABLE\n";
            else cout << "  🔴 BUSY → Emergency #" << u.getCurrentEmergency() << "\n";
        }
    }
    
    cout << "\n   👷 RESCUE TEAMS (6 units):\n";
    for (RescueUnit& u : rescueUnits) {
        if (u.getType() == "rescue_team") {
            cout << "      Unit #" << u.getId() << " @ " << u.getLocation();
            if (u.isAvailable()) cout << "  ✅ AVAILABLE\n";
            else cout << "  🔴 BUSY → Emergency #" << u.getCurrentEmergency() << "\n";
        }
    }
    
    cout << "\n   🚁 HELICOPTERS (4 units) [2x SPEED]:\n";
    for (RescueUnit& u : rescueUnits) {
        if (u.getType() == "helicopter") {
            cout << "      Unit #" << u.getId() << " @ " << u.getLocation();
            if (u.isAvailable()) cout << "  ✅ AVAILABLE\n";
            else cout << "  🔴 BUSY → Emergency #" << u.getCurrentEmergency() << "\n";
        }
    }
}

// ========== VIEW LOCATIONS ==========
void Dispatcher::viewLocations() {
    cout << "\n╔══════════════════════════════════════════════════════════════════╗\n";
    cout << "║                    AVAILABLE LOCATIONS (40+)                     ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════╝\n";
    
    vector<string> locations = cityMap.getAllLocations();
    
    cout << "\n   🏥 HOSPITALS:\n";
    vector<string> hospitals = {"Central_Hospital", "City_Hospital_North", "City_Hospital_South", 
                                 "City_Hospital_East", "Trauma_Center", "Children_Hospital"};
    for (string loc : hospitals) {
        if (cityMap.locationExistsCheck(loc))
            cout << "      • " << loc << "\n";
    }
    
    cout << "\n    FIRE STATIONS:\n";
    vector<string> fireStations = {"Fire_Station_1", "Fire_Station_2", "Fire_Station_3", 
                                    "Fire_Station_4", "Fire_Station_Central"};
    for (string loc : fireStations) {
        if (cityMap.locationExistsCheck(loc))
            cout << "      • " << loc << "\n";
    }
    
    cout << "\n    POLICE STATIONS:\n";
    vector<string> policeStations = {"Police_Station", "Police_Station_North", "Police_Station_South"};
    for (string loc : policeStations) {
        if (cityMap.locationExistsCheck(loc))
            cout << "      • " << loc << "\n";
    }
    
    cout << "\n     COMMERCIAL AREAS:\n";
    vector<string> commercial = {"Market_Area", "Mall", "Shopping_Complex", "Business_District", 
                                  "IT_Park", "Food_Court", "Movie_Theater", "Convention_Center"};
    for (string loc : commercial) {
        if (cityMap.locationExistsCheck(loc))
            cout << "      • " << loc << "\n";
    }
    
    cout << "\n   🏘️  RESIDENTIAL AREAS:\n";
    vector<string> residential = {"Residential_Area", "Green_Colony", "Lake_View_Apartments", 
                                   "Staff_Quarters", "Farm_House_Area"};
    for (string loc : residential) {
        if (cityMap.locationExistsCheck(loc))
            cout << "      • " << loc << "\n";
    }
    
    cout << "\n   🏭 INDUSTRIAL & TRANSPORT:\n";
    vector<string> industrial = {"Industrial_Area", "Factory_Zone", "Warehouse_District", 
                                  "Airport", "Railway_Station", "Bus_Depot"};
    for (string loc : industrial) {
        if (cityMap.locationExistsCheck(loc))
            cout << "      • " << loc << "\n";
    }
    
    cout << "\n   🎓 EDUCATIONAL & RECREATION:\n";
    vector<string> edu = {"School", "University", "Engineering_College", "Central_Park", 
                           "Sports_Complex", "Swimming_Pool"};
    for (string loc : edu) {
        if (cityMap.locationExistsCheck(loc))
            cout << "      • " << loc << "\n";
    }
    
    cout << "\n   🛣️  HIGHWAY & OTHER:\n";
    vector<string> other = {"Main_Chowk", "Flyover_Junction", "Toll_Plaza", "Helipad_Central", "SDRF_Base"};
    for (string loc : other) {
        if (cityMap.locationExistsCheck(loc))
            cout << "      • " << loc << "\n";
    }
}

// VIEW CITY MAP
void Dispatcher::viewCityMap() {
    cityMap.displayMap();
}

void Dispatcher::exportToJSON() {
    ofstream file("data.json");

    file << "{\n";
    file << "  \"emergencies\": [\n";

    for (size_t i = 0; i < emergencies.size(); i++) {

        Emergency &e = emergencies[i];

        file << "    {\n";
        file << "      \"id\": " << e.getId() << ",\n";
        file << "      \"location\": \"" << e.getLocation() << "\",\n";
        file << "      \"severity\": \"" << e.getSeverityString() << "\",\n";
        file << "      \"type\": \"" << e.getTypeString() << "\",\n";
        file << "      \"assigned\": "
             << (e.isAssigned() ? "true" : "false") << "\n";

        file << "    }";

        if (i != emergencies.size() - 1)
            file << ",";

        file << "\n";
    }

    file << "  ]\n";
    file << "}\n";

    file.close();
}

// SHOW MENU 
void Dispatcher::showMenu() {
    cout << "\n╔══════════════════════════════════════════════════════════════════╗\n";
    cout << "║              RESCUEOPT - DISASTER RESPONSE SYSTEM                ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════╣\n";
    cout << "║  1️⃣  Add New Emergency                                           ║\n";
    cout << "║  2️⃣  View Current Status                                         ║\n";
    cout << "║  3️⃣  Allocate Resources (Multi-Unit + Distance + ETA)           ║\n";
    cout << "║  4️⃣  Complete Emergency                                          ║\n";
    cout << "║  5️⃣  View City Map                                               ║\n";
    cout << "║  6️⃣  View All Locations                                          ║\n";
    cout << "║  7️⃣  Exit                                                        ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════╝\n";
    cout << "Enter your choice: ";
}

// MAIN RUN LOOP 
void Dispatcher::run() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        
        switch(choice) {
            case 1: {
                string location, type;
                int severity;
                
                cout << "\n--- ADD NEW EMERGENCY ---\n";
                cout << "Location (use option 6 to see all 40+ locations): ";
                cin >> location;
                
                cout << "Severity (1=Low, 2=Medium, 3=High, 4=Critical): ";
                cin >> severity;
                
                cout << "Type (fire/medical/flood/earthquake/landslide/building_collapse/road_accident/gas_leak/electrocution/drowning/animal_attack/avalanche/storm_damage/general): ";
                cin >> type;
                
                addEmergency(location, severity, type);
                break;
            }
            
            case 2:
                displayStatus();
                break;
                
            case 3:
                allocateResources();
                break;
                
            case 4: {
                int id;
                cout << "\nEnter Emergency ID to complete: ";
                cin >> id;
                completeEmergency(id);
                break;
            }
            
            case 5:
                viewCityMap();
                break;
                
            case 6:
                viewLocations();
                break;
                
            case 7:
                cout << "\n👋 Thank you for using RescueOpt! Stay safe!\n";
                break;
                
            default:
                cout << "\n❌ Invalid choice! Please try again.\n";
        }
    } while(choice != 7);
}
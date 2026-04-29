#include "Graph.h"
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

// TERRAIN DETECTION FUNCTION 
string Graph::getTerrainFromLocation(string locationName) {
    if (locationName.find("Hospital") != string::npos ||
        locationName.find("Fire_Station") != string::npos ||
        locationName.find("Police_Station") != string::npos ||
        locationName.find("Market") != string::npos ||
        locationName.find("Mall") != string::npos ||
        locationName.find("School") != string::npos ||
        locationName.find("Airport") != string::npos ||
        locationName.find("Station") != string::npos ||
        locationName.find("Depot") != string::npos ||
        locationName.find("Chowk") != string::npos ||
        locationName.find("Bridge") != string::npos ||
        locationName.find("Highway") != string::npos ||
        locationName.find("Trauma") != string::npos ||
        locationName.find("Children") != string::npos) {
        return "normal";
    }
    if (locationName.find("Residential") != string::npos ||
        locationName.find("Colony") != string::npos ||
        locationName.find("Apartments") != string::npos ||
        locationName.find("University") != string::npos ||
        locationName.find("College") != string::npos ||
        locationName.find("Park") != string::npos ||
        locationName.find("Complex") != string::npos ||
        locationName.find("Garden") != string::npos ||
        locationName.find("Factory") != string::npos ||
        locationName.find("Warehouse") != string::npos ||
        locationName.find("Business") != string::npos ||
        locationName.find("IT_Park") != string::npos ||
        locationName.find("Convention") != string::npos ||
        locationName.find("Sports") != string::npos ||
        locationName.find("Pool") != string::npos) {
        return "hilly";
    }
    if (locationName.find("Farm") != string::npos ||
        locationName.find("Village") != string::npos ||
        locationName.find("Hill") != string::npos ||
        locationName.find("Peak") != string::npos ||
        locationName.find("Ridge") != string::npos ||
        locationName.find("Temple") != string::npos ||
        locationName.find("Trek") != string::npos ||
        locationName.find("Route") != string::npos ||
        locationName.find("Base") != string::npos ||
        locationName.find("Helipad") != string::npos ||
        locationName.find("Remote") != string::npos ||
        locationName.find("Falls") != string::npos ||
        locationName.find("Forest") != string::npos ||
        locationName.find("Lake_View") != string::npos ||
        locationName.find("Quarters") != string::npos) {
        return "mountain";
    }
    
    return "normal"; // Default
}

//  ADD LOCATION 
void Graph::addLocation(string name) {
    if(!locationExists[name]) {
        adjList[name] = vector<pair<string, int>>();
        locationExists[name] = true;
    }
}

// ADD ROAD WITH AUTO-TERRAIN DETECTION 
void Graph::addRoad(string from, string to, int baseDistance) {
    if(locationExists[from] && locationExists[to]) {
        
        // Auto-detect terrain from both location names
        string terrainFrom = getTerrainFromLocation(from);
        string terrainTo = getTerrainFromLocation(to);
        string terrain = "normal";
        int multiplier = 1;
        
        if (terrainFrom == "mountain" || terrainTo == "mountain") {
            terrain = "mountain";
            multiplier = 3;
        } else if (terrainFrom == "hilly" || terrainTo == "hilly") {
            terrain = "hilly";
            double multiplier = 1.5;
        }    
        // Calculate effective distance
        int effectiveDistance = baseDistance;
        if (terrain == "hilly") effectiveDistance = (int)(baseDistance * 1.5);
        if (terrain == "mountain") effectiveDistance = baseDistance * 3;
        // Add road with effective distance
        adjList[from].push_back({to, effectiveDistance});
        adjList[to].push_back({from, effectiveDistance});
    }
}
//  SHORTEST PATH (DIJKSTRA) 
pair<vector<string>, int> Graph::shortestPath(string start, string end) {
    map<string, int> dist;
    map<string, string> prev;
    map<string, bool> visited;
    
    for(auto& loc : adjList) {
        dist[loc.first] = INT_MAX;
    }
    dist[start] = 0;  
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, start});  
    while(!pq.empty()) {
        string current = pq.top().second;
        pq.pop();      
        if(visited[current]) continue;
        visited[current] = true;   
        if(current == end) break;
        
        for(auto& neighbor : adjList[current]) {
            string next = neighbor.first;
            int weight = neighbor.second;
            
            if(dist[current] + weight < dist[next]) {
                dist[next] = dist[current] + weight;
                prev[next] = current;
                pq.push({dist[next], next});
            }
        }
    }
    
    vector<string> path;
    if(dist[end] != INT_MAX) {
        string current = end;
        while(current != "") {
            path.push_back(current);
            if(prev.find(current) != prev.end())
                current = prev[current];
            else
                break;
        }
        reverse(path.begin(), path.end());
    }
    
    return {path, dist[end]};
}

bool Graph::locationExistsCheck(string name) {
    return locationExists[name];
}

vector<string> Graph::getAllLocations() {
    vector<string> locations;
    for(auto& loc : adjList) {
        locations.push_back(loc.first);
    }
    return locations;
}

void Graph::displayMap() {
    cout << "\n=== CITY MAP ===\n";
    for(auto& loc : adjList) {
        cout << loc.first << " -> ";
        for(auto& road : loc.second) {
            cout << road.first << "(" << road.second << "KM) ";
        }
        cout << endl;
    }
}
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;

class Graph {
private:
    map<string, vector<pair<string, int>>> adjList;
    map<string, bool> locationExists;
    string getTerrainFromLocation(string locationName);
    
public:
    void addLocation(string name);
    void addRoad(string from, string to, int baseDistance);
    pair<vector<string>, int> shortestPath(string start, string end);
    bool locationExistsCheck(string name);
    vector<string> getAllLocations();
    void displayMap();
};

#endif
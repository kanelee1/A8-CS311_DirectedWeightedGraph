#include <iostream>
#include "graph.h"
#include <string>
#include <cstring>

using namespace std;
//give main arguments thru command line (ex: ./main AN BK)
int main(int argc, char *argv[]) {

  if (argc != 3) {
        cout << "Input error: Requires ./main, start city code, and end city code" << endl;
        return 1;
    }

    // Read city and road data
    vector<City> cities;
    vector<Road> roads;
    readCities(cities);
    readRoads(roads);

    // Print header
    printHeader();

    // Convert command-line arguments to city codes
    string startCityCode = argv[1];  // argv[0] is the program name
    string endCityCode = argv[2];

    // Find corresponding city IDs
    int startCityID = findCityID(cities, startCityCode);
    int endCityID = findCityID(cities, endCityCode);

    // check if valid city codes
    if (startCityID == -1 || endCityID == -1) {
        cout << "Invalid city codes" << endl;
        return 1;
    }
    
    //print given city information
    cout << "\nFrom City: " << cities[findCityIndex(cities, startCityID)].name
         << ", population " << cities[findCityIndex(cities, startCityID)].population
         << ", elevation " << cities[findCityIndex(cities, startCityID)].elevation << endl;
    cout << "To City: " << cities[findCityIndex(cities, endCityID)].name
         << ", population " << cities[findCityIndex(cities, endCityID)].population
         << ", elevation " << cities[findCityIndex(cities, endCityID)].elevation << endl;
    
    // Build graph
    unordered_map<int, vector<pair<int, int>>> graph;
    buildGraph(cities, roads, graph);

    // Call Dijkstra's algorithm
    Dijkstra(cities, roads, startCityID, endCityID);

    return 0;
}

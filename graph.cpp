#pragma once

#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <queue>

using namespace std;


// Read city data from file
void readCities(vector<City>& cities) {
    ifstream file("city.txt");
    if (!file.is_open()) {
        cout << "Error opening city.txt" << endl;
        exit(1);
    }
    City city;
    while (file >> city.ID >> city.code >> city.name >> city.population >> city.elevation) {
        cities.push_back(city);
    }
    file.close();
}

// Read road data from file
void readRoads(vector<Road>& roads) {
    ifstream file("road.txt");
    if (!file.is_open()) {
        cout << "Error opening road.txt" << endl;
        exit(1);
    }
    Road road;
    while (file >> road.from_cityID >> road.to_cityID >> road.distance) {
        roads.push_back(road);
    }
    file.close();
}
//----------------------------------------------------------------------------------

//Find index of city in cities vector
//param: cities vector, city ID
//return index
int findCityIndex(const vector<City>& cities, const int cityID) {
  for (size_t i = 0; i < cities.size(); i++) {
    if (cityID == cities[i].ID) {
      return i;
    } 
  }
  cout << "city not found (findCityIndex)" << endl;
  return -1;
}

//----------------------------------------------------------------------------------
//find corresponding city ID from given city code
//param: cities vector, city code
//if key city code matches in cities vector, return current ID number
int findCityID(const vector<City>& cities, const string& cityCode) {
  
    for (size_t i = 0; i < cities.size(); i++) {
        if (cityCode == cities[i].code) {
            return cities[i].ID;
        }
    }
    cout << "City not found" << endl;
    return -1;
}
//----------------------------------------------------------------------------------
// Build graph
void buildGraph(const vector<City>& cities, const vector<Road>& roads, unordered_map<int, vector<pair<int, int>>>& graph) {
    for (const Road& road : roads) {
        int fromCityIndex = findCityIndex(cities, road.from_cityID);
        int toCityIndex = findCityIndex(cities, road.to_cityID);
        int distance = road.distance;

        graph[fromCityIndex].push_back({toCityIndex, distance});
        // If roads are not one-directional, add the reverse edge:
        // graph[toCityIndex].push_back({fromCityIndex, distance});
    }
}
//--------------------------------------------------------------------------------------
// Dijkstra's algorithm to find shortest path
void Dijkstra(const vector<City>& cities, const vector<Road>& roads, const int startCityID, const int endCityID) {
    //find the index of the starting/source vertex
    int s = findCityIndex(cities, startCityID);
    if (s == -1) {
        cout << "Start city not found" << endl;
        return;
    }
 
    
    vector<int> Dist(cities.size(), numeric_limits<int>::max());
    vector<bool> visited(cities.size(), false);
    vector<int> parents(cities.size(), -1);
    
    Dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (const Road& road : roads) {
            if (road.from_cityID == cities[u].ID) {
                int v = findCityIndex(cities, road.to_cityID);
                if (v != -1 && Dist[u] + road.distance < Dist[v]) {
                    Dist[v] = Dist[u] + road.distance;
                    parents[v] = u;
                    pq.push({Dist[v], v});
                }
            }
        }
    }
    
   if (parents[endCityID] != -1) {
        cout << "The shortest distance from " << cities[startCityID].name << " to "
             << cities[endCityID].name << " is " << Dist[endCityID] << endl;
        cout << "Through the route: ";

        int current = endCityID;
        vector<string> route;
        while (current != startCityID) {
            route.push_back(cities[current].name);
            current = parents[current];
        }
        route.push_back(cities[current].name);
        reverse(route.begin(), route.end());

        for (size_t i = 0; i < route.size(); i++) {
            cout << route[i];
            if (i != route.size() - 1) {
                cout << "->";
            }
        }
        cout << endl;

    } else {
        cout << "Route not found" << endl;
    }
}
//---------------------------------------------------------------------------------------
void printHeader() {
    cout << "Authors: Suphapon Mahawong, Kane Svelan, Brian Sanchez" << endl;
    cout << "Date: xx/xx/20xx" << endl;
    cout << "Course: CS311 (Data structures and Algorithms)" << endl;
    cout << "Description: Program to find the shortest route between cities" << endl;
    cout << "----------------------------------------------------------------" << endl;
}

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Store city data
struct City {
    int ID;
    string code;
    string name;
    int population;
    int elevation;
};

// Store road data
struct Road {
    int from_cityID;
    int to_cityID;
    int distance;
};

void readCities(std::vector<City>& cities);

void readRoads(std::vector<Road>& roads);

int findCityIndex(const std::vector<City>& cities, const int cityID);

int findCityID(const vector<City>& cities, const string& cityCode);

void buildGraph(const std::vector<City>& cities, const std::vector<Road>& roads, 
std::unordered_map<int, std::vector<std::pair<int, int>>>& graph);

void Dijkstra(const std::vector<City>& cities, const std::vector<Road>& roads, const int startCityID, const int endCityID);

void printHeader();
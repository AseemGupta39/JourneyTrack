#ifndef GRAPH_M_H
#define GRAPH_M_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <queue>
#include <set>

using namespace std;

class Graph_M {
private:
    bool isDirected;
public:

    Graph_M(bool isDirected){
        this->isDirected = isDirected;
    }

    struct Vertex {
        map<string, int> neighbors;  // Neighbors and weights (for distance)
    };

    void addVertex(const string &vname);
    void removeVertex(const string &vname);
    void addEdge(const string &vname1, const string &vname2, int weight);
    void removeEdge(const string &vname1, const string &vname2);
    void displayMap() const;
    void displayStations() const;

    bool hasPath(const string &vname1, const string &vname2, map<string, bool> &processed);
    int dijkstra(const string &start, const string &end) const;
    vector<string> findShortestPath(const string &start, const string &end) const;
    vector<vector<string>> findAllPaths(const string &start, const string &end) const;

private:
    map<string, Vertex> vertices;
    int getMinDistance(const map<string, int> &dist, const set<string> &visited) const;
    void dfs(const string &current, const string &end, map<string, bool> &visited, vector<string> &path, vector<vector<string>> &allPaths) const;
};

#endif

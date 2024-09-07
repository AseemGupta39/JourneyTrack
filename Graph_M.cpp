#include "Graph_M.h"

void Graph_M::addVertex(const string &vname) {
    // adding vertex(node or station in map) if not already exist 
    if (vertices.find(vname) == vertices.end()) {
        vertices[vname] = Vertex();
    }
}

void Graph_M::removeVertex(const string &vname) {
    // remove vertex(node or station in map) 
    vertices.erase(vname);

    // remove edges to the removed vertex/node from all other vertices/nodes
    for (auto &pair : vertices) {
        pair.second.neighbors.erase(vname);
    }
}

void Graph_M::addEdge(const string &vname1, const string &vname2, int weight) {
    vertices[vname1].neighbors[vname2] = weight;
    // if not directed then add edge from the other(vname2) vertex also
    if(!isDirected){
        vertices[vname2].neighbors[vname1] = weight;   
    }
}

void Graph_M::removeEdge(const string &vname1, const string &vname2) {
    vertices[vname1].neighbors.erase(vname2);

    // if not directed then remove edge from the other(vname2) vertex also
    if(!isDirected){
        vertices[vname2].neighbors.erase(vname1); 
    }
}

void Graph_M::displayMap() const {
    for (const auto &pair : vertices) {
        cout << "Vertex " << pair.first << " has edges to: ";
        for (const auto &nbr : pair.second.neighbors) {
            cout << nbr.first << " (weight: " << nbr.second << ") ";
        }
        cout << endl;
    }
}

void Graph_M::displayStations() const {
    cout << "Stations: ";
    for (const auto &pair : vertices) {
        cout << pair.first << " ";
    }
    cout << endl;
}

bool Graph_M::hasPath(const string &vname1, const string &vname2, map<string, bool> &processed) {
    // if either of the vname1 and vname2 are not in the vertices/node list
    if (vertices.find(vname1) == vertices.end() || vertices.find(vname2) == vertices.end()) {
        return false;
    }

    // if vname1 and vname2 are having a direct edge between them
    if (vertices[vname1].neighbors.find(vname2) != vertices[vname1].neighbors.end()) {
        return true;
    }

    processed[vname1] = true;
    // recursively call for its neighbors  
    for (const auto &nbr : vertices[vname1].neighbors) {
        if (processed.find(nbr.first) == processed.end() && hasPath(nbr.first, vname2, processed)) {
            return true;
        }
    }
    // if did not found in any case
    return false;
}

int Graph_M::dijkstra(const string &start, const string &end) const {
    // returns minimum distance between start and end nodes/vertices if exists else returns a very big distance number
    map<string, int> dist;
    set<string> visited;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    for (const auto &pair : vertices) {
        dist[pair.first] = numeric_limits<int>::max();
    }
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        if (visited.find(u) != visited.end()) {
            continue;
        }
        visited.insert(u);

        for (const auto &nbr : vertices.at(u).neighbors) {
            string v = nbr.first;
            int weight = nbr.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[end];
}

void Graph_M::dfs(const string &current, const string &end, map<string, bool> &visited, vector<string> &path, vector<vector<string>> &allPaths) const {
    visited[current] = true;
    path.push_back(current);

    if (current == end) {
        allPaths.push_back(path);
    } else {
        for (const auto &nbr : vertices.at(current).neighbors) {
            if (!visited[nbr.first]) {
                dfs(nbr.first, end, visited, path, allPaths);
            }
        }
    }

    path.pop_back();
    visited[current] = false;
}

vector<vector<string>> Graph_M::findAllPaths(const string &start, const string &end) const {
    vector<vector<string>> allPaths;
    map<string, bool> visited;
    vector<string> path;

    dfs(start, end, visited, path, allPaths);

    return allPaths;
}

vector<string> Graph_M::findShortestPath(const string &start, const string &end) const {
    map<string, int> dist;
    map<string, string> prev;
    set<string> visited;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    for (const auto &pair : vertices) {
        dist[pair.first] = numeric_limits<int>::max();
        prev[pair.first] = "";
    }
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        if (visited.find(u) != visited.end()) {
            continue;
        }
        visited.insert(u);

        for (const auto &nbr : vertices.at(u).neighbors) {
            string v = nbr.first;
            int weight = nbr.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    vector<string> path;
    for (string at = end; at != ""; at = prev[at]) {
        path.insert(path.begin(), at);
    }

    if (path.size() == 1 && path[0] != start) {
        path.clear(); // No path found
        cout << "No path found\n";
    }
    return path;
}
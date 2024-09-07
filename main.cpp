#include "Graph_M.h"

int main()
{
    bool isDirected;
    string userResponse;
    cout << "Enter Y/y to make the graph directed\nOr anything else to make it undirected" << endl;
    getline(cin, userResponse);

    isDirected = (userResponse == "Y" || userResponse == "y");
    
    Graph_M g(isDirected);
    
    bool running = true;
    int choice;
    string vname1, vname2;
    int value;
    map<string,bool> processed;

    while (running)
    {
        cout << "1. Add Vertex\n";
        cout << "2. Remove Vertex\n";
        cout << "3. Add Edge\n";
        cout << "4. Remove Edge\n";
        cout << "5. Display Map\n";
        cout << "6. Display Stations\n";
        cout << "7. Is Path Exist\n";
        cout << "8. Find Minimum Path\n";
        cout << "9. Find All Paths\n";
        cout << "10. Minimum Distance\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(); // To ignore the leftover newline character from cin

        switch (choice)
        {
        case 1:
            cout << "Enter vertex name to add: ";
            getline(cin, vname1);
            g.addVertex(vname1);
            cout << "Vertex added." << endl;
            break;

        case 2:
            cout << "Enter vertex name to remove: ";
            getline(cin, vname1);
            g.removeVertex(vname1);
            cout << "Vertex removed." << endl;
            break;

        case 3:
            cout << "Enter first vertex name: ";
            getline(cin, vname1);
            cout << "Enter second vertex name: ";
            getline(cin, vname2);
            cout << "Enter edge value: ";
            cin >> value;
            g.addEdge(vname1, vname2, value);
            cout << "Edge added." << endl;
            break;

        case 4:
            cout << "Enter first vertex name: ";
            getline(cin, vname1);
            cout << "Enter second vertex name: ";
            getline(cin, vname2);
            g.removeEdge(vname1, vname2);
            cout << "Edge removed." << endl;
            break;

        case 5:
            g.displayMap();
            break;

        case 6:
            g.displayStations();
            break;

        case 7:
            cout << "Enter start vertex: ";
            getline(cin, vname1);
            cout << "Enter end vertex: ";
            getline(cin, vname2);
            if(g.hasPath(vname1, vname2,processed)){
                cout << "Path exists between " << vname1 << " and " << vname2 << endl;
            }else{
                cout << "Path does not exist between " << vname1 << " and " << vname2 << endl;
            }
            processed.clear();

            break;
    
        case 8:
            cout << "Enter start vertex: ";
            getline(cin, vname1);
            cout << "Enter end vertex: ";
            getline(cin, vname2);

            for(auto &it:g.findShortestPath(vname1, vname2)) {
                cout << it << " ->";
            }cout << "End\n";
            break;
        
        case 9:
            cout << "Enter start vertex: ";
            getline(cin, vname1);
            cout << "Enter end vertex: ";
            getline(cin, vname2);

            for(auto& vec: g.findAllPaths(vname1, vname2)){
                for(auto &it:vec){
                    cout << it << " -> ";
                }cout << "End\n";
            }
            break;

        case 10:
            cout << "Enter start vertex: ";
            getline(cin, vname1);
            cout << "Enter end vertex: ";
            getline(cin, vname2);
            cout << "Minimum distance: " << g.dijkstra(vname1, vname2) << endl;
            break;

        case 11:
            running = false;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            choice = 12;
            break;
        }
    }

    return 0;
}
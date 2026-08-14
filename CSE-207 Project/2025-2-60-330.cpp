#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// Queue Class Design
template <typename T>
class MyQueue {
    vector<T> q_data;
public:
    void push(T val) { q_data.push_back(val); }
    void pop() { 
        if(!q_data.empty()) 
            q_data.erase(q_data.begin()); 
    }
    T front() { return q_data.front(); }
    bool empty() { return q_data.empty(); }
};

class CampusEmergencyFinder {
    map<string, vector<string> > adj; // Adjacency List

public:
    void addEdge(string u, string v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void findRoute(string assemblyPoint) {
        map<string, int> dist;
        map<string, string> parent;
        
  
        map<string, vector<string> >::iterator it;
        for (it = adj.begin(); it != adj.end(); it++) {
            dist[it->first] = -1;
            parent[it->first] = "";
        }

        MyQueue<string> q;
        dist[assemblyPoint] = 0;
        q.push(assemblyPoint);

        while (!q.empty()) {
            string u = q.front();
            q.pop();

            vector<string> neighbors = adj[u];
            for (int i = 0; i < neighbors.size(); i++) {
                string v = neighbors[i];
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

    
        cout << "\n--- Campus Emergency Route Report ---\n";
        map<string, int>::iterator it2;
        for (it2 = dist.begin(); it2 != dist.end(); it2++) {
            string point = it2->first;
            int d = it2->second;

            if (point == assemblyPoint) continue;

            cout << "Point: " << point << " | Reachable: ";
            if (d != -1) {
                cout << "Yes | Steps: " << d << " | Route: ";
                vector<string> path;
                string temp = point;
                while (temp != "") {
                    path.push_back(temp);
                    temp = parent[temp];
                }
                reverse(path.begin(), path.end()); 
                for (int i = 0; i < path.size(); i++) {
                    cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
                }
            } else {
                cout << "No | Steps: - | Route: No path exists";
            }
            cout << endl;
        }
    }
};

int main() {
    CampusEmergencyFinder campus;
    int n, m;
    cout << "Enter number of points and roads: ";
    cin >> n >> m;

    cout << "Enter " << m << " roads (Example: Library Gate):\n";
    for (int i = 0; i < m; i++) {
        string u, v;
        cin >> u >> v;
        campus.addEdge(u, v);
    }

    string assembly;
    cout << "ASSEMBLY: ";
    cin >> assembly;

    campus.findRoute(assembly);

    return 0;
}
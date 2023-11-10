#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

class Graph {
public:
    Graph(int vertices);
    void addEdge(int from, int to);
    vector<vector<int>> demucron();

private:
    int vertices;
    vector<vector<int>> adj;
    vector<bool> visited;
    stack<int> order;
    vector<int> currentLevel;

    void DFS(int v, bool saveState);
    void fillOrder(int v);
};

Graph::Graph(int vertices) {
    this->vertices = vertices;
    adj.resize(vertices);
    visited.assign(vertices, false);
}

void Graph::addEdge(int from, int to) {
    adj[from].push_back(to);
}

vector<vector<int>> Graph::demucron() {
    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            fillOrder(i);
        }
    }

    visited.assign(vertices, false);
    vector<vector<int>> levels;

    while (!order.empty()) {
        int v = order.top();
        order.pop();

        if (!visited[v]) {
            currentLevel.clear();
            DFS(v, true);
            levels.push_back(currentLevel);
        }
    }

    return levels;
}

void Graph::DFS(int v, bool saveState) {
    visited[v] = true;
    if (saveState) {
        currentLevel.push_back(v);
    }

    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            DFS(neighbor, saveState);
        }
    }
}

void Graph::fillOrder(int v) {
    visited[v] = true;

    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            fillOrder(neighbor);
        }
    }

    order.push(v);
}

int main() {
    int vertices = 8;
    Graph g(vertices);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 3);
    g.addEdge(5, 4);
    g.addEdge(6, 5);
    g.addEdge(7, 6);
    g.addEdge(6, 7);

    vector<vector<int>> levels = g.demucron();

    for (int i = 0; i < levels.size(); ++i) {
        cout << "Level " << i << ": ";
        for (int vertex : levels[i]) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return 0;
}

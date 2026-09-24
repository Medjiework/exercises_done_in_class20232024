#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
public:
    Graph();
    void InsertVertex(int v);
    void InsertEdge(int u, int v, int weight);
    bool IsEmpty();
    list<vector<int>> Adjacent_List(int u);
    void PrintAdjacentMatrix();
    void PrintAdjacentList();
    void DFS(int v);
    void BFS(int v);

private:
    int NumberVecterxs;
    int NumberEdges;
    list<int> vertexs;
    vector<vector<int>> adjacent_matrix;
    vector<list<vector<int>>> adjacent_list;
};

Graph::Graph() {
    NumberVecterxs = NumberEdges = 0;
}

bool Graph::IsEmpty() {
    return (vertexs.size() == 0);
}

list<vector<int>> Graph::Adjacent_List(int i) {
    return adjacent_list[i];
}

void Graph::InsertVertex(int v) {
    vertexs.push_back(v);
    NumberVecterxs++;
}

void Graph::InsertEdge(int u, int v, int weight = 1) {
    if (adjacent_matrix.size() == 0) {
        for (int i = 0; i < vertexs.size(); i++)
            adjacent_matrix.push_back(vector<int>(vertexs.size()));
    }
    if (adjacent_list.size() == 0) {
        for (int i = 0; i < vertexs.size(); i++)
            adjacent_list.push_back(list<vector<int>>());
    }

    adjacent_matrix[u][v] = adjacent_matrix[v][u] = weight;
    adjacent_list[u].push_back({ v, weight });
    adjacent_list[v].push_back({ u, weight });
    NumberEdges++;
}

void Graph::PrintAdjacentMatrix() {
    for (int i = 0; i < vertexs.size(); i++) {
        for (int j = 0; j < vertexs.size(); j++) {
            if (adjacent_matrix[i][j])
                cout << "(" << i << ", " << j << ", " << adjacent_matrix[i][j] << ")" << endl;
        }
    }
}

void Graph::PrintAdjacentList() {
    for (int i = 0; i < vertexs.size(); i++) {
        for (auto it : adjacent_list[i]) {
            cout << "(" << i << ", " << it[0] << ", " << it[1] << ")" << endl;
        }
    }
}

void Graph::DFS(int v) {
    bool* visited = new bool[NumberVecterxs];
    fill(visited, visited + NumberVecterxs, false);

    list<int> stack;

    stack.push_back(v);
    visited[v] = true;

    while (!stack.empty()) {
        v = stack.back();
        stack.pop_back();

        cout << "*" << v << endl;

        for (auto it : adjacent_list[v]) {
            if (!visited[it[0]]) {
                stack.push_back(it[0]);
                visited[it[0]] = true;
            }
        }
    }

    delete[] visited;
}

void Graph::BFS(int v) {
    bool* visited = new bool[NumberVecterxs];
    fill(visited, visited + NumberVecterxs, false);
    visited[v] = true;
    list<int> q;
    q.push_back(v);
    while (!q.empty()) {
        v = q.front();
        cout << "*" << v << endl;
        q.pop_front();
        for (auto it : adjacent_list[v]) {
            if (!visited[it[0]]) {
                q.push_back(it[0]);
                visited[it[0]] = true;
            }
        }
    }
    delete[] visited;
}

int main() {
    int u, v;
    int weight;
    int N; // number of input vertices
    int M; // number of input edges

    Graph g1;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> u;
        g1.InsertVertex(u);
    }
    for (int j = 0; j < M; j++) {
        cin >> u >> v;
        g1.InsertEdge(u, v);
    }
    g1.PrintAdjacentMatrix();
    g1.PrintAdjacentList();

    cout << "DFS from vertex 0 for Graph 1:" << endl;
    g1.DFS(0);
    cout << "BFS from vertex 0 for Graph 1:" << endl;
    g1.BFS(0);

    Graph g2;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> u;
        g2.InsertVertex(u);
    }
    for (int j = 0; j < M; j++) {
        cin >> u >> v >> weight;
        g2.InsertEdge(u, v, weight);
    }
    g2.PrintAdjacentMatrix();
    g2.PrintAdjacentList();

    cout << "DFS from vertex 0 for Graph 2:" << endl;
    g2.DFS(0);
    cout << "BFS from vertex 0 for Graph 2:" << endl;
    g2.BFS(0);

    return 0;
}

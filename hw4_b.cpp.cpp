#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

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
    void Kruskal();

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
            adjacent_matrix.push_back(vector<int>(vertexs.size(), 0));
    }
    if (adjacent_list.size() == 0) {
        for (int i = 0; i < vertexs.size(); i++)
            adjacent_list.push_back(list<vector<int>>());
    }

    adjacent_matrix[u][v] = adjacent_matrix[v][u] = weight;
    adjacent_list[u].push_back({v, weight});
    adjacent_list[v].push_back({u, weight});
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

        cout << "*\n" << v << endl;

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
        cout << "*\n" << v << endl;
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

struct Edge {
    int src, dest, weight;
};

bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

class DisjointSet {
public:
    DisjointSet(int n);
    int find(int u);
    void unite(int u, int v);

private:
    vector<int> parent, rank;
};

DisjointSet::DisjointSet(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i)
        parent[i] = i;
}

int DisjointSet::find(int u) {
    if (u != parent[u])
        parent[u] = find(parent[u]);
    return parent[u];
}

void DisjointSet::unite(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);
    if (rootU != rootV) {
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

void Graph::Kruskal() {
    vector<Edge> edges;
    for (int i = 0; i < vertexs.size(); ++i) {
        for (int j = 0; j < vertexs.size(); ++j) {
            if (adjacent_matrix[i][j] != 0 && i < j) {
                edges.push_back({i, j, adjacent_matrix[i][j]});
            }
        }
    }

    sort(edges.begin(), edges.end(), compareEdges); // Sorting edges by weight

    DisjointSet ds(NumberVecterxs);
    vector<Edge> mst;

    // Applying Kruskal's algorithm to select the edges of the MST
    for (const Edge& e : edges) {
        if (ds.find(e.src) != ds.find(e.dest)) {
            mst.push_back(e);
            ds.unite(e.src, e.dest);
        }
    }

    // Sorting the MST edges lexicographically (first by src, then by dest)
    sort(mst.begin(), mst.end(), [](const Edge& e1, const Edge& e2) {
        if (e1.src != e2.src) return e1.src < e2.src;
        return e1.dest < e2.dest;
    });

    // Output the result with asterisk before each edge in the desired format *u v
    for (const Edge& e : mst) {
        // Print * followed by the edge in the format *01, *02, etc.
        cout << "*" << e.src << e.dest << endl;
    }
}

int main() {
    int u, v;
    int weight;
    int N; // number of input vertices
    int M; // number of input edges

    Graph g1;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        g1.InsertVertex(i);
    }
    for (int j = 0; j < M; j++) {
        cin >> u >> v >> weight;
        g1.InsertEdge(u, v, weight);
    }

    
    g1.Kruskal();

    return 0;
}

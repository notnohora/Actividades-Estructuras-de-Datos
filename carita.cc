#include <iostream>
#include <vector>
#include <limits>

using namespace std;
const int INF = numeric_limits<int>::max();

class Graph {
private:
    vector<vector<int>> adj_matrix;

public:
    Graph(int n, const vector<vector<int>>& adj_list) {
        adj_matrix = vector<vector<int>>(n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            adj_matrix[i][i] = 0;
        }
        for (const auto& edge : adj_list) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            if (u != v) {  
                adj_matrix[u][v] = w;
            }
        }
    }

    Graph(const vector<vector<int>>& matrix) {
        adj_matrix = matrix;
    }
    
    int size() const {
        return adj_matrix.size();
    }

    vector<int>& operator[](int i) {
        return adj_matrix[i];
    }

    const vector<int>& operator[](int i) const {
        return adj_matrix[i];
    }
    
};

Graph ProductMM(const Graph& g) {
    int n = g.size();
    Graph C = g;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (C[i][k] != INF && C[k][j] != INF) {
                    C[i][j] = min(C[i][j], C[i][k] + C[k][j]);
                }
            }
        }
    }

    return C;
}
//Print Functions (not relevant)
void printAdjacencyList(Graph& g, int n) {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < n; j++) {
            if (g[i][j] != INF) {
                cout << j << " ";
            }
        }
        cout << "\n";
    }
}

void printMatrix(Graph& g, int n) {
    for (int row = 0; row < n; row++) {
        cout << "    ";
        for (int col = 0; col < n; col++) {
            if(g[row][col] != INF && g[row][col] != 0){
            cout << g[row][col] << (col < n - 1 ? " " : "");
            }
            else{
                cout << "." << (col < n - 1 ? " " : "");
            }
        }
        cout << "\n";
    }
}



int main() {
    int numberOfNodes= 5;
    vector<vector<int>> adj_List = {
    {0, 1, 2}, {0, 2, 6}, {0, 3, 7},
    {1, 3, 3},{1, 4, 6},
    {2, 4, 1},
    {3, 4, 5}
};
    Graph graph(numberOfNodes, adj_List);
    printAdjacencyList(graph, numberOfNodes);
    cout << "\nAdjacency Matrix:\nA =\n";
    printMatrix(graph, numberOfNodes);
    Graph C = ProductMM(graph);
    cout << "\nMinimum Paths Matrix:\nC =\n";
    printMatrix(C, numberOfNodes);
    return 0;
}
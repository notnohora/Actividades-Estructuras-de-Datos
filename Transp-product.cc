#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<int>> adj_matrix;

public:
    Graph(int n, const vector<vector<int>>& adj_list) {
        adj_matrix = vector<vector<int>>(n, vector<int>(n, 0));
        for (const auto& edge : adj_list) {
            int u = edge[0];
            int v = edge[1];
            if (u != v) {  
                adj_matrix[u][v] = 1;
                adj_matrix[v][u] = 1; 
            }
        }
    }

    Graph(const vector<vector<int>>& matrix) {
        adj_matrix = matrix;
    }

    vector<int>& operator[](int i) {
        return adj_matrix[i];
    }

    const vector<int>& operator[](int i) const {
        return adj_matrix[i];
    }

    vector<vector<int>> TransposedMatrix() {
        int n = adj_matrix.size();
        int m = adj_matrix[0].size();
        vector<vector<int>> t(m, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                t[j][i] = adj_matrix[i][j];
            }
        }
        return t;
    }

    vector<int> ProductMV(int index) {
        int n = adj_matrix.size();
        int m = adj_matrix[0].size();
        vector<int> v(m, 0);
        v[index] = 1;

        vector<int> result(n, 0);
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                result[row] += adj_matrix[row][col] * v[col];
            }
        }
        return result;
    }
};

//Print Funtions (not relevant)
void printAdjacencyList(Graph& g, int n) {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 1) {
                cout << j << " ";
            }
        }
        cout << "\n";
    }
}

void printAdjacencyMatrix(Graph& g, int n) {
    cout << "\nAdjacency Matrix:\nA = ";
    for (int row = 0; row < n; row++) {
        cout << (row > 0 ? "    " : "");
        for (int col = 0; col < n; col++) {
            cout << g[row][col] << (col < n - 1 ? " " : "");
        }
        cout << "\n";
    }
}

void printTransposedMatrix(Graph& g, int n) {
    cout << "\nTransposed Adjacency Matrix:\nA^T = ";
    for (int row = 0; row < n; row++) {
        cout << (row > 0 ? "      " : "");
        for (int col = 0; col < n; col++) {
            cout << g[row][col] << (col < n - 1 ? " " : "");
        }
        cout << "\n";
    }
}

void printProductResult(const vector<int>& result, int index) {
    cout << "\nMatrix product * unit vector at the indicated position returns the connections of the node corresponding to that index:\n";
    cout << "Result: [ ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << "]\n";

    cout << "Nodes connected to node " << index << ": ";
    bool first = true;
    for (int i = 0; i < result.size(); i++) {
        if (result[i] == 1) {
            if (!first) cout << ", ";
            cout << i;
            first = false;
        }
    }
    cout << "\n";
}


int main() {
    int numberOfNodes= 10;
    vector<vector<int>> adj_List = {
    {0, 1}, {0, 2}, {0, 3},
    {1, 2}, {1, 4}, {1, 7},
    {2, 3}, {2, 5}, {2, 8},
    {3, 6}, {3, 9},
    {4, 5}, {4, 7},
    {5, 6}, {5, 8},
    {6, 9},
    {7, 8},
    {8, 9}
};
    Graph graph(numberOfNodes, adj_List);
    Graph transposedMatrix(graph.TransposedMatrix());
    int index = 1;
    vector<int> vector = transposedMatrix.ProductMV(index);
    printAdjacencyList(graph, numberOfNodes);
    printAdjacencyMatrix(graph, numberOfNodes);
    printTransposedMatrix(transposedMatrix, numberOfNodes);
    printProductResult(vector, index);
    return 0;
}

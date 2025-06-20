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
                //adj_matrix[v][u] = 1; //para no dirigidos
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

    Graph ProductMM(const Graph& B) const {
        int n = adj_matrix.size();
        vector<vector<int>> result(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                for (int k = 0; k < n; ++k){
                    result[i][j] += adj_matrix[i][k] * B[k][j];
                }
            }
        }
        return Graph(result);
    }

Graph OrFunction(const Graph& B) const {
    int n = adj_matrix.size();
    vector<vector<int>> result(n, vector<int>(n));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            result[i][j] = adj_matrix[i][j] || B[i][j];
        }
    }
    return Graph(result);
}
Graph AndFunction(const Graph& B) const {
    int n = adj_matrix.size();
    vector<vector<int>> result(n, vector<int>(n));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            result[i][j] = adj_matrix[i][j] && B[i][j];
        }
    }
    return Graph(result);
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
};

//Print Functions (not relevant)
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

void printMatrix(Graph& g, int n) {
    for (int row = 0; row < n; row++) {
        cout << "    ";
        for (int col = 0; col < n; col++) {
            cout << g[row][col] << (col < n - 1 ? " " : "");
        }
        cout << "\n";
    }
}


Graph IvA(const Graph& A, int steps) {
    Graph current = A;
    Graph C = A; 
    Graph power = A;

    for (int i = 1; i < steps; ++i) {
        power = power.ProductMM(A);    // A^n
        C = C.OrFunction(power);       // C = C ∨ A^n
        cout << "\nA^" << i + 1 << ":\n";
        printMatrix(power, A.size());
    }

    return C;
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
    printAdjacencyList(graph, numberOfNodes);
    cout << "\nAdjacency Matrix:\nA =\n";
    printMatrix(graph, numberOfNodes);

    vector<vector<int>> identity(numberOfNodes, vector<int>(numberOfNodes, 0));
    for (int i = 0; i < numberOfNodes; ++i){
        identity[i][i] = 1;
    }
    Graph C(identity);
    C = C.OrFunction(graph);

    Graph result = IvA(graph, numberOfNodes); 
    C = C.OrFunction(result);
    Graph t(C);
    t.TransposedMatrix();
    C = C.AndFunction(t);
    cout << "\nMatriz C:\n";
    printMatrix(C, numberOfNodes);

    return 0;
}

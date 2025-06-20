#include <iostream>
#include <vector>
#include <limits>
#include <random>
using namespace std;

class Graph
{
private:
    vector<vector<int>> adj_matrix;

public:
    Graph(int n)
    {
        adj_matrix = vector<vector<int>>(n, vector<int>(n, -1));
    }

    void add_edge(int u, int v, int weight)
    {
        if (u == v)
            return; // evitar bucles
        adj_matrix[u][v] = weight;
        adj_matrix[v][u] = weight;
    }

    bool has_edge(int u, int v)
    {
        return adj_matrix[u][v] != -1;
    }

  void print()
{
    cout << "Representación de la matriz de conexiones con pesos:\n";
    int n = adj_matrix.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adj_matrix[i][j] == -1)
                cout << "- ";
            else
                cout << adj_matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void prim()
{
    int n = adj_matrix.size();
    vector<int> parent(n, -1);
    vector<int> key(n, numeric_limits<int>::max());
    vector<bool> inMST(n, false);

    key[0] = 0;

    for (int count = 0; count < n - 1; ++count)
    {
        int u = -1;
        int min_key = numeric_limits<int>::max();
        for (int v = 0; v < n; v++)
        {
            if (!inMST[v] && key[v] < min_key)
            {
                min_key = key[v];
                u = v;
            }
        }

        if (u == -1)
            break;

        inMST[u] = true;

        for (int v = 0; v < n; v++)
        {
            if (adj_matrix[u][v] != -1 && !inMST[v] && adj_matrix[u][v] < key[v])
            {
                key[v] = adj_matrix[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "\nConexiones seleccionadas para el Árbol de Expansión Mínima (usando Prim):\n";
    int total_weight = 0;
    for (int i = 1; i < n; ++i)
    {
        if (parent[i] != -1)
        {
            cout << "Nodo " << parent[i] << " conectado con Nodo " << i
                 << " (costo: " << adj_matrix[i][parent[i]] << ")\n";
            total_weight += adj_matrix[i][parent[i]];
        }
    }
    cout << "Costo total acumulado del árbol generado: " << total_weight << "\n";
}
};


int main()
{
    int n = 10;
    Graph g(n);

    // Generador de aristas aleatorias (con peso entre 1 y 20)
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> node_dist(0, n - 1);
    uniform_int_distribution<> weight_dist(1, 20);

    int edges_added = 0;
    while (edges_added < 20)
    {
        int u = node_dist(gen);
        int v = node_dist(gen);
        int w = weight_dist(gen);
        if (u != v && !g.has_edge(u, v))
        {
            g.add_edge(u, v, w);
            edges_added++;
        }
    }

    g.print();
    g.prim();

    return 0;
}

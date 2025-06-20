#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Point{

public:
    vector<double> features;
    int clusterId;

    Point(const vector<double> &f){
        features = f;
        clusterId= -1;
    }
};

class K_Means{

private:

    int maxIterations;
    int k_;
    vector<vector<double>> centroids;

    double euclideanDistance(const vector<double> &a, const vector<double> &b){
        double sum = 0.0;
        for (auto i =  0; i < a.size(); ++i)
            sum += pow(a[i] - b[i], 2);
        return sqrt(sum);
    }

    void assignClusters(vector<Point> &points){
        for (auto &point : points){
            double minDist= numeric_limits<double>::max();
            int bestCluster= -1;
            for (int i = 0; i < k_; ++i){
                double dist = euclideanDistance(point.features, centroids[i]);
                if (dist < minDist){
                    minDist = dist;
                    bestCluster = i;
                }
            }
           point.clusterId = bestCluster;
        }
    }

    void updateCentroids(vector<Point> &points){
        vector<vector<double>> new_centroids(k_, vector<double>(points[0].features.size(), 0.0));
        vector<int> counts(k_, 0);

        for (const auto &point : points){
            for (auto j = 0; j < point.features.size(); ++j){
                new_centroids[point.clusterId][j] += point.features[j];
            }
            counts[point.clusterId]++;
        }

        for (int i = 0; i < k_; ++i){
            if (counts[i] == 0)
                continue;
            for (auto j = 0; j < new_centroids[i].size(); ++j){
                new_centroids[i][j] /= counts[i];
            }
        }

        centroids = new_centroids;
    }

public:

    K_Means(int k, int max){
        k_ = k;
        maxIterations = max;
    }

    void train(vector<Point> &points){
        centroids.clear();
        srand(time(0));
        for (int i = 0; i < k_; ++i){
            int index = rand() % points.size();
            centroids.push_back(points[index].features);
        }

        for (int iter = 0; iter < maxIterations; ++iter){
            assignClusters(points);
            updateCentroids(points);
        }
    }

    void printResults(const vector<Point> &points){
        vector<int> clusterCounts(k_, 0);

        for (const auto &point : points){
             clusterCounts[point.clusterId]++;

         }

        cout << "\nResumen por Clúster:\n";
        for (int i = 0; i < k_; ++i){
            cout << "Clúster " << i << ": " << clusterCounts[i] << " elementos\n";
        }

        cout << "\nCentroides Finales:\n";
        for (int i = 0; i < k_; ++i){
            cout << "Clúster " << i << " centroide: ";
            for (double val : centroids[i])
                cout << val << " ";
            cout << endl;
        }
    }
};

vector<Point> LoadDataSet(const string &fileName){
    ifstream inputFile(fileName);
    vector<Point> points;
    string row;

    bool isFirstLine = true;

    while (getline(inputFile, row)){
        if (isFirstLine){
            isFirstLine = false;  // Skip the header
            continue;
        }

        vector<double> extractedFeatures;
        stringstream rowStream(row);
        string value;
        int columnIndex = 0;

        while (getline(rowStream, value, '\t')){
            // Only extract relevant columns
            if (columnIndex == 4 || (columnIndex >= 9 && columnIndex <= 14)){
                try {
                    extractedFeatures.push_back(value.empty() ? 0.0 : stod(value));
                } catch (...) {
                    extractedFeatures.push_back(0.0); // Handle conversion error
                }
            }
            columnIndex++;
        }

        if (!extractedFeatures.empty()){
            points.push_back(Point(extractedFeatures));
        }
    }

    return points;
}


int main(){
    vector<Point> dataSet = LoadDataSet("Data.txt");
    if (dataSet.empty()){
        cout << "Error uploading file.\n";
        return 0;
    }
    K_Means kMeans(5, 100);
    kMeans.train(dataSet);
    kMeans.printResults(dataSet);

    return 0;
}

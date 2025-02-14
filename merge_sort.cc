#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

void Merge(vector<int>* v, int begin, int middle, int end) {
    vector<int> firstVector;
    int i = begin, j = middle + 1, k = 0;

    while (i <= middle && j <= end) {
        if (v->at(i) <= v->at(j)) {
            firstVector.push_back(v->at(i));
            k += 1;
            i += 1;
        } else {
            firstVector.push_back(v->at(j));
            k += 1;
            j += 1;
        }
    }
    while (i <= middle) {
        firstVector.push_back(v->at(i));
        k += 1;
        i += 1;
    }
    while (j <= end) {
        firstVector.push_back(v->at(j));
        k += 1;
        j += 1;
    }

    for (int i = begin; i <= end; i++) {
        v->at(i) = firstVector.at(i - begin);
    }
}

void MergeSort(vector<int>* vector, int begin, int end) {
    if (begin < end) {
        int middle = (begin + end) / 2;
        MergeSort(vector, begin, middle);
        MergeSort(vector, middle + 1, end);
        Merge(vector, begin, middle, end);
    }
}

void PrintVectors(vector<int>* vector, int i) {
    if (i < vector->size()) {
        cout << " " << vector->at(i);
        PrintVectors(vector, i + 1);
    }
}

void GenerateRandomNumbers(vector<int>* vector, int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100);

    for (int i = 0; i < size; i++) {
        vector->push_back(distrib(gen));
    }
}

/*
void GenerateRandomNumbers(vector<int>* vector, int i, int size) {
    if (i < size) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 100);
        vector->push_back(distrib(gen));
        GenerateRandomNumbers(vector, i + 1, size);
    }
}
*/

int main() {
    cout << "MERGE SORT IMPLEMENTATION" << endl;
    vector<int> a;
    int sizeVector = 10;
    GenerateRandomNumbers(&a, sizeVector);
    cout << "Vector generated with random numbers:" << endl;
    PrintVectors(&a, 0);
    MergeSort(&a, 0, sizeVector - 1);
    cout << " " << endl << "Vector after being sorted:" << endl;
    PrintVectors(&a, 0);
    cout << " " << endl;
    return 0;
}

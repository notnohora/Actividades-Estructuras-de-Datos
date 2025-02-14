#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

int Partitions(vector<int>* v, int begin, int end){
    int pIndex = (begin + end) / 2;
    int pivot = v->at(pIndex);
    swap(v->at(pIndex), v->at(end)); 
    int i = begin-1;
    
    for (int j = begin; j < end; j++) {
        if (v->at(j) <= pivot) {
            i++;
            swap(v->at(i), v->at(j));
        } 
    }
    i++;
    swap(v->at(i), v->at(end)); 
    return i;
}

void QuickSort(vector<int>* v, int begin, int end){
    if(begin < end){
       int pIndex = Partitions(v, begin, end);
       QuickSort(v, begin, pIndex-1);
       QuickSort(v, pIndex+1, end);
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
    cout << "MIDDLE PIVOT QUICK SORT IMPLEMENTATION" << endl;
    vector<int> a;
    int sizeVector = 10000;
    GenerateRandomNumbers(&a, sizeVector);
    cout << "Vector generated with random numbers:" << endl;
    PrintVectors(&a, 0);
    QuickSort(&a,0,sizeVector-1);
    cout << " " << endl << "Vector after being sorted:" << endl;
    PrintVectors(&a, 0);
    cout << " " << endl;
    return 0;
}
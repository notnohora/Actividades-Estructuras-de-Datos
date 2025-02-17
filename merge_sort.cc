#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;


void Merge(vector<long>* v, long begin, long middle, long end) {
    vector<long> firstVector;
    long i = begin, j = middle + 1, k = 0;

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

void MergeSort(vector<long>* vector, long begin, long end) {
    if (begin < end) {
        long middle = (begin + end) / 2;
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

void GenerateRandomNumbers(vector<long>* vec, long size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100000);

    for (long i = 0; i < size; i++) {
        vec->push_back(distrib(gen));
    }
}

/*
Recursive Version:

void PrintVectors(vector<int>* vector, int i) {
    if (i < vector->size()) {
        cout << " " << vector->at(i);
        PrintVectors(vector, i + 1);
    }
}

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
    vector<long> a, b;
    vector<long > t;
    GenerateRandomNumbers(&a, 100000000);
    b = a;
    int i = 0;
    while(i < 10){
    //cout << "Vector generated with random numbers:" << endl;
    //PrintVectors(&a);
    
    auto start = steady_clock::now();  
        MergeSort(&a, 0, a.size() - 1);
        auto end = steady_clock::now();

        auto duration = duration_cast<nanoseconds>(end - start);
        long long nanoseconds = duration.count();

        if (nanoseconds < 0) {
            cerr << "Error: negative value. " << i << endl;
            nanoseconds = 0; 
        }

        t.push_back(nanoseconds);

    a = b;
    /*
    for(int i = 0; i < b.size(); i++){
        a.pop_back();
    }
    for(int i = 0; i < b.size(); i++){
        a.push_back(b.at(i));
    }
        */
    i++;
   }
   for(int i = 0; i < 10; i++){
    cout << i << ". " << t.at(i)<< endl;
   }
    cout << " " << endl;
    return 0;
}

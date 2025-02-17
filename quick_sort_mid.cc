#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

int Partitions(vector<long >* v, long begin, long end){
    //long long pIndex = (begin + end) / 2; //middle
    long pivot = v->at(end);
    //long long pivot = v->at(pIndex); // middle
    //swap(v->at(pIndex), v->at(end)); // middle
    long i = begin-1;
    
    for (long  j = begin; j < end; j++) {
        if (v->at(j) <= pivot) {
            i++;
            swap(v->at(i), v->at(j));
        } 
    }
    i++;
    swap(v->at(i), v->at(end)); 
    return i;
}

void QuickSort(vector<long>* v, long begin, long end){
    if(begin < end){
       long pIndex = Partitions(v, begin, end);
       QuickSort(v, begin, pIndex-1);
       QuickSort(v, pIndex+1, end);
    }
}

void PrintVectors(vector<long>* vec) {
    for (long i = 0; i < vec->size(); i++) {
        cout << " " << vec->at(i);
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
    
    cout << "QUICK SORT IMPLEMENTATION" << endl;
    vector<long> a, b;
    vector<long > t;
    GenerateRandomNumbers(&a, 10000);
    b = a;
    int i = 0;
    while(i < 10){
    //cout << "Vector generated with random numbers:" << endl;
    //PrintVectors(&a);
    
    auto start = steady_clock::now();  
        QuickSort(&a, 0, a.size() - 1);
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


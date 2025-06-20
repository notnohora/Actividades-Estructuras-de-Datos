#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cassert>

using namespace std;
template <typename T>

class Vector {

    private:
    T* storage_;
    unsigned int capacity_;
    unsigned int size_;

    private:
    void resize() {
        unsigned int capacity2 = capacity_ * 1.5;
        T* storage2 = new T[capacity2];
        for ( unsigned int i = 0; i < size_; i++) {
            storage2[i] = storage_[i];
        }
        delete [] storage_;
        storage_ = storage2;
        capacity_ = capacity2;
    }

    public:
    Vector(unsigned int numberOfElements) {
        capacity_ = numberOfElements;
        storage_ = new T[capacity_];
        size_ = 0;
    }

    Vector() {
        capacity_ = 5;
        storage_ = new T[capacity_];
        size_ = 0;
    }
    
    unsigned int capacity() const {
        return capacity_;
    }

    unsigned int size() const {
        return size_;
    }
    bool empty(){
        return size_ == 0;
    }
    const T& at(unsigned int position) const {
        assert(position >= 0 && position < size_);
        return storage_[position];
    }

    void push_back(const T& element) {
        if (size_ == capacity_){
            resize();
        }
        storage_[size_] = element;
        size_++;
    }


    void print(){
        for (unsigned int i = 0; i < size_; i++){
            cout << " " << storage_[i];
        }
        cout << endl;
    }

};

template <typename T>
Vector<T> MergeSort(Vector<T>* vector1, Vector<T>* vector2,int begin ,int size1, int size2){
    Vector<T> vector;
    long i = begin, j = 0;

    while (i <= size1 && j <= size2) {
        if (vector1->at(i) <= vector2->at(j)) {
            vector.push_back(vector1->at(i));
            i += 1;
        } else {
            vector.push_back(vector2->at(j));
            j += 1;
        }
    }
    while (i <= size1) {
        vector.push_back(vector1->at(i));
        i += 1;
    }
    while (j <= size2) {
        vector.push_back(vector2->at(j));
        j += 1;
    }
    return vector;
}

template <typename T>
Vector<T> MergeSortedVectors( Vector<T> vector1, Vector<T> vector2){
    return MergeSort(&vector1, &vector2, 0, vector1.size()-1,vector2.size()-1);
}

int main(){
    Vector<int> vector1, vector2, vector3, vector4, vector5, vector6, vector7, vector8; 
    Vector<int> mergedVector = MergeSortedVectors(vector1, vector2);
    mergedVector.print();
    vector1.push_back(1);
    vector1.push_back(3);
    vector1.push_back(5);
    vector2.push_back(2);
    vector2.push_back(4);
    vector2.push_back(6);
    Vector<int> mergedVector1 = MergeSortedVectors(vector1, vector2);
    mergedVector1.print(); // Expected: {1, 2, 3, 4, 5, 6}
    vector3.push_back(1);
    vector3.push_back(2);
    vector3.push_back(3);
    Vector<int> mergedVector2 = MergeSortedVectors(vector3, vector4);
    mergedVector2.print(); // Expected: {1, 2, 3}
    vector6.push_back(4);
    vector6.push_back(5);
    vector6.push_back(6);
    Vector<int> mergedVector3 = MergeSortedVectors(vector5, vector6);
    mergedVector3.print(); // Expected: {4, 5, 6}
    vector7.push_back(1);
    vector7.push_back(1);
    vector7.push_back(1);
    vector7.push_back(1);
    vector8.push_back(1);
    vector8.push_back(1);
    vector8.push_back(1);
    vector8.push_back(1);
    Vector<int> mergedVector4 = MergeSortedVectors(vector7, vector8);
    mergedVector4.print(); // Expected: {1,1,1,1,1,1,1,1}
return 0;
}
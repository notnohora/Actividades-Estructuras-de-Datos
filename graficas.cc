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
    void resize( float typeOfPolice) { 
      unsigned int capacity2 = capacity_;  

        if (typeOfPolice == 1) {
            capacity2 = capacity_ + 1;  
        } else if (typeOfPolice == 2) {
            capacity2 = capacity_ + 2;  
        } else if (typeOfPolice == 3) {
            capacity2 = static_cast<unsigned int>(capacity_ * 1.5);  
        } else if (typeOfPolice == 4) {
            capacity2 = static_cast<unsigned int>(capacity_ * 1.7); 
        } else if (typeOfPolice == 5) {
            capacity2 = static_cast<unsigned int>(capacity_ * 2); 
        }
        
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
    
    void push_back(const T& element, float typeOfPolice) {
        if (size_ == capacity_){
            resize(typeOfPolice);
        }
        storage_[size_] = element;
        size_++;
    }

};

template <typename T>
void DymanicResizing (const unsigned int numOfelements, Vector<T>& vector, float typeOfPolice){
    int times = numOfelements / 1000;

    ofstream file("data.txt");

    if (!file) {
        cerr << "Error opening file"<< endl;
        return;
    }

    for(unsigned int i = 0; i < times; i++){
        int j = 0;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 1000);

        while(j < 1000){
            int random = distrib(gen);
            vector.push_back(random, typeOfPolice);
            j++;
        }
        file << i << " " << vector.capacity() << " " << vector.size() << endl;
    }  
    file.close();
}

int main() {
    Vector<int> myVector1, myVector2, myVector3, myVector4;
    //DymanicResizing(100000, myVector1, 1);
    //DymanicResizing(100000, myVector2, 2);
    //DymanicResizing(100000, myVector3, 3);
    //DymanicResizing(100000, myVector4, 4);
    DymanicResizing(100000, myVector4, 5);

    return 0;
}
#include <iostream>
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
    
    unsigned int capacity() {
        return capacity_;
    }

    unsigned int size() {
        return size_;
    }

    const T& at(unsigned int position) const {
        assert(position >= 0 && position < size_);
        return storage_[position];
    }

    void push_front(const T& element){
        if (size_ == capacity_){
            resize();
        }

        for (unsigned int i = size_; i > 0; i--){
            swap(storage_[i], storage_[i - 1]);
        }
        storage_[0] = element;
        size_++;
    }

    void push_back(const T& element){
        if (size_ == capacity_){
            resize();
        }
        storage_[size_] = element;
        size_++;
    }

    void pop_front(){
        if(size_ == 0) return;
        for (unsigned int i = 0; i < size_ - 1; i++){
            storage_[i] = storage_[i + 1];
        }
        size_--;
    }

    void pop_back(){
        if(size_ == 0) return;
        size_--;
    }

    void print(){
        for (unsigned int i = 0; i < size_; i++){
            cout << " " << storage_[i];
        }
        cout << endl;
    }

    void insert(unsigned int index,T element) {
        assert(index < size_);
        if(index == 0){
            push_front(element);
            return;
        }

        if (index == size_ - 1){
            push_back(element);
            return;
        }
        
        if (size_ == capacity_){
            resize();
        }

        for (unsigned int i = size_; i > index; i--){
            storage_[i] = storage_[i-1];
        }
        storage_[index] = element;
        size_++;
    }

    void erase(unsigned int index){
        assert(index >= 0 && index < size_);
    
        if(index == 0){
            pop_front();
            return;
        }
    
        if(index == size_ - 1){
            pop_back();
            return;
        }
    
        for(unsigned int i = index; i < size_ ; i++){
            storage_[i] = storage_[i + 1];
        }
        size_--;
    } 
};

int main() {
    Vector<int> MyVector;
    //push back
    MyVector.push_back(15);
    
    
    return 0;
}
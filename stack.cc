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
    
    unsigned int capacity() const {
        return capacity_;
    }

    unsigned int size() const {
        return size_;
    }
    bool empty(){
        return size_ == 0;
    }
    void push_back(const T& element) {
        if (size_ == capacity_){
            resize();
        }
        storage_[size_] = element;
        size_++;
    }
    const T& at(unsigned int position) const {
        assert(position >= 0 && position < size_);
        return storage_[position];
    }
    void pop_back(){
        assert(size_ > 0);
        size_--;
    }
    void print(){
        for (unsigned int i = 0; i < size_; i++){
            cout << " " << storage_[i];
        }
        cout << endl;
    }

};

template <typename T>
class Stack{
    private:
    
    Vector<T> vector_;
    unsigned int size_;
    public:
    Stack(){
    }
    bool empty(){
        return vector_.size() == 0;
    }
    void push(const T& elem){
            vector_.push_back(elem);
    }
    T top(){
        assert(!vector_.empty());
        return vector_.at(vector_.size()-1);
    }
    void pop(){
        assert(!vector_.empty());
        vector_.pop_back();
    }
    void print() {
        assert(!vector_.empty());
        vector_.print();
    }
    unsigned int size(){
        return vector_.size();
    }
      
};

int main(){
        Stack<int> Mystack;
        cout << "empty: " << Mystack.empty() << endl; 
        //Mystack.push(10);
        //Mystack.push(20);
        //Mystack.push(30);
        //Mystack.print();  
    
        //cout << "Top: " << Mystack.top() << endl; // Debería imprimir: 30
        cout << "empty: " << Mystack.empty() << endl; 
        //Mystack.pop();
        Mystack.print();  // Debería imprimir: 10 20
        cout << "size: " << Mystack.size() << endl; 
    
        return 0;
}
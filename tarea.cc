#include <iostream>
#include <cassert>

using namespace std;
template <typename T>

class Vector {

    private:
    T* storage_;
    unsigned int capacity_;
    unsigned int size_;

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

    public:
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
    void push_front(const T& element) {
        if (size_ == capacity_)
        {
            resize();
        }

        for (unsigned int i = size_; i > 0; i--) {
            swap(storage_[i], storage_[i - 1]);
        }
        storage_[0] = element;
        size_++;
    }

    void push_back(const T& element) {
        if (size_ == capacity_) {
            resize();
        }
        storage_[size_] = element;
        size_++;
    }

    void pop_front() {
        if(size_ == 0) return;
        for (unsigned int i = 0; i < size_ - 1; i++) {
            storage_[i] = storage_[i + 1];
        }
        size_--;
    }

    void print() {
        for (unsigned int i = 0; i < size_; i++) {
            cout << " " << storage_[i];
        }
        cout << endl;
    }

    void insert(unsigned int position,T element) {
        assert(position < size_);

        if(position == 0) {
            push_front(element);
            return;
        }

        if (position == size_ - 1)
        {
            push_back(element);
            return;
        }
        
        if (size_ == capacity_)
        {
            resize();
        }

        for (unsigned int i = size_; i > position; i--)
        {
            storage_[i] = storage_[i-1];
        }
        
        storage_[position] = element;
        size_++;
    }

    void pop_back() {
        if(size_ == 0) return;
        size_--;
    }
    
    void erase(unsigned int position) {
        assert(position >= 0 && position < size_);
    
        if(position == 0) {
            pop_front();
            return;
        }
    
        if (position == size_ - 1)
        {
            pop_back();
            return;
        }
    
        for (unsigned int i = position; i < size_ ; i++)
        {
            storage_[i] = storage_[i + 1];
        }
        
    size_--;
    }

    
};

int main() {
    Vector<int> MyVector(3);
    MyVector.push_front(1);
    MyVector.push_front(1);
    MyVector.push_front(1);
    MyVector.push_front(2);
    MyVector.push_front(3);
    MyVector.push_front(1);
    MyVector.push_front(2);
    MyVector.push_front(5);
    cout << "Tamaño: " << MyVector.size() << endl;
    MyVector.print();
    
    MyVector.print();
    MyVector.insert(1,4);
   MyVector.insert(2,5);
    MyVector.print();
    MyVector.erase(0);
    MyVector.erase(2);
    MyVector.erase(MyVector.size()-1);
    MyVector.print();
    
    return 0;
}
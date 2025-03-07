#include <iostream>

using namespace std;

template <typename T>

class List{

    private:
    class Node{

        private:
        T element;
        Node* next;

        public:
        Node(){
            element = T();
            next = nullptr;
        }
        Node(const T& elem){
            element = elem;
            next = nullptr;
        }
        void setNext(Node* newNode){
            next = newNode;
        }
        Node* getNext() const{
            return next;
        }
        T getElement() const{
            return element;
        }
        
    };
    Node* firts_;
    Node* last_;
    unsigned int size_;
    
    public:
    
    List(){
        firts_ = nullptr;
        last_ = nullptr;
        size_ = 0;
    }

    unsigned int size(){
        return size_;
    }

    bool empty(){
        return size_ == 0;
    }

    void push_back(const T& elem){
        Node* n = new Node(elem);
        if(firts_ == nullptr){
            firts_ = n;
            last_ = n;
        }
        else{
        last_->setNext(n);
        last_ = n;}
        size_++;
    }
    void push_front(const T& elem){
        Node* n = new Node(elem);
        if(firts_ == nullptr){
            firts_ = n;
            last_ = n;
        }
        else{
        n->setNext(firts_);
        firts_ = n;}
        size_++;
    }

    void print() {
        Node* naux = firts_;
        while (naux != nullptr) {
            cout << naux->getElement() << " ";
            naux = naux->getNext();
        }
        cout << endl;
    }
};

template <typename T>
class Stack{
    private:
    class Node{

        private:
        T element;
        Node* next;

        public:
        Node(){
            element = T();
            next = nullptr;
        }
        Node(const T& elem){
            element = elem;
            next = nullptr;
        }
        void setNext(Node* newNode){
            next = newNode;
        }
        Node* getNext() const{
            return next;
        }
        T getElement() const{
            return element;
        }
        
    };
    Node* top_;
    unsigned int size_;

    public:
    Stack(){
        top_ = nullptr;
        size_ = 0;
    }
    bool empty(){
        return size_ == 0;
    }
    void push(const T& elem){
        Node* n = new Node(elem);
        if(empty()){
            top_ = n;
        }
        else{
            n->setNext(top_);
            top_ = n;}
            size_++;
    }
    T top(){
        return top_->getElement();
    }
    void pop(){
        if(size_ == 1){
            top_ = nullptr;
        }
        else{
            top_ = top_->getNext();
        }
        size_--;
    }
    void print() {
        Node* naux = top_;
        while (naux != nullptr) {
            cout << naux->getElement() << " ";
            naux = naux->getNext();
        }
        cout << endl;
    }
      
};
template <typename T>
class Queqe{
    private:
    class Node{

        private:
        T element;
        Node* next;

        public:
        Node(){
            element = T();
            next = nullptr;
        }
        Node(const T& elem){
            element = elem;
            next = nullptr;
        }
        void setNext(Node* newNode){
            next = newNode;
        }
        Node* getNext() const{
            return next;
        }
        T getElement() const{
            return element;
        }
        
    };
    Node* firts_;
    Node* last_;
    unsigned int size_;

    public:
    Queqe(){
        firts_ = nullptr;
        last_ = nullptr;
        size_ = 0;
    }
    bool empty(){
        return size_ == 0;
    }
    void push(const T& elem){
        Node* n = new Node(elem);
        if(empty()){
            firts_ = n;
            last_ = n;
        }
        else{
            last_->setNext(n);
            last_ = n;}
            size_++;
        }
    T front(){
        return firts_->getElement();
    }
    void pop(){
        if(size_ == 1){
            firts_ = nullptr;
        }
        else{
            firts_ = firts_->getNext();
        }
        size_--;
    }
    void print() {
        Node* naux = firts_;
        while (naux != nullptr) {
            cout << naux->getElement() << " ";
            naux = naux->getNext();
        }
        cout << endl;
    }
      
};

int main() {
    List<int> myList;
    myList.push_front(50);
    myList.push_back(30);
    Stack<char> myStack;
    myStack.push('n');
    myStack.push('o');
    myStack.push('h');
    myStack.push('o');
    myStack.push('r');
    myStack.push('a');
    Queqe<string> myQueqe;
    myQueqe.push("nohora");
    myQueqe.push("camila");
    myQueqe.push("cardozo");
    myQueqe.push("cardenas");
    
    cout << "Lista: ";
    myList.print();
    cout << "Pila: ";
    myStack.print();
    myStack.pop();
    myStack.print();
    cout << "Cola: ";
    myQueqe.print();
    myQueqe.pop();
    myQueqe.print();
    return 0;
}
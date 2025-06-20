#include <iostream>
#include <cassert>
#include <queue>
using namespace std;

template <typename T>
// BINARY SEARCH TREE
class Tree{

    private:

     class Node{
        private:
        T data_;
        Node* left_;
        Node* right_;

        public:
        void SetData(const T n){
            data_ = n;
        }
        void SetRight(Node* n){
            right_= n;
        }
        void SetLeft(Node* n){
            left_ = n;
        }
        T GetData(){
            return data_;
        }
        Node* GetRight(){
            return right_;
        }
        Node* GetLeft(){
            return left_;
        }
        Node(){
            data_ = T();
            right_ = nullptr;
            left_ = nullptr;
        }
        Node(T data){
            data_ = data;
            right_ = nullptr;
            left_ = nullptr;
        }
      };

      Node* root;
      unsigned int size_;

      public:

      Tree(){
        root = nullptr;
        size_ = 0;
      }
    bool empty(){
        return size_ == 0;
    }
    unsigned int size(){
        return size_;
    }

    void Insert(const T &data){
        Node* n = new Node(data);
        if(empty()){
            root = n;
            size_ += 1;
            return;
        }
        Node* current = root;
        Node* parent = nullptr;
        while(current != nullptr){
            parent = current;
            if(data < current->GetData()){
                current = current->GetLeft();
            }
            else{
                current = current->GetRight();
            }
        }
        if(data < parent->GetData()){
            parent->SetLeft(n);
        }
        else{
            parent->SetRight(n);
        }
        size_++;
    }
    
    void PrintInOrder(Node* n){
        if(n == nullptr){
            return;
        }
        PrintInOrder(n->GetLeft());
        cout<<n->GetData()<<"->";
        PrintInOrder(n->GetRight());
    }
    void PrintPreOrder(Node* n){
        if(n == nullptr){
            return;
        }
        cout<<n->GetData()<<"->";
        PrintPreOrder(n->GetLeft());
        PrintPreOrder(n->GetRight());
    }
    void PrintPosOrder(Node* n){
        if(n == nullptr){
            return;
        }
        PrintPosOrder(n->GetLeft());
        PrintPosOrder(n->GetRight());
        cout<<n->GetData()<<"->";
    }
    void PrintLevelsOrder(){
        if(empty()){
            return;
        }
        queue<Node*> queue;
        queue.push(root);
        while(!queue.empty()){
        Node* current = queue.front();
        queue.pop();
        cout<<"("<<current->GetData()<<")->";
        if(current->GetLeft() != nullptr){
            queue.push(current->GetLeft());
        }
        if(current->GetRight() != nullptr){
            queue.push(current->GetRight());
        }}
    }

    void Print(){
        if(empty()) return;
        PrintLevelsOrder();
    }

   bool Find(const T &data){
    if(empty()) return false;
    Node* current = root;

    while (current->GetData() != data){
        if(data < current->GetData()){
            current = current->GetLeft();
        }
        else{
            current = current->GetRight();
        }
        if(current == nullptr){
            return false;
        }
    }
    if (current->GetData() == data){
        return true;
    }
    else{
        return false;
    }
}

void Remove(const T &data){
    //first case: tree is empty
    if(empty()) return;

    Node* parent = nullptr;
    Node* current = root;

    //search
    while(data != current->GetData()){
        parent = current;
        if(data < current->GetData()){
            current = current->GetLeft();
        }
        else{
            current = current->GetRight();
        }
        if(current == nullptr){
            return;
        }
    }
    //second case: the node has no children
    if(current->GetLeft() == nullptr && current->GetRight() == nullptr){
        if(parent == nullptr){
            root = nullptr;
        }
        else{if(current == parent->GetLeft()){
            parent->SetLeft(nullptr);
        }
        else{
            parent->SetRight(nullptr);
        }
    }
        delete current;
    }
    //third case: the node has one children 
    else if(current->GetRight() == nullptr || current->GetLeft() == nullptr){
        Node* son = nullptr;
        if(current->GetRight() != nullptr){
            son = current->GetRight();
        }
        else{
            son = current->GetLeft();
        }
        if(current->GetData() < parent->GetData()){
            parent->SetLeft(son);
        }
        else{
            parent->SetRight(son);
        }
        delete current;
    }
    //fourth case: the node has two children
    else if(current->GetRight() != nullptr && current->GetLeft() != nullptr){
        Node* succ = current->GetRight();
        Node* psucc = current;

        while(succ->GetLeft() != nullptr){
            psucc = succ;
            succ = succ->GetLeft();
        }
        if(psucc->GetLeft() == succ){
           psucc->SetLeft(succ->GetRight());
        }
        else{
            psucc->SetRight(succ->GetRight());
        }
        succ->SetLeft(current->GetLeft());
        succ->SetRight(current->GetRight());
        if( parent == nullptr){
          root = succ;
        }
        else{
            if(parent->GetLeft() == current){
                parent->SetLeft(succ);
            }
            else{
                parent->SetRight(succ);
            }
        }
        delete current;
    }
    size_--;
}
};
    


int main(){
    Tree<int> tree;
    tree.Insert(12);
    tree.Insert(15);
    tree.Insert(3);
    tree.Insert(4);
    tree.Insert(2);
    tree.Print();
    //cout<<tree.Find(15)<<endl;
    //cout<<tree.Find(19)<<endl;
    tree.Remove(3);
    tree.Print();
    return 0;
}


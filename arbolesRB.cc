#include <iostream>
#include <cassert>
using namespace std;
enum Color { RED, BLACK };
template <typename T>
// ARBOLES ROJO-NEGRO
class RBTree{

    private:

     class Node{
        private:
        T data_;
        Color color_;
        Node* parent_;
        Node* letf_;
        Node* right_;

        public:
        void SetColor(const Color color){
            color_=color;
        }
        void SetData(const T n){
            data_ = n;
        }
        void SetRight(Node* n){
            right_= n;
        }
        void SetLeft(Node* n){
            letf_ = n;
        }
        void SetParent(Node* n){
            parent_ = n;
        }
        T GetData(){
            return data_;
        }
        Color GetColor(){
            return color_;
        }
        Node* GetParent(){
            return parent_;
        }
        Node* GetRight(){
            return right_;
        }
        Node* GetLeft(){
            return letf_;
        }
        Node(){
            data_ = T();
            color_ = RED;
            parent_ = nullptr;
            right_ = nullptr;
            letf_ = nullptr;
        }
        Node(T data){
            data_ = data;
            color_ = RED;
            parent_ = nullptr;
            right_ = nullptr;
            letf_ = nullptr;
        }
      };

      Node* root;
      unsigned int size_;

      public:
      Node* GetRoot(){
        return root;
      }
      RBTree(){
        root = nullptr;
        size_ = 0;
      }
    bool empty(){
        return size_ == 0;
    }
    unsigned int size(){
        return size_;
    }
    void rotateLeft(Node* n) {
        Node* current = n->GetRight();
        n->SetRight(current->GetLeft());
        if (current->GetLeft() != nullptr)
            current->GetLeft()->SetParent(n);
        current->SetParent(n->GetParent());
        if (n->GetParent() == nullptr)
            root = current;
        else if (n == n->GetParent()->GetLeft())
            n->GetParent()->SetLeft(current);
        else
            n->GetParent()->SetRight(current);
        current->SetLeft(n);
        n->SetParent(current);
    }
    
    void rotateRight(Node* n) {
        Node* current = n->GetLeft();
        n->SetLeft(current->GetRight());
        if (current->GetRight() != nullptr)
        current->GetRight()->SetParent(n);
        current->SetParent(n->GetParent());
        if (n->GetParent() == nullptr)
            root = current;
        else if (n == n->GetParent()->GetRight())
            n->GetParent()->SetRight(current);
        else
            n->GetParent()->SetLeft(current);
            current->SetRight(n);
        n->SetParent(current);
    }
    
    void fixInsert(Node* n) {
        Node* uncle;
        while (n != root && n->GetParent()->GetColor() == RED) {
            if (n->GetParent() == n->GetParent()->GetParent()->GetLeft()) {
                uncle = n->GetParent()->GetParent()->GetRight(); // tío
                if (uncle != nullptr && uncle->GetColor() == RED) {
                    // Caso 1: El tío es rojo => recolorear
                    n->GetParent()->SetColor(BLACK);
                    uncle->SetColor(BLACK);
                    n->GetParent()->GetParent()->SetColor(RED);
                    n = n->GetParent()->GetParent();
                } else {
                    if (n == n->GetParent()->GetRight()) {
                        // Caso 2: El nodo es hijo derecho => rotar
                        n = n->GetParent();
                        rotateLeft(n);
                    }
                    // Caso 3: El nodo es hijo izquierdo
                    n->GetParent()->SetColor(BLACK);
                    n->GetParent()->GetParent()->SetColor(RED);
                    rotateRight(n->GetParent()->GetParent());
                }
            } else {
                // Simétrico: el padre es hijo derecho
                uncle = n->GetParent()->GetParent()->GetLeft();
                if (uncle != nullptr && uncle->GetColor() == RED) {
                    // Caso 1
                    n->GetParent()->SetColor(BLACK);
                    uncle->SetColor(BLACK);
                    n->GetParent()->GetParent()->SetColor(RED);
                    n = n->GetParent()->GetParent();
                } else {
                    if (n == n->GetParent()->GetLeft()) {
                        // Caso 2
                        n = n->GetParent();
                        rotateRight(n);
                    }
                    // Caso 3
                    n->GetParent()->SetColor(BLACK);
                    n->GetParent()->GetParent()->SetColor(RED);
                    rotateLeft(n->GetParent()->GetParent());
                }
            }
        }
        root->SetColor(BLACK);
    }
    
    void Insert(const T &data){
        Node* n = new Node(data);
        if(empty()){
            root = n;
            root->SetColor(BLACK);  
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
    
        n->SetParent(parent);
        size_++;
        fixInsert(n);
    }
    
    void PrintInOrder(Node* n){
        if(n == nullptr){
            return;
        }
        PrintInOrder(n->GetLeft());
        cout<<n->GetData()<<"->";
        PrintInOrder(n->GetRight());
    }

    void Print(){
        if(empty()) return;
        PrintInOrder(root);
    }

    int height(Node* node) {
        if (!node) return -1; // convention: height of empty tree is -1
        int leftHeight = height(node->GetLeft());
        int rightHeight = height(node->GetRight());
        return 1 + max(leftHeight, rightHeight);
    }
};
int main(){
    RBTree<int> tree;
    tree.Insert(12);
    tree.Insert(15);
    tree.Insert(3);
    tree.Insert(4);
    tree.Insert(2);
    tree.Insert(1);
    tree.Insert(7);
    tree.Insert(33);
    tree.Insert(6);
    tree.Print();
    cout<<endl;
    cout<<tree.height(tree.GetRoot())<<endl;
    //cout<<tree.Find(19)<<endl;
    return 0;
}
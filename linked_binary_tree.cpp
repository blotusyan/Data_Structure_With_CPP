#include<iostream>
#include<list>

template<typename T> 
class LinkedBinaryTree{
    protected:
        // Node
        template<typename U> 
        class Node{
            public:
                U element;
                Node<U>* parent;
                Node<U>* left;
                Node<U>* right;
                Node<U>(U val = 20): element(val), parent(nullptr), left(nullptr), right(nullptr){}
        };
    public:
        // Position, similar to Iterator
        template<typename U> 
        class Position{
            private:
                Node<U>* v;
            public:
                Position<U>(Node<U>* _v = nullptr): v(_v) {}
                U& operator*(){
                    return v->element;
                }
                Position<U> left(){
                    return Position(v->left);
                }
                Position<U> right(){
                    return Position(v->right);
                }
                Position<U> parent(){
                    return Position(v->parent);
                }
                bool isRoot() const{
                    return v->parent == nullptr; //does not call parent(), ar current layer uses only member var instead of method
                }
                bool isExternal() const{
                    return v->left == nullptr && v->right == nullptr;
                }
                friend class LinkedBinaryTree;
        };
        typedef std::list<Position<T>> PositionList;

    public:
        LinkedBinaryTree(): _root(nullptr), n(0){}
        int size() const{
            return n;
        }
        bool empty() const {
            return size() == 0;
        }
        Position<T> root() const {
            return Position<T>(_root);
        }
        PositionList positions() const {
            PositionList positionList;
            preorder(_root, positionList);
            return PositionList(positionList);
        }
        void addRoot(){
            _root = new Node<T>(100);
            // _root.parent = nullptr;
            n+=1;
        }
        void expandExternal(const Position<T>& p){
            Node<T>* v = p.v;
            v->left = new Node<T>;
            v->left->parent = v;
            v->right = new Node<T>;
            v->right->parent = v;
            n+=2;
        }
        Position<T> removeAboveExternal(const Position<T>& p){
            Node<T>* w = p.v;
            Node<T>* v = w->parent;
            Node<T>* sibling = ((w==v->left)?(v->right):(v->left));
            if (v == _root){
                _root = sibling;
                sibling->parent = nullptr;
            }
            else{
                Node<T>* grandParent = v->parent;
                if (v == grandParent->left){
                    grandParent->right = sibling;
                }
                else{
                    grandParent->left = sibling;
                }
                sibling->parent = grandParent;
            }
            delete w;
            delete v;
            n-=2;
            return Position<T>(sibling);
        }
    protected:
        void preorder(Node<T>* v, PositionList& positionList) const {
            positionList.push_back(Position<T>(v));
            if (v->left != nullptr){
                preorder(v->left, positionList);
            }
            if (v->right != nullptr){
                preorder(v->right, positionList);
            }
        }
    private:
        Node<T>* _root;
        int n;
};

int main(){
    LinkedBinaryTree<int> my_tree;
    my_tree.addRoot();
    my_tree.expandExternal(my_tree.root());
    std::cout << " tree is here: " << *my_tree.root() << std::endl;
    return 0;
}

#include<iostream>

template<typename T>
class NodeList;  // forward declaration

template<typename T>
class Node{
    private:
        T val;
        Node<T>* next;
        friend class NodeList<T>;
};

template<typename T>
class NodeList{
    public:
        NodeList(): cursor(nullptr) {}
        ~NodeList(){
            while(!isEmpty()){
                remove(); //dont have to be remove(front())
            }
            delete cursor;
        }
        bool isEmpty(){
            return cursor == nullptr;
        }
        const T& front(){
            return cursor->next->val;
        }
        const T& back(){
            return cursor->val;
        }
        void advance(){
            cursor = cursor->next;
        }
        void add(const T& value){
            //add immediately after the cursor (front)
            Node<T>* new_node = new Node<T>;
            new_node->val = value;
            if (cursor == nullptr){ //handle condition when cursor is nullptr
                new_node->next = new_node;
                cursor = new_node;
            }
            else{
                new_node->next = cursor->next;
                cursor->next = new_node;
            }
        }
        void remove(){
            Node<T>* old = cursor->next;
            if (old == cursor){ // handle condition when cursor is pting to the only item in list
                cursor = nullptr;
            }
            else{
                cursor->next = cursor->next->next;
            }
            delete old;
        }

    private:
        Node<T>* cursor;
};

int main(){
    NodeList<int> my_list;
    my_list.add(3);
    my_list.add(2);
    my_list.add(1);
    int front = my_list.front();
    int back = my_list.back();
    std::cout << "front is : " << front << " and the back is : " << back << std::endl;
    return 0;
}
#include<iostream>

template<typename T>
class NodeList;            // Forward declaration of NodeList

template<typename T>
class Node{
    private: //all private
        T val;
        Node<T>* next;
        friend class NodeList<T>; //<T>
};

template<typename T>
class NodeList{
    public:
        NodeList(): head(nullptr){}
        ~NodeList(){
            while (!isEmpty()){
                removeFront();
            }
        }
        bool isEmpty(){
            return head == nullptr;
        }
        const T& front(){
            return head->val;
        }
        void addFront(const T& value){  //const
            Node<T>* new_node = new Node<T>; //Node<T>
            new_node->val = value;
            new_node->next = head;
            head = new_node;
        }
        void removeFront(){
            Node<T>* old_node = head; //Node<T>
            head = head->next;
            delete old_node;
        }
        // IF IMPLEMENT, NEED ALL METHODS TO HAVE TEMPLATE HEADER
    private:
        Node<T>* head;

};


int main(){
    NodeList<int> my_list;
    bool res = my_list.isEmpty();
    std::cout << "the list " << (res?"is":"is not") << " empty" << std::endl;
    my_list.addFront(2);
    my_list.addFront(3);
    my_list.removeFront();
    my_list.removeFront();
    bool res1 = my_list.isEmpty();
    std::cout << "the list " << (res1?"is":"is not") << " empty" << std::endl;
    return 0;
}
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

template<typename T>
class LinkedQueue{
    private:
        NodeList<T> LinkedList;
        int num;
    public:
        LinkedQueue(): num(0), LinkedList(){}
        bool isEmpty(){
            return num == 0;
        }
        const T& front(){
            return LinkedList.front();
        }
        const T& back(){
            return LinkedList.back();
        }
        void enqueue(const T& val){
            LinkedList.add(val);
            LinkedList.advance();
            num++; // add count
        }
        void dequeue(){
            LinkedList.remove();
            num--;
        }

};


int main(){
    LinkedQueue<int> my_queue;
    my_queue.enqueue(1);
    my_queue.enqueue(2);
    my_queue.enqueue(3);
    std::cout << "front item is : " <<  my_queue.front() << std::endl;
    std::cout << "back item is : " <<  my_queue.back() << std::endl;
    my_queue.dequeue();
    std::cout << "front item is : " <<  my_queue.front() << std::endl;
    std::cout << "back item is : " <<  my_queue.back() << std::endl;
    return 0;
}
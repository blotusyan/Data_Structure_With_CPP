#include<iostream>
class StackEmpty : public std::exception{ //custom exception
    public:
        StackEmpty(char* message): msg(message){}
    private: 
        char* msg;
};
class StackFull : public std::exception{
    public:
        StackFull(char* message): msg(message){}
    private: 
        char* msg;
};

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

template<typename T>
class ListArray{
    public:
        ListArray(int n = 10) : num(n), LL(){}
        ~ListArray(){
            while(!LL.isEmpty()){
                pop();
            }
        }
        int size() const{
            return num;
        }
        bool empty(){
            return LL.isEmpty();
        }
        const T& top() throw(StackEmpty){
            if (empty()){
                throw StackEmpty("it is empty");
            }
            return LL.front();
        }
        void push(const T& val){
            ++num; //increment
            LL.addFront(val);
        }
        void pop() throw(StackEmpty){
            if (empty()){
                throw StackEmpty("it is empty");
            }
            --num; //decrement
            LL.removeFront();
        }
    private:
        int num;
        NodeList<T> LL; // use object instance instead of class

};

int main(){
    ListArray<int> my_stack(10);
    my_stack.push(0);
    my_stack.push(4);
    my_stack.push(1);
    std::cout << "top item is : " << my_stack.top() << std::endl;
    return 0;
}
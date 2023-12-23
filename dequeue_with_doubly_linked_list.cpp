#include<iostream>

template<typename T>
class NodeList;  // forward declaration

template<typename T>
class Node{
    private:
        T val;
        Node<T>* next;
        Node<T>* prev;
        friend class NodeList<T>;
};

template<typename T>
class NodeList{
    public:
        NodeList<T>(){
            header = new Node<T>;
            trailer = new Node<T>;
            header->next = trailer;
            trailer->prev = header;
        }
        ~NodeList<T>(){
            while (!isEmpty()){
                removeFront();
            }
            delete header;
            delete trailer;
        }
        bool isEmpty(){
            return header->next == trailer;
        }

        const T& front(){ //const NODE<T>&
            return header->next->val; //return val is enough
        }

        const T& back(){
            return trailer->prev->val;
        }

        void addFront(const T& value){
            add(header->next, value);
        }
        void addBack(const T& value){
            add(trailer, value);
        }
        void removeFront(){
            remove(header->next);
        }
        void removeBack(){
            remove(trailer->prev);
        }

    protected: // add & remove at arbitrary location
        void add(Node<T>* v, const T& value){
            Node<T>* u = new Node<T>;
            u->val = value;
            u->next = v;
            u->prev = v->prev;
            v->prev->next =  u;
            v->prev = u;
        }
        void remove(Node<T>* v){
            Node<T>* first = v->prev;
            Node<T>* second = v->next;
            first->next = second;
            second->prev = first;
            delete v;
        }


    private: // no size member
        Node<T>* header;
        Node<T>* trailer;

};

template<typename T>
class deque{
    private:
        NodeList<T> my_double_linked_list; // not a ptr
        int num;
    public:
        deque(): num(0), my_double_linked_list(){}
        int size(){
            return num;
        }
        bool isEmpty(){
            return num == 0;
        }
        const T& front(){
            return my_double_linked_list.front(); //use . instead of ->
        }
        const T& back(){
            return my_double_linked_list.back();
        }
        void insertFront(const T& val){
            my_double_linked_list.addFront(val);
            num++;
        }
        void insertBack(const T& val){
            my_double_linked_list.addBack(val);
            num++;
        }
        void removeFront(){
            my_double_linked_list.removeFront();
            num--;
        }
        void removeBack(){
            my_double_linked_list.removeBack();
            num--;
        }
};

int main(){
    deque<int> my_list;
    my_list.insertFront(2);
    my_list.insertFront(1);
    my_list.insertBack(3);
    auto front = my_list.front();
    auto back = my_list.back();
    std::cout << "front is : " << front << ", " << "back is: " << back << std::endl;
    return 0;
}
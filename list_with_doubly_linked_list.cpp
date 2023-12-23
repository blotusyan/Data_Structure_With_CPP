#include<iostream>

template<typename T>
class NodeList;  // forward declaration

template<typename T>
class Iterator;

template<typename T>
class Node{
    private:
        T val;
        Node<T>* next;
        Node<T>* prev;
        friend class NodeList<T>;
        friend class Iterator<T>;
};

template<typename T>
class Iterator{
    private:
        Node<T>* v;
        Iterator(Node<T>* u){
            v = u;
        }
    public:
        T& operator*(){
            return v->val;
        }
        bool operator==(const Iterator& p) const{
            //return *this == *p;
            return v == p.v;
        }
        bool operator!=(const Iterator& p) const{
            return v != p.v;
        }
        Iterator& operator++(){
            //return &v->next; There is only one iterator, need to reassign
            v = v->next;
            return *this;
        }
        Iterator& operator--(){
            v = v->prev;
            return *this; //this is a ptr to current instance
            //In the operator++() method, 
            //*this is used as a reference to the current iterator object. 
            //It allows you to update the iterator and return a reference to the updated iterator itself. 
            //The * in *this is not related to the operator*() method. 
            //To clarify, when you use *this in the operator++() method, you are referring to the current object, 
            //not invoking the operator*() method. 
            //The operator*() method is invoked when you use the dereference operator * explicitly on an iterator object.
        }
        friend class NodeList<T>;
};

template<typename T>
class NodeList{
    public:
        Iterator<T> begin() const{
            return Iterator<T>(header->next);
        }
        Iterator<T> end() const {
            return Iterator<T>(trailer); //end is the position after the last one, so should not use trailer->prev here
        }
        NodeList<T>(){
            num = 0;
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
        int size(){
            return num;
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
            num++;
        }
        void addBack(const T& value){
            add(trailer, value);
            num++;
        }
        void insertFront(const T& value){
            insert(begin(), value);
        }
        void insertBack(const T& value){
            insert(end(), value);
        }
        void eraseFront(){
            insert(begin());
        }
        void eraseBack(){
            insert(--end());
        }
        void removeFront(){
            remove(header->next);
            num--;
        }
        void removeBack(){
            remove(trailer->prev);
            num--;

        }
        void print(){
            Node<T>* head = header->next;
            while (head != trailer){
                std::cout << head->val << " --> ";
                head = head->next;
            }
            std::cout << std::endl;
        }

    protected: // add & remove at arbitrary location
        void add(Node<T>* v, const T& value){ //position is refered by a ptr to Node
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
        void insert(Iterator<T> p, const T& value) //ptr to Node is wrapped by a class object Iterator
        { // need to remove & for p here otherwise cause : non-const lvalue reference to type 'Iterator<...>' cannot bind to a temporary of type 'Iterator<...>'
            Node<T>* cur_node = p.v;
            Node<T>* prev_ = cur_node->prev;
            Node<T>* new_node = new Node<T>;
            new_node->val = value;
            new_node->next = cur_node;
            new_node->prev = prev_;
            prev_->next = new_node;
            cur_node->prev = new_node;
        }
        void erase(Iterator<T> p){
            Node<T>* cur_node = p.v; // this is the same thing as v in line 129 as input
            Node<T>* prev_node = cur_node->prev;
            Node<T>* next_node = cur_node->next;
            prev_node->next = next_node;
            next_node->prev = prev_node;
            delete cur_node;
        }

    private: // no size member
        int num;
        Node<T>* header;
        Node<T>* trailer;

};

// sequence is list + indexing                                  

template<typename T>
class NodeSequence: public NodeList{
    public:
        Iterator atIndex(int i) const{
            Iterator p = begin();
            for (int j = 0; j<i; i++){
                ++p;
            }
            return p;
        }
        int indexOf(const Iterator& p) const{
            Iterator q = begin();
            int j = 0;
            while (q != p){
                q++;
                j++;
            }
            return j;
        }

};
int main(){
    NodeList<int> my_list;
    my_list.insertFront(2);
    my_list.insertFront(1);
    my_list.insertBack(3);
    auto front = my_list.front();
    auto back = my_list.back();
    std::cout << "front is : " << front << ", " << "back is: " << back << std::endl;
    my_list.print();
    return 0;
}
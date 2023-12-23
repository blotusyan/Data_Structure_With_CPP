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

        // void addFront(const T& value){
        //     Node<T>* new_node = new Node<T>;
        //     new_node->val = value;
        //     new_node->next = header->next;
        //     header->next->prev = new_node;
        //     header->next = new_node;
        //     new_node->prev = header;
        // }
        // void removeFront(){
        //     Node<T>* old = header->next;
        //     header->next = old->next;
        //     old->next->prev = header;
        //     delete old;
        // }
        // void addBack(){
        //     Node<T>* new_node = new Node<T>;
        //     new_node->val = value;
        //     new_node->next = trailer;
        //     trailer->prev->next = new_node;
        //     new_node->prev = trailer->prev;
        //     trailer->prev = new_node;
        // }
        // void removeBack(){
        //     Node<T>* old = trailer->prev;
        //     trailer->prev = old->prev;
        //     old->prev->next = trailer;
        //     delete old;
        // }
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
        void print(){
            Node<T>* head = header->next;
            while (head != trailer){
                std::cout << head->val << " --> ";
                head = head->next;
            }
            std::cout << std::endl;
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
            // Node<T>* old_next = v->next;
            // old_next->prev = v->prev;
            // old_next->next = v->next->next;
            // v->next->next->prev = old_next;
            // v->prev->next = old_next;

            //use two ptrs
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

int main(){
    NodeList<int> my_list;
    my_list.addFront(2);
    my_list.addFront(1);
    my_list.addBack(3);
    auto front = my_list.front();
    auto back = my_list.back();
    std::cout << "front is : " << front << ", " << "back is: " << back << std::endl;
    my_list.print();
    return 0;
}
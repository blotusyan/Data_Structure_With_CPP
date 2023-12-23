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
template <typename T>
class ArrayStack{
    public:
        ArrayStack(int cap = 10): capacity(cap), num(-1), array(new T[cap]){} //constructor array
        bool isEmpty(){
            return num < 0;
        }
        int size(){
            return num + 1;
        }
        const T& top() {
            if (isEmpty()){
                throw StackEmpty("top of empty stack");
            }
            return array[num];
        }
        void push(const T& e) { // const T&
            if (num + 1 == capacity){
                throw StackFull("push to full stack");
            }
            array[++num] = e;
        }
        void pop() {
            if (isEmpty()){
                throw StackEmpty("pop from empty stack");
            }
            array[num--] = 0;
        }
    private:
        T* array;
        int capacity;
        int num;

};

int main(){
    ArrayStack<int> array(5); // pass in argument
    array.push(1);
    array.push(5);
    array.pop();
    std::cout << "top item is : " << array.top() << " it is good" << std::endl;
    array.pop();
    array.pop();
    return 0;
}
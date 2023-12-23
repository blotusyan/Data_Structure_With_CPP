#include<iostream>

class IndexOutOfBounds : public std::exception{ //custom exception
    public:
        IndexOutOfBounds(char* message): msg(message){}
    private: 
        char* msg;
};

template <typename T>
class ArrayVector{
    private:
        int n;
        int capa;
        T* Array;
    public:
        ArrayVector(int capa_ = 10): n(0), capa(0), Array(new T[capa_]){} //nullptr + forget to make use of the value capa_ in constructor
        int size() const {
            return n;
        }
        bool isEmpty(){
            return size() == 0;
        }
        T& operator[](int i){
            return Array[i];
        }
        T& at(int i){
            if (i < 0 || i >= n){ // two conditions
                throw IndexOutOfBounds("out of bound"); // if it is over the total assigned nums instead of the capacity
            }
            return Array[i];
        }
        void erase(int i){
            for (int ite = i + 1; ite < n; ite++){
                Array[ite-1] = Array[ite];
            }
            n--;
        }
        void insert(int i, const T& val){
            if (n >= capa){
                reserve(std::max(1,2*capa));
            }
            // for (int ite = i + 1; ite < n; ite++){ //overlap, need to start from end
            //     Array[ite] = Array[ite-1];
            // }
            for (int ite = n - 1; ite >= i; ite--){ //remember it is not the end of the array, maybe just part of it, so need to use one more index
                Array[ite+1] = Array[ite];
            }
            n++;
            Array[i] = val;
        }
        void reserve(int N){
            if (capa >= N){
                return;
            }
            T* new_array = new T[N]; // just a array, not a ArrayVector object instance
            for (int j = 0; j < n; j++){
                new_array[j] = Array[j];
            }
            if (Array != nullptr){
                delete[] Array;
            }
            Array = new_array;
            capa = N;
            // Array = new ArrayVector(capa*2)
        }
};

int main(){
    ArrayVector<int> my_vec;
    my_vec.insert(0, 3);
    my_vec.insert(0, 2);
    my_vec.insert(0, 1);
    my_vec.reserve(100);
    std::cout << "first item is: " << my_vec.at(90) << std::endl;
    return 0;
}
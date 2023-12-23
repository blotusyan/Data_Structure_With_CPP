#include<iostream>
#include<list>
#include<vector>

template <typename K, typename V>
class m_Entry{
    private:
        K _key;
        V _val;
    public:
        m_Entry(const K key_, const V val_): _key(key_), _val(val_){}
        K get_key(){
            return this->_key;
        }
        V get_val(){
            return this->_val;
        }
        void set_key(const K key_){
            this->_key = key_;
        }
        void set_val(const V val_){
            this->_val = val_;
        }

};


template<typename K, typename V>
class Map{
    public:
        using Entry = m_Entry<K, V>; // replace template 
        class m_Entry;
        int size() const{
            return n;
        }
        bool empty() const{
            return n == 0;
        }
        V find(const K& k){ //typename + iterator (dependent type name)
            for (auto itr = _map.begin(); itr != _map.end(); itr++){
                if (itr->get_key() == k){
                    std::cout << " the key value pair is : " << itr->get_key() << "->" << itr->get_val() << std::endl;
                    return itr->get_val();
                }
            }
            return "-1";
        }
        void put(const K& k, const V& v){
            _map.push_back(Entry(k, v));
            n+=1;
        }
        // void erase(const K& k){
        //     auto itr = _map.find(k);
        //     _map.erase(itr);
        //     n-=1;
        // }
    private:
        int n;
        std::vector<Entry> _map;
};

int main(){
    Map<int, std::string> my_map;
    my_map.put(5, "five");
    std::cout<<"first item is " << my_map.find(5) << std::endl;
    return 0;
}
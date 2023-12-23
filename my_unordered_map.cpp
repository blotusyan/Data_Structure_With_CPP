#include<list>
#include<iostream>

class hashMap{
    public:
        class Entry{
            public:
                int key;
                std::string val;
                Entry(int _key, std::string _val): key(_key), val(_val){}
        };
        int getIndex(int& key){
            return key % num;
        }
        hashMap(int n = 0){
            num = n;
            table = new std::list<Entry>[n];
        }
        void put(int key, std::string val){ //not reference &key, cuz in main it is a rvalue
            int index = getIndex(key);
            for (auto it = table[index].begin(); it != table[index].end(); it++){
                if (it->key == key){
                    it->val = val;
                    return;
                }
            }
            table[index].push_back(Entry(key, val));
            return;
        }
        std::string get(int key){
            int index = getIndex(key);
            for (auto it = table[index].begin(); it != table[index].end(); it++){
                if (it->key == key){
                    return it->val;
                }
            }
            std::cout << "key not found" << std::endl;
            return "-1";
        }
        void erase(int key){
            int index = getIndex(key);
            for (auto it = table[index].begin(); it != table[index].end(); it++){
                if (it->key == key){
                    table[index].erase(it);
                    return;
                }
            }
            return;
        }
    protected:
        int num;
        std::list<Entry>* table;
};

int main(){
    hashMap my_map(1);
    my_map.put(1,"ABC");
    my_map.put(2,"DEF");
    my_map.put(3,"HHF");
    my_map.erase(1);
    auto val = my_map.get(3);
    std::cout << "return value pair is: " << val  << std::endl;
    return 0;
}
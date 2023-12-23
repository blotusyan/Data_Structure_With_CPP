#include <iostream>
#include <list>
#include <functional>
using namespace std;

class MyHashMap {
private:
    int bucketSize;
    list<pair<int, int>>* buckets;
    int hashFunction(int key) {
        return (key) % bucketSize;
    }
public:
    MyHashMap(int size) {
        bucketSize = size;
        buckets = new list<pair<int, int>>[bucketSize];
    }
    void put(int key, int value) {
        int index = hashFunction(key);
        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->first == key) {
                it->second = value;
                return;
            }
        }
        buckets[index].push_back({key, value});
    }
    int get(int key) {
        int index = hashFunction(key);
        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->first == key)
                return it->second;
        }
        return -1;
    }
    void remove(int key) {
        int index = hashFunction(key);
        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->first == key) {
                buckets[index].erase(it);
                return;
            }
        }
    }
    bool containsKey(int key) {
        int index = hashFunction(key);
        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->first == key)
                return true;
        }
        return false;
    }
};

int main() {
    MyHashMap map(10);
    map.put(5, 100);
    map.put(10, 200);
    map.put(15, 300);
    cout << "Value at key 10: " << map.get(10) << endl;
    cout << "Value at key 20: " << map.get(20) << endl;
    map.remove(10);
    cout << "Contains key 10: " << map.containsKey(10) << endl;
    return 0;
}

#include <iostream>
#include <list>

template <typename K, typename V>
class Map {
private:
    struct Entry {
        K key;
        V value;
        Entry(const K& k, const V& v) : key(k), value(v) {}
    };

    std::list<Entry> entries;

public:
    void put(const K& key, const V& value) {
        for (auto& entry : entries) {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }
        entries.emplace_back(key, value);
    }

    bool get(const K& key, V& value) const {
        for (const auto& entry : entries) {
            if (entry.key == key) {
                value = entry.value;
                return true;
            }
        }
        return false;
    }

    void erase(const K& key) {
        entries.remove_if([&key](const Entry& entry) { return entry.key == key; });
    }

    bool contains(const K& key) const {
        for (const auto& entry : entries) {
            if (entry.key == key) {
                return true;
            }
        }
        return false;
    }

    int size() const {
        return entries.size();
    }

    bool empty() const {
        return entries.empty();
    }
};

int main() {
    Map<int, std::string> my_map;

    my_map.put(1, "one");
    my_map.put(2, "two");
    my_map.put(3, "three");
    
    std::string value;
    if (my_map.get(2, value)) {
        std::cout << "Value for key 2: " << value << std::endl;
    } else {
        std::cout << "Key 2 not found" << std::endl;
    }

    my_map.erase(2);

    if (my_map.contains(2)) {
        std::cout << "Key 2 is still in the map" << std::endl;
    } else {
        std::cout << "Key 2 has been removed from the map" << std::endl;
    }

    std::cout << "Map size: " << my_map.size() << std::endl;

    return 0;
}

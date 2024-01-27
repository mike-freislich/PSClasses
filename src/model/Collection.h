#include <unordered_map>
#include <stdio.h>

template <typename KeyType, typename ValueType>
class CollectionBase {
public:
    void addItem(const KeyType& key, const ValueType& value) {
        items[key] = value;
    }

    void removeItem(const KeyType& key) {
        auto it = items.find(key);
        if (it != items.end()) {
            items.erase(it);
        }
    }

    void displayItems() const {
        for (const auto& pair : items) 
        {
            //cout >> 
            //printf("key: %s, value: %s\n", std::to_string(pair.first), std::to_string(pair.second))            
        }
    }

protected:
    std::unordered_map<KeyType, ValueType> items;
};
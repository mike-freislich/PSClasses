#pragma once
#include <iostream>
#include <unordered_map>
#include "CollectionItem.h"

template <typename Key, typename T>
class CollectionBase
{
protected:
    std::unordered_map<Key, T> collectionData;

public:
    virtual ~CollectionBase() {}

    // Overload [] operator for reading elements
    T operator[](const Key &key) const
    {
        // Fail if key doesn't exist
        auto it = collectionData.find(key);
        if (it == collectionData.end())
        {
            printf("ERROR - Key [%s] not found!", key.c_str());
            throw std::out_of_range("Key not found!");
        }
        return it->second;
    }

    // Function to create a new item
    virtual T add(const Key &key, T value)
    {
        std::string tempKey = "unknown";
        if (CollectionItemBase *ci = dynamic_cast<CollectionItemBase *>(value))
            tempKey = ci->key;

        if (contains(key))
            throw std::out_of_range("Key [" + tempKey + "] already exists!");

        collectionData[key] = value;
        return collectionData[key];
    }

    bool contains(const Key &key) const { return collectionData.find(key) != collectionData.end(); }

    size_t size() const { return collectionData.size(); }

    const std::unordered_map<Key, T> &getData() const { return collectionData; }

    void clear() { collectionData.clear(); }

    virtual std::string serialize() { return ""; };

    virtual bool update()
    {
        bool result = false;
        for (auto item : collectionData)
            result &= item.second->update();
        return result;
    }
};

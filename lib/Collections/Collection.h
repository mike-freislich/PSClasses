#pragma once
#include <iostream>
#include <stdio.h>
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
            return nullptr;
        }
        return it->second;
    }

    // Function to create a new item
    virtual T add(const Key &key, T value)
    {
        std::string tempKey = "unknown";
        
        if (CollectionItemBase *ci = static_cast<CollectionItemBase *>(value))
            tempKey = ci->key;

        if (key == "")
        {
            printf("Key is empy!");
            return nullptr;
        }         
        if (contains(key))
        {
            printf("Key [%s] already exists!", tempKey.c_str());
            return nullptr;
            //throw std::out_of_range();
        }

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

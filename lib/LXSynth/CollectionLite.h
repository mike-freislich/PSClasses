#pragma once
#include <vector>
#include "CollectionLiteItem.h"

template <typename T, typename KeyType>
class CollectionLite
{
public:
    std::vector<T *> items;

    virtual ~CollectionLite()
    {
        for (auto item : items)
            delete item;
        clear();
    }

    template <typename I>
    I *add(KeyType key)
    {
        if (contains(key))
            return static_cast<I *>(at(key));
        return static_cast<I *>(add(new I(key)));
    }

    T *add(KeyType key)
    {
        if (contains(key))
            return at(key);
        return add(new T(key));
    }

    T *add(T *item)
    {
        if (!contains(item->key))
        {
            items.push_back(item);
            return item;
        }
        else
            return at(item->key);
    }

    // returns null if the key is not found
    T *operator[](KeyType key) { return at(key); }
    bool contains(KeyType key) { return at(key); }
    int count() { return (int)items.size(); }
    void clear() { items.clear(); }

    virtual void update()
    {        
        for (auto i : items)
            i->update();        
    }

protected:
    T *at(KeyType key)
    {
        for (auto item : items)
            if (item->key == key)
                return item;
        return nullptr;
    }
};
#pragma once
#include <iostream>
#include "StringBuilder.h"

class CollectionItemBase
{
public:
    std::string key;
    std::string typeName = "CollectionItemBase";
    std::string displayName;
    virtual ~CollectionItemBase() { printf("deleting %s\n", typeName.c_str()); }
    virtual bool update() { return false; }
    virtual void serialize(StringBuilder *sb) {}

    template <typename T>
    static T *create(const std::string &key, const char *displayName)
    {
        static_assert(std::is_base_of<CollectionItemBase, T>::value, "T must be a derived class of CollectionItemBase");        
        T *t = new (T);
        if (CollectionItemBase *cb = dynamic_cast<CollectionItemBase *>(t))
        {
            cb->key = key;
            cb->displayName = displayName;
        }
        return t;
    }

    virtual void display()
    {
        StringBuilder sb;
        serialize(&sb);
        printf("%s\n", sb.c_str());
    }
};
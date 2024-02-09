#pragma once
#include <iostream>
#include "StringBuilder.h"

static int collectionItemCount = 0;

class CollectionItemBase
{
public:
    std::string key;
    std::string typeName = "CollectionItemBase";
    std::string displayName;
    CollectionItemBase() { collectionItemCount++; }
    virtual ~CollectionItemBase() { printf("deleting %s : %d remaining\n", typeName.c_str(), --collectionItemCount); }
    virtual bool update() { return false; }
    virtual void serialize(PS::StringBuilder *sb) {}

    template <typename T>
    static T *create(const std::string &key, const std::string &displayName)
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
        PS::StringBuilder sb;
        serialize(&sb);
        printf("%s\n", sb.c_str());
    }
};
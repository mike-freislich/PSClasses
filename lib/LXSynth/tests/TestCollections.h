#pragma once

#include "CollectionLite.h"

class Radness : public CollectionLiteItem
{
public:
    const char *value;
    Radness(const char *key) : CollectionLiteItem(key)
    {
        value = key;
    }
    ItemType getType() override { return ItemType::TRadness; }
    bool update() override
    {
        printf("updating Radness\n");
        return true;
    }
};

class RadnessExtra : public Radness
{
public:
    RadnessExtra(const char *key) : Radness(key) {}
    ItemType getType() override { return ItemType::TRadnessExtra; }
    bool update() override
    {
        printf("updating Radness Extra\n");
        return true;
    }
};

void testCollections()
{

    CollectionLite<Radness> c;

    c.add(new RadnessExtra("test"));
    c.add(new Radness("foo"));
    c.add(new Radness("again"));

    for (auto item : c.items)
    {
        if (item->isType(ItemType::TRadnessExtra))
        {
            printf("Item %s\n", item->value);
        }
    }

    if (CollectionLiteItem *item = c["NADA"])
    {
        if (item->isType(ItemType::TRadness))
            printf("%s\n", static_cast<Radness *>(item)->value);
    }

    printf("%d items in collection\n", c.count());
    c.update();
}
#pragma once
#include <string>
#include "PSKeys.h"
#include "PSAllControllers.h"

uint16_t PSObjectCount = 0;

class PSObject
{
public:
    std::string name;
    PSKeys key;

    PSObject(const PSKeys &key, const std::string &name) : key(key), name(name) {
        PSObjectCount ++;      
        printf("PSObject [%s] added : %d PSObjects in memory\n", name.c_str(), PSObjectCount);
    }

    virtual ~PSObject() {
        PSObjectCount --;
        printf("PSObject [%s] freed : %d PSObjects in memory\n", name.c_str(), PSObjectCount);        
    }
    //PSController *asController() { return static_cast<PSController *>(this); }


};

/*
// PSObject(int k, const std::string &n) : key(k), name(n) {}
//  static PSObject findByKey(const PSObjectVector &objects, int searchKey)
//  {
//      auto it = std::find_if(objects.begin(), objects.end(),
//          [searchKey](PSObject obj)
//          { return obj.key == searchKey; });
//      if (it != objects.end())
//          return *it;
//      else
//          return PSObject(-1, "null");
//  }

// class PSTest : public PSObject
// {
// public:
//     uint32_t data;
//     PSTest(int k, const std::string &n) : PSObject(k, n) {}
// };

// class PSTest2 : public PSObject
// {
// public:
//     std::string s = "foo";
//     PSTest2(int k, const std::string &n) : PSObject(k, n) {}
// };

// void testPSTest()
// {

//     PSObjectVector v;
//     v.push_back(PSTest(1, "testing"));
//     v.push_back(PSTest2(2, "foo"));
//     v.push_back(PSTest(3, "asddq"));
//     v.push_back(PSTest2(20, "foo20"));

//     PSObject result = PSObject::findByKey(v, 2);
//     if (result.key != -1)
//     {
//         printf("sucess! found object %s\n", result.name.c_str());
//     }
// }

*/
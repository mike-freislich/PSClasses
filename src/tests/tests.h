#pragma once

//#include "ControllerManager.h"
//#include "ParameterManager.h"
//#include "SceneManager.h"
//#include "ModuleManager.h"
//#include "testAudioUnitFactory.h"
//#include "AudioDerived.h"
#include "ParameterList.h"

void testCollection();

void runTests()
{
    //testCollection();
    //testL();
    //testAudioUnitFactory();
    //testAudioDerived();
    testParameters();
}

#pragma region alpha tests
/// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----



// class Controller : public CollectionItemBase
// {
// public:
//     int pin;

//     virtual void display()
//     {
//         StringBuilder sb;
//         serialize(&sb);
//         printf("%s\n", sb.c_str());
//     }

//     template <typename T>
//     static T *create(int pin, const char *displayName)
//     {
//         static_assert(std::is_base_of<Controller, T>::value, "T must be a derived class of Controller");
//         T *c = new T();
//         c->pin = pin;
//         c->displayName = displayName;
//         return c;
//     }

//     virtual void serialize(StringBuilder *sb)
//     {
//         sb->begin()
//             ->addPair("key", key)
//             ->add(",")
//             ->addPair("type", typeName)
//             ->add(",")
//             ->addPair("name", displayName)
//             ->add(",")
//             ->addPair("pin", pin);
//     };

// protected:
//     float _value;
// };



// class Button : public Controller
// {
// public:
//     Button() { typeName = "Button"; }
//     bool isPressed() { return _value > 0; }

//     static Button *create(int pin, const char *displayName)
//     {
//         Button *newButton = Controller::create<Button>(pin, displayName);
//         return newButton;
//     }

//     void serialize(StringBuilder *sb) override
//     {
//         Controller::serialize(sb);
//         sb->add(",")->addPair("state", isPressed());
//     }
// };

// class Potentiometer : public Controller
// {
// public:
//     Potentiometer() { typeName = "Potentiometer"; }
//     bool linear = true;

//     static Potentiometer *create(int pin, const char *displayName, bool linear)
//     {
//         Potentiometer *newPot = Controller::create<Potentiometer>(pin, displayName);
//         newPot->linear = linear;
//         return newPot;
//     }

//     void serialize(StringBuilder *sb) override
//     {
//         Controller::serialize(sb);
//         sb->add(",")->addPair("taper", linear);
//     }
// };

// class ControllerCollection : public CollectionBase<std::string, Controller *>
// {
// public:
//     ~ControllerCollection()
//     {
//         for (auto &pair : collectionData)
//             delete pair.second;
//     }

//     Controller *add(const std::string &key, Controller *value) override
//     {
//         if (contains(key))
//         {
//             delete value;     // delete duplicate received
//             return collectionData[key]; // return existing item
//         }
//         value->key = key.c_str();
//         return CollectionBase::add(key, value);
//     }

//     std::string serialize() override
//     {
//         StringBuilder sb;
//         sb.startArray("CONTROLLERS");
//         int count = 0;
//         for (auto &pair : collectionData)
//         {
//             sb.startElement();
//             if (Controller *c = pair.second)
//             {
//                 c->serialize(&sb);
//                 count++;
//             }
//             sb.endElement();
//             if (count < collectionData.size())
//                 sb.add(",");
//         }
//         sb.endArray();
//         return sb.toString();
//     }

// private:
// };

#pragma endregion

// void testCollection()
// {    
//     try
//     {        
//         Controllers.add(CTRL_BTN_DataG, CButton::create(CTRL_BTN_DataG, 12, "enter"));
//         Controllers.add(CTRL_BTN_Shift, CButton::create(CTRL_BTN_Shift, 17, "shift"));
//         Controllers.add(CTRL_POT_DataA, CPotentiometer::create(CTRL_POT_DataA, 22, "Env-Attack"));
        
//         // for (const auto &pair : Controllers.getData())
//         //     if (Controller *c = pair.second)                                
//         //         c->display();        

//         Parameters.add(PARM_AENVa_AMOUNT, Parameter::create(PARM_AENVa_AMOUNT, "lvl"));
//         Parameters.add(PARM_AENVa_ATTACK, Parameter::create(PARM_AENVa_ATTACK, "atk"));
//         Parameters.add(PARM_AENVa_HOLD, Parameter::create(PARM_AENVa_HOLD, "hld"));
//         Parameters.add(PARM_AENVa_DECAY, Parameter::create(PARM_AENVa_DECAY, "dec"));
//         Parameters.add(PARM_AENVa_SUSTAIN, Parameter::create(PARM_AENVa_SUSTAIN, "sus"));
//         Parameters.add(PARM_AENVa_RELEASE, Parameter::create(PARM_AENVa_RELEASE, "rel"));

//         // for (const auto &pair : Parameters.getData())
//         //     if (Parameter *p = pair.second)                                
//         //         p->display();        

//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     printf("{\n%s,\n%s\n}\n", Controllers.serialize().c_str(), Parameters.serialize().c_str());    
// }
#pragma once

#include "Utils.h"
#include "Variant.h"

//Reflection
#define MRT_GET_PROP_NAME(var) #var

namespace MortarCore
{

class MortarObject;

    struct ClassMeta
    {
        MortarObject* m_Object;
        std::unordered_map<std::string, Variant> m_Properties; // Stores a list of all properties that can be accessed in this class
    };

    class Reflection
    {
    public:
    
        // Template method to register a class by type
        static void RegisterObject(MortarObject* mObject);
        
        // Used to register a variant property from a class
        static void RegisterProperty(uint64_t mID, std::string propName, VariantType type, void* value);

        static ClassMeta& GetClassMeta(uint64_t id) { return m_ObjectRegistry[id]; }

        template <typename T>
        static T* GetMortarObject(uint64_t id); const
        static void FreeMortarObject(uint64_t id);

    private:

        static std::unordered_map<uint64_t, ClassMeta> m_ObjectRegistry;
    };

}
#include "Reflection.h"
#include "MortarObject.h"

namespace MortarCore
{
    std::unordered_map<uint64_t, ClassMeta> Reflection::m_ObjectRegistry;

    
    void Reflection::RegisterObject(MortarObject* mObject)
    {
        std::string name = typeid(*mObject).name();
        try
        {
            ClassMeta meta = { mObject };
            Reflection::m_ObjectRegistry.emplace(mObject->GetID(), meta);
    
            MRT_PRINT("Object Registered in ClassDB: " + name);
        }
        catch(const std::exception& e)
        {
            MRT_PRINT_ERR("Object could not be added due to collision: " + name);
            MRT_PRINT_ERR(e.what());
        }
    }

    void Reflection::RegisterProperty(uint64_t mID, std::string propName, VariantType type, void* value)
    {
        Variant var(propName, type, value);
        Reflection::m_ObjectRegistry[mID].m_Properties[propName] = var;

        MRT_PRINT("Property Registered in ClassDB: " + propName);

    }

    template <typename T>
    T* Reflection::GetMortarObject(uint64_t id) { return m_ObjectRegistry[id].m_Object; } const

    void Reflection::FreeMortarObject(uint64_t id)
    {
        MortarObject* ref = m_ObjectRegistry[id].m_Object;     
        m_ObjectRegistry.erase(id);        
        delete ref;
    } 
       
   
}
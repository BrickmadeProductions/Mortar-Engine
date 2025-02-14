#pragma once

#include "Utils.h"

namespace MortarCore
{
    enum class VariantType
    {
        INT,
        BOOL,
        STRING,
        FLOAT,
        DOUBLE,
        VEC2,
        VEC3,
        VEC4,
        OBJECT,
    };


    class Variant
    {
    public:

        Variant() = default;
        Variant(std::string name, VariantType type, void* valuePtr) : m_Name(name), m_Type(type), m_Value(valuePtr) {}


        VariantType GetType() { return m_Type; }
        std::string GetName() { return m_Name; }
        
        template <typename T>
        T* GetValue(){ return reinterpret_cast<T*>(m_Value); }

    private:

        std::string m_Name;
        VariantType m_Type;
        void* m_Value;
    };
}
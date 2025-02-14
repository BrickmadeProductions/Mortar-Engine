#pragma once

#include "Utils.h"
#include "core/math/Math.h"
#include "Reflection.h"

namespace MortarCore 
{

    class MortarObject {
    public:

        MortarObject() : m_ID(MRTMath::R64Int(0, uint64_t(-1))) { Reflection::RegisterObject(this);}  // FIX ID GENERATION, POSIBLE COLLISIONS TODO
        virtual ~MortarObject() = default;

        template <class T, typename ... Args>
        static Ref<T> Create(Args&& ... args)
        { 
            Ref<T> mObject = CreateRef<T>(std::forward<Args>(args)...);
            mObject->RegisterProperties();
            return mObject; 
        }

        uint64_t GetID() const { return m_ID; }
        virtual std::string ToString() const { return "MortarObject"; }

        virtual void RegisterProperties() {}

    protected:

        uint64_t m_ID;

    };

} 
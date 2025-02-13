#pragma once

#include "Utils.h"

namespace MortarCore
{
    class Resource
    {
        public:
            Resource() = default;
            Resource(Resource& copy) = default;
            virtual ~Resource() = default;

        template <class T>
        constexpr Ref<T> MakeCopy() 
        { 
            auto* copy = dynamic_cast<T*>(this);
            return CreateRef<T>(*copy); 
        }
    };
    
} 

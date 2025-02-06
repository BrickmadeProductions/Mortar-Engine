#pragma once

#include "Utils.h"

namespace MortarCore
{
	class FrameBuffer
    {
    public:
        virtual ~FrameBuffer() = default;

        virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

        static Ref<FrameBuffer> CreateBuffer();

    protected:

		uint32_t m_BufferID;
    };
}
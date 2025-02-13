#pragma once

#include "Utils.h"
#include "core/resource/Texture.h"

namespace MortarCore
{
    class ImageLoader
    {
        public:

            static unsigned char* LoadImage(const char* path, int width, int height, int m_Channels);
            static void FreeImage(unsigned char* Image);
    };
}

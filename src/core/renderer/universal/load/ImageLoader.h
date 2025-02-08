#pragma once

#include "Utils.h"

namespace MortarCore
{
    class Texture
    {
        public:

            Texture(const char* path, int width, int height, bool useAlpha);
            ~Texture();

            void SetTextureID(uint32_t id) { m_TextureID = id; }
            uint32_t GetTextureID() { return m_TextureID; }

            unsigned char* GetData() { return m_Data; }
            int GetChannels () { return m_Channels; }
            int GetWidth() { return m_Width; }
            int GetHeight() { return m_Height; }

        private:

            uint32_t m_TextureID;

            unsigned char* m_Data;

            int m_Width, m_Height;
            int m_Channels = 4;
    };
    
    class ImageLoader
    {
        public:

            static void FreeImage(unsigned char* Image);
    };
}

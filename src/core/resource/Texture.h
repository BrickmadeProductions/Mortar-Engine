
#pragma once

#include "Utils.h"
#include "Resource.h"

namespace MortarCore
{
    class Texture : public Resource
    {
        public:

            Texture(const char* path, int width, int height, int channels);
            ~Texture();

            void SetTextureID(uint32_t id) { m_TextureID = id; }
            void SetTextureUnit(uint32_t unit) { m_TextureUnit = unit; }
            
            uint32_t GetTextureID() { return m_TextureID; }
            uint32_t GetTextureUnit() { return m_TextureUnit; }

            unsigned char* GetData() { return m_Data; }
            int GetChannels () { return m_Channels; }
            int GetWidth() { return m_Width; }
            int GetHeight() { return m_Height; }

        private:

            uint32_t m_TextureID, m_TextureUnit;

            unsigned char* m_Data;

            int m_Width, m_Height;
            int m_Channels = 4;
    };
}
#include "Texture.h"
#include "core/renderer/universal/load/ImageLoader.h"

namespace MortarCore
{
    Texture::Texture(const char* path, int width, int height, int channels) : m_Width(width), m_Height(height), m_Channels(channels)
    {
        m_Data = ImageLoader::LoadImage(path, width, height, m_Channels);

        if (!m_Data) // Check if the texture was loaded successfully
        {
            MRT_PRINT_ERR("Failed to load texture: " + std::string(path));
            MRT_CORE_ASSERT(false);
        }
    }
    Texture::~Texture() 
    {
        if (m_Data) ImageLoader::FreeImage(m_Data); // Free the texture data
    }
}
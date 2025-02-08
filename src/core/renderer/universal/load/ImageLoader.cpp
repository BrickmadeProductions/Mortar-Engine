#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION    
#include "core/utils/stb_image.h"

namespace MortarCore
{
    Texture::Texture(const char* path, int width, int height, bool useAlpha) : m_Width(width), m_Height(height)
    {
        m_Channels = useAlpha ? 4 : 3;
        m_Data = stbi_load(path, &width, &height, &m_Channels, 0);

        if (!m_Data) // Check if the texture was loaded successfully
        {
            MRT_PRINT_ERR("Failed to load texture: " + std::string(path));
            MRT_CORE_ASSERT(false); // Or handle it however you want
        }
    }
    Texture::~Texture() 
    {
        if (m_Data) 
        {
            stbi_image_free(m_Data); // Free the texture data
        }
    }

    void ImageLoader::FreeImage(unsigned char* Image) { stbi_image_free(Image); }
} 

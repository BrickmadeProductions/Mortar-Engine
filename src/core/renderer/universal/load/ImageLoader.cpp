#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION    
#include "core/utils/stb_image.h"

namespace MortarCore
{
    unsigned char* ImageLoader::LoadImage(const char* path, int width, int height, int m_Channels) { return stbi_load(path, &width, &height, &m_Channels, 0); }
    void ImageLoader::FreeImage(unsigned char* Image) { stbi_image_free(Image); }
} 

#define STB_IMAGE_IMPLEMENTATION
#include "../External/stb/stb_image.h"

#include "Texture.h"
#include "../File/File.h"

GAE_Texture_t* GAE_Texture_create(const char* path)
{
    GAE_File_t* file = GAE_File_create(path);
    GAE_Texture_t* texture = GAE_Texture_createFromFile(file);
    GAE_Texture_load(texture, GAE_FALSE);

    return texture;
}

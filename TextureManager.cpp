#include "TextureManager.h"

TextureManager::~TextureManager()
{
    for (TextureMap::const_iterator it = textures.begin(); (it != textures.end()); it++)
        delete it->second;
}

Texture* TextureManager::getTexture(const std::string& id)
{
    TextureMap::const_iterator it = textures.find(id);
    if (it == textures.end()) return NULL;
    else return it->second;
}

Texture* TextureManager::loadTextureFromFile(const std::string& id, const std::string& filename)
{
    // Load texture from specified file
    Texture* texture = new Texture(filename);
    // Added loaded texture to the map using the given ID
    textures.insert( std::pair<std::string, Texture*>(id, texture) );
}

TextureManager TextureManager::getInstance()
{
    static TextureManager texManager;
    return texManager;
}

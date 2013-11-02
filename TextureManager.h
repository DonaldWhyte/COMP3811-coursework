#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include "Texture.h"

class TextureManager
{

public:
    // Deletes all textures loaded with this manager
    virtual ~TextureManager();
    
    /* Retrieve texture with given ID. If a texture with the ID doesn't
     * exist, then a NULL pointer is returned. */
    Texture* getTexture(const std::string& id);
    /* Load texture from an image file. The loaded texture is stored
     * with the given ID (overwriting an existing texture if it
     * exists). */
    Texture* loadTextureFromFile(const std::string& id, const std::string& filename);
    
    static TextureManager* getInstance();
    
private:
    static TextureManager* instance;

    typedef std::map<std::string, Texture*> TextureMap;
    TextureMap textures;
    
};

#endif

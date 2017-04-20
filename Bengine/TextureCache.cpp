//
//  TextureCache.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 11/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "TextureCache.hpp"
#include "ImageLoader.hpp"

#include <iostream>

namespace Bengine {

    TextureCache::TextureCache(){}

    TextureCache::~TextureCache(){}

    GLTexture TextureCache::getTexture(std::string texturePath)
    {
        auto it = textureMap_.find(texturePath);
        if( it== textureMap_.end()){
            GLTexture newTexture = ImageLoader::loadPNG(texturePath);
            textureMap_[texturePath] = newTexture;
            return newTexture;
        }
        return it->second;
    }
}

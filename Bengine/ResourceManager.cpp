//
//  ResourceManager.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 11/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "ResourceManager.hpp"

namespace Bengine {

    TextureCache ResourceManager::_textureCache;

    GLTexture ResourceManager::getTexture(std::string texturePath)
    {
        return  _textureCache.getTexture(texturePath);
    }
}

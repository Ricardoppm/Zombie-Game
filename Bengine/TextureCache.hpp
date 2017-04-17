//
//  TextureCache.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 11/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef TextureCache_hpp
#define TextureCache_hpp

#include <map>
#include <string>
#include "GLTexture.h"

namespace Bengine {

    class TextureCache
    {
    public:
        TextureCache();
        ~TextureCache();

        GLTexture getTexture(std::string texturePath);
        
    private:
        std::map<std::string, GLTexture> textureMap;
    };
}
#endif /* TextureCache_hpp */

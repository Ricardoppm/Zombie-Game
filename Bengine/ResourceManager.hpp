//
//  ResourceManager.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 11/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <string>

#include "TextureCache.hpp"

namespace Bengine {

    class ResourceManager
    {
    public:
        static GLTexture getTexture(std::string texturePath);
        
    private:
        static TextureCache textureCache_;
        
    };
}
#endif /* ResourceManager_hpp */

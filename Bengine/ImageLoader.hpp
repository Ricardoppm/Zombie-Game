//
//  ImageLoader.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 11/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef ImageLoader_hpp
#define ImageLoader_hpp

#include <string>

#include "GLTexture.h"

namespace Bengine {

    class ImageLoader
    {
    public:
        static GLTexture loadPNG( std::string filePath);
    };
}
#endif /* ImageLoader_hpp */

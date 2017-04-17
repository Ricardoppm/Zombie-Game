//
//  GLTexture.h
//  OPENGL
//
//  Created by Ricardo Martins on 11/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef GLTexture_h
#define GLTexture_h

#include <OpenGL/gl3.h>

namespace Bengine {

    struct GLTexture
    {
        GLuint id;
        int width;
        int height;

    };
}
#endif /* GLTexture_h */

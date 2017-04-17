//
//  Sprite.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 10/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <OpenGL/gl3.h>
#include <string>

#include "GLTexture.h"

namespace Bengine {
    
    class Sprite
    {
    public:
        Sprite();
        ~Sprite();
        
        void init(float x, float y, float width, float height, std::string texturePath);
        
        void draw();
        
    private:
        int _x;
        int _y;
        int _width;
        int _heigth;

        GLuint _vboID;
        
        GLTexture _texture;
    };
}
#endif /* Sprite_hpp */

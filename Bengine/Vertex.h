//
//  Vertex.h
//  OPENGL
//
//  Created by Ricardo Martins on 10/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Vertex_h
#define Vertex_h

#include <OpenGL/gl3.h>

namespace Bengine {

    struct Position{
        float x;
        float y;
    };

    struct Color{
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    };

    struct UV{
        float u;
        float v;
    };

    // vertex definition
    struct Vertex{ 
        Position position;
        Color color;
        UV uv;
        
        void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a){
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }
        
        void setUV(float u, float v){
            uv.u = u;
            uv.v = v;
        }
        
        void setPosition(float x, float y){
            position.x = x;
            position.y = y;
        }
    };
}

#endif /* Vertex_h */

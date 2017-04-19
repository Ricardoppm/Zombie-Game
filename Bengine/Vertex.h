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

    struct ColorRGBA8{
        ColorRGBA8() : r(0), g(0), b(0), a(0) {}
        ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A):
        r(R), g(G), b(B), a(A){}
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
        ColorRGBA8 color;
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

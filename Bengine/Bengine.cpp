//
//  Bengine.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 15/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Bengine.hpp"

namespace Bengine {
    int init()
    {
        //Initialize SDL
        if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
            return 1;
        }
        else{
            // Tell SDL that we want a double buffered window, avoiding flickering
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        }
        return 0;
    }
        
}

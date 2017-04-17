//
//  Window.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 15/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Window.hpp"

#include "errors.hpp"

namespace Bengine {

    Window::Window(){}

    Window::~Window(){}

    int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
    {
        Uint32 flags = SDL_WINDOW_OPENGL;
        
        if( currentFlags & WINDOW_INVISIBLE)
            flags |= SDL_WINDOW_HIDDEN;
        if( currentFlags & WINDOW_FULLSCREEN)
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        if( currentFlags & WINDOW_BORDERLESS)
            flags |= SDL_WINDOW_BORDERLESS;
        
        
        //Create window
        _sdlWindow = SDL_CreateWindow( windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
        if( _sdlWindow == NULL )
        {
            std::string error = "Window could not be created! SDL_Error:";
            error.append(SDL_GetError());
            fatalError(error);
        }
        else
        {
            // Update OpenGL Core to 3.3 (from 2.1)
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
            
            // Set up OpenGL context
            SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
            if( glContext == nullptr){
                fatalError("SDL context couldn't be created!");
            }
            
            // In order to make things work??
            GLuint vertexArrayID;
            glGenVertexArrays(1, &vertexArrayID);
            glBindVertexArray(vertexArrayID);
            
            // Set window color
            glClearColor(1.0f, 1.0f, 1.f, 1.0);
            
            // Check OpenGL version
            std::printf("*** OpenGL version: %s ***\n", glGetString(GL_VERSION));
            
            // Set VSYNC - 1 = enable
            SDL_GL_SetSwapInterval(0);
            
            // Enable alpha blend
            glEnable(GL_BLEND);
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
        }
        return 1;
    }

    void Window::swapBuffer()
    {
        // Swap out buffers and draw on screen
        SDL_GL_SwapWindow(_sdlWindow);
    }
}

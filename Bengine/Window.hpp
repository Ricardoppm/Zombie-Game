//
//  Window.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 15/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <string>

namespace Bengine {

    enum windowFlags{ WINDOW_INVISIBLE = 0x1, WINDOW_FULLSCREEN= 0x2, WINDOW_BORDERLESS=0x4 };

    class Window
    {
    public:
        Window();
        ~Window();

        int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags );
        
        void swapBuffer();
        
        int getScreenWidth(){ return _screenWidth;}
        int getScreenHeight(){ return _screenHeight;}
        
    private:
        SDL_Window* _sdlWindow;
        int _screenWidth;
        int _screenHeight;
    };
}
#endif /* Window_hpp */

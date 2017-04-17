//
//  errors.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 10/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "errors.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <cstdlib>

namespace Bengine {

    void fatalError( std::string errorString)
    {
        std::cout << errorString << std::endl;
        std::cout << "Enter any key to quit!\n";
        int temp;
        std::cin >> temp;
        SDL_Quit();
        exit(-1);
    }
}

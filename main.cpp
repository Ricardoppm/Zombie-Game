//
//  main.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 17/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include <iostream>

#include "MainGame.hpp"


int main(int argc, const char * argv[]) {
    
    MainGame mainGame;
    
    mainGame.run();
    
    SDL_Delay(3000);
    
    return 0;
}

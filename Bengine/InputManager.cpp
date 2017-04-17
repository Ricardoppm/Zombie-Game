//
//  InputManager.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 17/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "InputManager.hpp"

namespace Bengine {
    
    InputManager::InputManager(): _mouseCoords(0.f)
    {}
    
    InputManager::~InputManager(){}
    
    void InputManager::pressKey(unsigned int keyID){ _keyMap[keyID] = true; }
    
    void InputManager::releaseKey(unsigned int keyID){ _keyMap[keyID] = false; }
    
    void InputManager::setMouseCoords(float x, float y){
        _mouseCoords.x = x;
        _mouseCoords.y = y;
    }
    
    bool InputManager::isKeyPressed(unsigned int keyID) const
    {
        auto it = _keyMap.find(keyID);
        if( it != _keyMap.end())
            return it->second;
        return false;
    }
}

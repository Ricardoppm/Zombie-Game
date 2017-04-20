//
//  InputManager.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 17/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "InputManager.hpp"

namespace Bengine {
    
    InputManager::InputManager() {}
    
    InputManager::~InputManager() {}
    
    void InputManager::update()
    {
        // Loop through key map and copy iy to previousKeyMap
        for (auto& it : keyMap_) {
            previousKeyMap_[it.first] = it.second;
        }
    }
    
    void InputManager::pressKey(unsigned int keyID){ keyMap_[keyID] = true; }
    
    void InputManager::releaseKey(unsigned int keyID){ keyMap_[keyID] = false; }
    
    void InputManager::setMouseCoords(float x, float y){
        mouseCoords_.x = x;
        mouseCoords_.y = y;
    }
    
    bool InputManager::isKeyDown(unsigned int keyID) const
    {
        auto it = keyMap_.find(keyID);
        if( it != keyMap_.end())
            return it->second;
        return false;
    }
    
    bool InputManager::isKeyPressed(unsigned int keyID) const
    {
        if( isKeyDown(keyID) && !wasKeyDown(keyID))
            return true;
        return false;
    }
    
    bool InputManager::wasKeyDown(unsigned int keyID) const
    {
        auto it = previousKeyMap_.find(keyID);
        if( it != previousKeyMap_.end())
            return it->second;
        return false;
    }
}

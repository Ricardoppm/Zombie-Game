//
//  InputManager.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 17/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef InputManager_hpp
#define InputManager_hpp

#include <unordered_map>
#include <glm/glm.hpp>

namespace Bengine {
    
    class InputManager
    {
    public:
        InputManager();
        ~InputManager();
    
        void pressKey(unsigned int keyID);
        void releaseKey(unsigned int keyID);
        
        void setMouseCoords( float x, float y);
        
        bool isKeyPressed (unsigned int keyID) const;
        
        // Getters
        glm::vec2 getMouseCoords() const { return _mouseCoords; }
        
    private:
        std::unordered_map<unsigned int, bool> _keyMap;
        glm::vec2 _mouseCoords;
        
    };
}

#endif /* InputManager_hpp */

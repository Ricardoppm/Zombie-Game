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
        
        void update();
    
        void pressKey(unsigned int keyID);
        void releaseKey(unsigned int keyID);
        
        void setMouseCoords( float x, float y);
        
        // return true if key is held down
        bool isKeyDown (unsigned int keyID) const;
        
        // Returns true if key was just pressed
        bool isKeyPressed(unsigned int keyID) const;
        
        // Getters
        glm::vec2 getMouseCoords() const { return mouseCoords_; }
        
    private:
        bool wasKeyDown(unsigned int keyID) const;
        
        std::unordered_map<unsigned int, bool> keyMap_;
        std::unordered_map<unsigned int, bool> previousKeyMap_;

        glm::vec2 mouseCoords_ = glm::vec2(0.0f);
        
    };
}

#endif /* InputManager_hpp */

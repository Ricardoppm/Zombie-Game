//
//  Camera2D.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 15/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Camera2D_hpp
#define Camera2D_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Bengine {
    
    class Camera2D
    {
    public:
        Camera2D();
        ~Camera2D();
        
        void init(int screenWidth, int screenHeight);
        
        void update();
        
        glm::vec2 convertScreenToWorld( glm::vec2 screenCoords);
        
        bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);
        
        // Setters
        void setPosition(const glm::vec2& newPosition){ position_ = newPosition; needsMatrixUpdate_=true; };
        void setScale(float newScale){ scale_ = newScale; needsMatrixUpdate_=true; }
        
        
        // Getters
        glm::vec2 getPosition(){ return position_;}
        float getScale(){ return scale_;}
        glm::mat4 getCameraMatrix(){ return cameraMatrix_;}
        
    private:
        int screenWidth_ = 500;
        int screenHeight_ = 360;
        
        bool needsMatrixUpdate_  = true;
        float scale_ = 1.0f;
        glm::vec2 position_ = glm::vec2(0,0);
        glm::mat4 cameraMatrix_ = glm::mat4(1.f);
        glm::mat4 orthoMatrix_ = glm::mat4(1.f);        
    };
}
#endif /* Camera2D_hpp */

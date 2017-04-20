//
//  Camera2D.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 15/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Camera2D.hpp"

namespace Bengine {
    
    Camera2D::Camera2D(){}
    
    Camera2D::~Camera2D(){}
    
    void Camera2D::init(int screenWidth, int screenHeight){
        screenWidth_ = screenWidth;
        screenHeight_ = screenHeight;
        orthoMatrix_ = glm::ortho(0.0f, (float)screenWidth_, 0.0f, (float)screenHeight_);
    }
    
    void Camera2D::update()
    {
        if(needsMatrixUpdate_){
            // Camera translation
            glm::vec3 translate(-position_.x + screenWidth_/2, -position_.y +  screenHeight_/2, 0.0f);
            cameraMatrix_ = glm::translate(orthoMatrix_, translate);
            
            // Camera scale
            glm::vec3 scale(scale_, scale_, 0.0f);
            cameraMatrix_ = glm::scale(glm::mat4(1.0f), scale) * cameraMatrix_;
            
            needsMatrixUpdate_ = false;
        }
    }
    
    glm::vec2 Camera2D::convertScreenToWorld( glm::vec2 screenCoords)
    {
        // Invert screen coordinates
        screenCoords.y = screenHeight_ - screenCoords.y;
        // Make it so that 0 is the center
        screenCoords -= glm::vec2(screenWidth_/2, screenHeight_/2);
        // Scale the coordinates
        screenCoords /= scale_;
        // Translate to the camera position
        screenCoords += position_;
        return screenCoords;
    }
    
    // Simple AABB test to see if object is within camera view
    bool Camera2D::isBoxInView(const glm::vec2 &position, const glm::vec2 &dimensions)
    {
        glm::vec2 scaledScreenDimensions = glm::vec2( screenWidth_, screenHeight_)/scale_;
        
        const float MIN_DISTANCE_X = dimensions.x/2.f + scaledScreenDimensions.x/2.f;
        const float MIN_DISTANCE_Y = dimensions.y/2.f + scaledScreenDimensions.y/2.f;
        
        // Center positions
        glm::vec2 centerPos = position + dimensions/2.f;
        glm::vec2 centerCameraPos = position_;
        
        // Vector from camera to object
        glm::vec2 distVec = centerPos - centerCameraPos;
        
        float xDepth = MIN_DISTANCE_X - std::abs(distVec.x);
        float yDepth = MIN_DISTANCE_Y - std::abs(distVec.y);
        
        // There was a collision
        if( xDepth > 0 && yDepth > 0)
            return true;
        
        // no collision
        return false;
    }
    
}

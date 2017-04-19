//
//  Camera2D.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 15/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Camera2D.hpp"

namespace Bengine {
    
    Camera2D::Camera2D():
    _needsMatrixUpdate(true),
    _scale(1.0f),
    _position(0,0),
    _cameraMatrix(1),
    _screenWidth(500),
    _screenHeight(360),
    _orthoMatrix(1.0f)
    {
    }
    
    Camera2D::~Camera2D()
    {
    }
    
    void Camera2D::init(int screenWidth, int screenHeight){
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        _orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
    }
    
    void Camera2D::update()
    {
        if(_needsMatrixUpdate){
            // Camera translation
            glm::vec3 translate(-_position.x + _screenWidth/2, -_position.y +  _screenHeight/2, 0.0f);
            _cameraMatrix = glm::translate(_orthoMatrix, translate);
            
            // Camera scale
            glm::vec3 scale(_scale, _scale, 0.0f);
            _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
            
            _needsMatrixUpdate = false;
        }
    }
    
    glm::vec2 Camera2D::convertScreenToWorld( glm::vec2 screenCoords)
    {
        // Invert screen coordinates
        screenCoords.y = _screenHeight - screenCoords.y;
        // Make it so that 0 is the center
        screenCoords -= glm::vec2(_screenWidth/2, _screenHeight/2);
        // Scale the coordinates
        screenCoords /= _scale;
        // Translate to the camera position
        screenCoords += _position;
        return screenCoords;
    }

    // Simple AABB test to see if object is within camera view
    bool Camera2D::isBoxInView(const glm::vec2 &position, const glm::vec2 &dimensions)
    {
        glm::vec2 scaledScreenDimensions = glm::vec2( _screenWidth, _screenHeight)/_scale;
        
        const float MIN_DISTANCE_X = dimensions.x/2.f + scaledScreenDimensions.x/2.f;
        const float MIN_DISTANCE_Y = dimensions.y/2.f + scaledScreenDimensions.y/2.f;

        // Center positions
        glm::vec2 centerPos = position + dimensions/2.f;
        glm::vec2 centerCameraPos = _position;
        
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

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

    
    
}

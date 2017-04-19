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
        void setPosition(const glm::vec2& newPosition){ _position = newPosition; _needsMatrixUpdate=true; };
        void setScale(float newScale){ _scale = newScale; _needsMatrixUpdate=true; }
        
        
        // Getters
        glm::vec2 getPosition(){ return _position;}
        float getScale(){ return _scale;}
        glm::mat4 getCameraMatrix(){ return _cameraMatrix;}
    
    private:
        int _screenWidth;
        int _screenHeight;
        
        bool _needsMatrixUpdate;
        float _scale;
        glm::vec2 _position;
        glm::mat4 _cameraMatrix;
        glm::mat4 _orthoMatrix;
    };
}
#endif /* Camera2D_hpp */

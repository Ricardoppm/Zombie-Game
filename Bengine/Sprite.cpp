//
//  Sprite.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 10/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Sprite.hpp"

#include <cstddef>

#include "Vertex.h"
#include "ResourceManager.hpp"

namespace Bengine {
    
    Sprite::Sprite() {}

    Sprite::~Sprite()
    {
        if(vboID_){
            glDeleteBuffers(1, &vboID_);
        }
    }

    void Sprite::init(float x, float y, float width, float height, std::string texturePath)
    {
        x_ = x;
        y_ = y;
        width_ = width;
        heigth_ = height;
        
        texture_ = ResourceManager::getTexture(texturePath);
        
        if(vboID_==0){
            glGenBuffers(1, &vboID_);
        }
        
        Vertex vertexData[6]; // 6 vertexis
        
        // first triangle
        vertexData[0].setPosition(x + width, y + height);
        vertexData[0].setUV(1.f, 1.f);

        vertexData[1].setPosition(x, y + height);
        vertexData[1].setUV(0.f, 1.f);

        vertexData[2].setPosition(x, y);
        vertexData[2].setUV(0.f, 0.f);

        // second triangle
        vertexData[3].setPosition(x, y);
        vertexData[3].setUV(0.f, 0.f);

        vertexData[4].setPosition(x + width, y);
        vertexData[4].setUV(1.f, 0.f);

        vertexData[5].setPosition(x + width, y + height);
        vertexData[5].setUV(1.f, 1.f);

        
        for (int i = 0; i<6; i++) {
            vertexData[i].setColor(255, 0, 0, 255);
        }
        
        vertexData[1].setColor(0, 255, 0, 255);

        vertexData[4].setColor(0, 0, 255, 255);
        
        // Tell OpenGL to bind our vertex buffer object
        glBindBuffer(GL_ARRAY_BUFFER, vboID_);
        // Upload the data to the GPU
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData , GL_STATIC_DRAW);
        // Unbind the buffer (optional)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // Draws the sprite to the screen
    void Sprite::draw()
    {
        glBindTexture(GL_TEXTURE_2D, texture_.id);
        
        // bind the buffer object
        glBindBuffer(GL_ARRAY_BUFFER, vboID_);
        
        // tell OpenGL that we want to use the first
        // attribute array. We only need one array right now
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        
        // Point OpenGL to the data in our VBO
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position) );
        // This is the color attribute pointes
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color) );
        // This is the UV attribute pointes
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv) );

        
        // Draw the 6 vertices to the screen
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // Disable the vertex attribute array
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        //Unbind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

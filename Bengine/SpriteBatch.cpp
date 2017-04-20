//
//  SpriteBatch.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 17/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "SpriteBatch.hpp"

namespace Bengine {
    
    SpriteBatch::SpriteBatch(){}
    
    SpriteBatch::~SpriteBatch(){}
    
    void SpriteBatch::init()
    {
        createVertexArray();
    }
    
    void SpriteBatch::begin(GlyphSortType sortType)
    {
        sortType_ = sortType;
        renderBatches_.clear();
        glyphs_.clear();
    }
    void SpriteBatch::end()
    {
        glyphPointers_.resize(glyphs_.size());
        for(int i = 0; i< glyphs_.size(); i++){
            glyphPointers_[i] = &glyphs_[i];
        }
        sortGlyphs();
        createRenderBatches();
    }
    
    void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color )
    {
        glyphs_.emplace_back(destRect, uvRect, texture, depth, color);
    }
    
    void SpriteBatch::renderBatch()
    {
        glBindVertexArray(vao_);
        
        for (int i=0; i < renderBatches_.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, renderBatches_[i].texture);
            
            glDrawArrays(GL_TRIANGLES, renderBatches_[i].offset, renderBatches_[i].numVertices);
        }
        glBindVertexArray(0);
    }
    
    void SpriteBatch::createRenderBatches()
    {
        std::vector<Vertex> vertices;
        vertices.resize(glyphs_.size() *6);
        if( glyphs_.empty())
            return;
        
        int offset = 0;
        int cv = 0; // current vertex
        renderBatches_.emplace_back(offset, 6, glyphPointers_[0]->texture);
        vertices[cv++] = glyphPointers_[0]->topLeft;
        vertices[cv++] = glyphPointers_[0]->bottomLeft;
        vertices[cv++] = glyphPointers_[0]->bottomRight;
        vertices[cv++] = glyphPointers_[0]->bottomRight;
        vertices[cv++] = glyphPointers_[0]->topRight;
        vertices[cv++] = glyphPointers_[0]->topLeft;
        offset+=6;
        
        for(int cg = 1; cg < glyphs_.size(); cg++){
            if( glyphPointers_[cg]->texture != glyphPointers_[cg-1]->texture){
                renderBatches_.emplace_back(offset, 6, glyphPointers_[cg]->texture);
            }
            else{
                renderBatches_.back().numVertices +=6;
            }
            vertices[cv++] = glyphPointers_[cg]->topLeft;
            vertices[cv++] = glyphPointers_[cg]->bottomLeft;
            vertices[cv++] = glyphPointers_[cg]->bottomRight;
            vertices[cv++] = glyphPointers_[cg]->bottomRight;
            vertices[cv++] = glyphPointers_[cg]->topRight;
            vertices[cv++] = glyphPointers_[cg]->topLeft;
            offset+=6;
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        // Orphan the data
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        // Upload data
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
    }
    
    void SpriteBatch::createVertexArray()
    {
        if( vao_ == 0){
            glGenVertexArrays(1, &vao_);
        }
        glBindVertexArray(vao_);
        
        if( vbo_ == 0){
            glGenBuffers(1, &vbo_);
        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        
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
        
        glBindVertexArray(0);
        
    }
    
    void SpriteBatch::sortGlyphs()
    {
        switch (sortType_) {
            case GlyphSortType::BACK_TO_FRONT :
                std::stable_sort(glyphPointers_.begin(), glyphPointers_.end(), compareBackToFront);
                break;
                
            case GlyphSortType::FRONT_TO_BACK:
                std::stable_sort(glyphPointers_.begin(), glyphPointers_.end(), compareFrontToBack);
                break;
                
            case GlyphSortType::TEXTURE:
                std::stable_sort(glyphPointers_.begin(), glyphPointers_.end(), compareTexture);
                break;
        }
    }
    
    bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b){ return (a->depth < b->depth);  }
    bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b){ return (a->depth > b->depth); }
    bool SpriteBatch::compareTexture(Glyph* a, Glyph* b){ return (a->texture < b->texture); }
    
    
}

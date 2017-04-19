//
//  SpriteBatch.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 17/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "SpriteBatch.hpp"

namespace Bengine {
    
    SpriteBatch::SpriteBatch()
    :_vbo(0), _vao(0)
    {}
    SpriteBatch::~SpriteBatch(){}
    
    void SpriteBatch::init()
    {
        createVertexArray();
    }
    
    void SpriteBatch::begin(GlyphSortType sortType)
    {
        _sortType = sortType;
        _renderBatches.clear();
        _glyphs.clear();
    }
    void SpriteBatch::end()
    {
        _glyphPointers.resize(_glyphs.size());
        for(int i = 0; i< _glyphs.size(); i++){
            _glyphPointers[i] = &_glyphs[i];
        }
        sortGlyphs();
        createRenderBatches();
    }
    
    void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color )
    {
        _glyphs.emplace_back(destRect, uvRect, texture, depth, color);
    }
    
    void SpriteBatch::renderBatch()
    {
        glBindVertexArray(_vao);
        
        for (int i=0; i < _renderBatches.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
            
            glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
        }
        glBindVertexArray(0);
    }
    
    void SpriteBatch::createRenderBatches()
    {
        std::vector<Vertex> vertices;
        vertices.resize(_glyphs.size() *6);
        if( _glyphs.empty())
            return;
        
        int offset = 0;
        int cv = 0; // current vertex
        _renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);
        vertices[cv++] = _glyphPointers[0]->topLeft;
        vertices[cv++] = _glyphPointers[0]->bottomLeft;
        vertices[cv++] = _glyphPointers[0]->bottomRight;
        vertices[cv++] = _glyphPointers[0]->bottomRight;
        vertices[cv++] = _glyphPointers[0]->topRight;
        vertices[cv++] = _glyphPointers[0]->topLeft;
        offset+=6;
        
        for(int cg = 1; cg < _glyphs.size(); cg++){
            if( _glyphPointers[cg]->texture != _glyphPointers[cg-1]->texture){
                _renderBatches.emplace_back(offset, 6, _glyphPointers[cg]->texture);
            }
            else{
                _renderBatches.back().numVertices +=6;
            }
            vertices[cv++] = _glyphPointers[cg]->topLeft;
            vertices[cv++] = _glyphPointers[cg]->bottomLeft;
            vertices[cv++] = _glyphPointers[cg]->bottomRight;
            vertices[cv++] = _glyphPointers[cg]->bottomRight;
            vertices[cv++] = _glyphPointers[cg]->topRight;
            vertices[cv++] = _glyphPointers[cg]->topLeft;
            offset+=6;
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        // Orphan the data
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        // Upload data
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
    }
    
    void SpriteBatch::createVertexArray()
    {
        if( _vao == 0){
            glGenVertexArrays(1, &_vao);
        }
        glBindVertexArray(_vao);
        
        if( _vbo == 0){
            glGenBuffers(1, &_vbo);
        }
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        
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
        switch (_sortType) {
            case GlyphSortType::BACK_TO_FRONT :
                std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareBackToFront);
                break;
                
            case GlyphSortType::FRONT_TO_BACK:
                std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFrontToBack);
                break;
                
            case GlyphSortType::TEXTURE:
                std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
                break;
        }
    }
    
    bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b){ return (a->depth < b->depth);  }
    bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b){ return (a->depth > b->depth); }
    bool SpriteBatch::compareTexture(Glyph* a, Glyph* b){ return (a->texture < b->texture); }
    
    
}

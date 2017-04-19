//
//  SpriteBatch.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 17/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef SpriteBatch_hpp
#define SpriteBatch_hpp

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>

#include "Vertex.h"

namespace Bengine {
    
    enum class GlyphSortType{
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT,
        TEXTURE
    };
    
    class Glyph{
    public:
        Glyph(){}
        Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& Color):
        texture(Texture), depth(Depth)
        {
            // (x,y) == bottom left
            
            topLeft.color = Color;
            topLeft.setPosition(destRect.x, destRect.y + destRect.w);
            topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
            
            bottomLeft.color = Color;
            bottomLeft.setPosition(destRect.x, destRect.y);
            bottomLeft.setUV(uvRect.x, uvRect.y);
            
            topRight.color = Color;
            topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
            topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
            
            bottomRight.color = Color;
            bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
            bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
        }
        
        
        GLuint texture;
        float depth;
        
        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;
    };
    
    class RenderBatch
    {
    public:
        RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture):
        offset(Offset), numVertices(NumVertices), texture(Texture){}
        GLuint offset;
        GLuint numVertices;
        GLuint texture;
    };
    
    class SpriteBatch
    {
    public:
        SpriteBatch();
        ~SpriteBatch();
        
        void init();
        
        void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
        void end();
        
        void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color );
        
        void renderBatch();
        
    private:
        void createRenderBatches();
        void createVertexArray();
        void sortGlyphs();
        
        static bool compareFrontToBack(Glyph* a, Glyph* b);
        static bool compareBackToFront(Glyph* a, Glyph* b);
        static bool compareTexture(Glyph* a, Glyph* b);
        
        GLuint _vbo;
        GLuint _vao;
        GlyphSortType _sortType;
        
        std::vector<Glyph*> _glyphPointers; // For sorting
        std::vector<Glyph> _glyphs; // Contains actual glyphs
        std::vector<RenderBatch> _renderBatches;
    };
}

#endif /* SpriteBatch_hpp */

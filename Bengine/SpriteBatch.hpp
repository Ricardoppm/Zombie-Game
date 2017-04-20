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
        Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& Color);
        Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& Color, float angle);
        
        GLuint texture;
        float depth;
        
        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;
        
    private:
        glm::vec2 rotatePoint(glm::vec2 position, float angle);

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
        
        void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle);

        void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& direction );

        
        void renderBatch();
        
    private:
        void createRenderBatches();
        void createVertexArray();
        void sortGlyphs();
        
        static bool compareFrontToBack(Glyph* a, Glyph* b);
        static bool compareBackToFront(Glyph* a, Glyph* b);
        static bool compareTexture(Glyph* a, Glyph* b);
        
        GLuint vbo_ = 0;
        GLuint vao_ = 0;
        GlyphSortType sortType_;
        
        std::vector<Glyph*> glyphPointers_; // For sorting
        std::vector<Glyph> glyphs_; // Contains actual glyphs
        std::vector<RenderBatch> renderBatches_;
    };
}

#endif /* SpriteBatch_hpp */

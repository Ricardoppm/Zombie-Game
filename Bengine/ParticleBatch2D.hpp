//
//  ParticleBatch2D.hpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 20/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef ParticleBatch2D_hpp
#define ParticleBatch2D_hpp

#include <glm/glm.hpp>
#include <functional>

#include "Vertex.h"
#include "SpriteBatch.hpp"
#include "GLTexture.h"

namespace Bengine {
    
    class Particle2D
    {
    public:
        glm::vec2 position = glm::vec2(0.f);
        glm::vec2 velocity = glm::vec2(0.f);
        ColorRGBA8 color;
        float life = 0.f;
        float width = 0.f;
    };
    
    inline void defaultParticleUpdate(Particle2D& particle, float deltaTime)
    {
        particle.position += particle.velocity * deltaTime;
    }
    
    
    class ParticleBatch2D
    {
    public:
        ParticleBatch2D();
        ~ParticleBatch2D();
        
        void init(int maxParticles,
                  float decayRate,
                  GLTexture texture,
                  std::function<void(Particle2D&, float)> updateFunc = defaultParticleUpdate);
        
        void update(float deltaTime);
        
        void draw(SpriteBatch* spriteBatch);
        
        void addParticle(const glm::vec2& position,
                         const glm::vec2& velocity,
                         const ColorRGBA8& color,
                         float width);
        
    private:
        int findFreeParticle();
        
        std::function<void(Particle2D&, float)> updateFunc_;
        
        float decayRate_ = 0.1f;
        Particle2D* particles_ = nullptr;
        int maxParticles_ = 0 ;
        GLTexture texture_;
        int lastFreeParticle_ = 0;
    };
    
   
}
#endif /* ParticleBatch2D_hpp */

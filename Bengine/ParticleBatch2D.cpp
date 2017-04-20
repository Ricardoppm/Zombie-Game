//
//  ParticleBatch2D.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 20/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "ParticleBatch2D.hpp"

namespace Bengine {
 
    // ParticleBatch2D functions
    ParticleBatch2D::ParticleBatch2D(){}
    
    ParticleBatch2D::~ParticleBatch2D()
    {
        delete [] particles_;
    }
    
    void ParticleBatch2D::init(int maxParticles,
                               float decayRate,
                               GLTexture texture,
                               std::function<void(Particle2D&, float)> updateFunc /* = defaultUpdateFunc */)
    {
        maxParticles_ = maxParticles;
        particles_ = new Particle2D[maxParticles_];
        
        decayRate_ = decayRate;
        texture_ = texture;
        updateFunc_ = updateFunc;
    }
    
    void ParticleBatch2D::update(float deltaTime)
    {
        for (int i = 0; i < maxParticles_; i++) {
            // Check if particle is active
            if( particles_[i].life > 0.f){
                updateFunc_(particles_[i], deltaTime);
                particles_[i].life -= decayRate_ * deltaTime;
            }
        }
    }
    
    void ParticleBatch2D::draw(SpriteBatch* spriteBatch)
    {
        glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);
        
        for (int i = 0; i < maxParticles_; i++) {
            // Check if particle is active
            if( particles_[i].life > 0.f){
                auto& p = particles_[i];
                glm::vec4 destRect(p.position.x ,p.position.y, p.width, p.width);
                spriteBatch->draw(destRect, uvRect, texture_.id, 0, p.color);
            }
        }

    }
    
    void ParticleBatch2D::addParticle(const glm::vec2 &position,
                                      const glm::vec2 &velocity,
                                      const Bengine::ColorRGBA8 &color,
                                      float width)
    {
        int particleIndex = findFreeParticle();
        
        auto& p = particles_[particleIndex];
        p.life = 1.f;
        p.position = position;
        p.velocity = velocity;
        p.color = color;
        p.width = width;
    }
    
    
    int ParticleBatch2D::findFreeParticle()
    {
        for(int i = lastFreeParticle_; i < maxParticles_; i++){
            if( particles_[i].life <= 0.f){
                lastFreeParticle_ = i;
                return i;
            }
        }
        
        for(int i = 0; i < lastFreeParticle_; i++){
            if( particles_[i].life <= 0.f){
                lastFreeParticle_ = i;
                return i;
            }
        }
        // No particles are free, override first particle
        return 0;
    }
}

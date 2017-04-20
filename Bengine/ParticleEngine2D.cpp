//
//  ParticleEngine2D.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 20/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "ParticleEngine2D.hpp"



namespace Bengine {
    
    ParticleEngine2D::ParticleEngine2D(){}
    
    ParticleEngine2D::~ParticleEngine2D()
    {
        for( auto&b:batches_){
            delete b;
        }
        
    }
    
    void ParticleEngine2D::addParticleBatch(ParticleBatch2D* particleBatch)
    {
        batches_.push_back(particleBatch);
    }
        
    void ParticleEngine2D::update(float deltaTime)
    {
        for(auto& b: batches_){
            b->update(deltaTime);
        }
    }
    
    void ParticleEngine2D::draw(SpriteBatch* spriteBatch)
    {
        for (auto& batch : batches_) {
            spriteBatch->begin();
            batch->draw(spriteBatch);
            spriteBatch->end();
            spriteBatch->renderBatch();
        }
    }
}

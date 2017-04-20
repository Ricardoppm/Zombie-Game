//
//  ParticleEngine2D.hpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 20/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef ParticleEngine2D_hpp
#define ParticleEngine2D_hpp

#include <vector>

#include "ParticleBatch2D.hpp"
#include "SpriteBatch.hpp"

namespace Bengine {
    class ParticleEngine2D
    {
    public:
        ParticleEngine2D();
        ~ParticleEngine2D();
        
        // After adding a particleBatch, this class becomes resposible for allocation
        void addParticleBatch(ParticleBatch2D* particleBatch);
        
        void update(float deltaTime);
        
        void draw(SpriteBatch* spriteBatch);
        
    private:
        std::vector<ParticleBatch2D*> batches_;
    };
}
#endif /* ParticleEngine2D_hpp */

//
//  Gun.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 19/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Gun.hpp"

#include <ctime>
#include <random>
#include <glm/gtx/rotate_vector.hpp>

Gun::Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletSpeed, float bulletDamage ):
name_(name),
fireRate_(fireRate),
bulletsPerShot_(bulletsPerShot),
spread_(spread),
bulletSpeed_(bulletSpeed),
bulletDamage_(bulletDamage),
frameCounter_(0)
{
}

Gun::~Gun()
{
}

void Gun::update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets)
{
    frameCounter_++;
    if( frameCounter_ >= fireRate_ && isMouseDown){
        fire(position, direction, bullets);
        frameCounter_ = 0;
    }
}

void Gun::fire( const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets)
{
    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randRotate (-spread_, spread_);

    for (int i = 0; i < bulletsPerShot_; i++) {
        bullets.emplace_back(bulletDamage_,
                             position,
                             glm::rotate(direction, randRotate(randomEngine)),
                             bulletSpeed_);
    }
    
    
    
}

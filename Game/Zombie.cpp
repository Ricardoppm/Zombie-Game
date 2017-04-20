//
//  Zombie.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Zombie.hpp"

#include "ResourceManager.hpp"

#include "Human.hpp"


Zombie::Zombie() {}

Zombie::~Zombie() {}

void Zombie::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombie, float deltaTime)
{
    Human* closestHuman = getNearestHuman(humans);
    
    if( closestHuman != nullptr){
        direction_ = glm::normalize(closestHuman->getPosition() - position_);
        position_ += direction_ * speed_ * deltaTime;
    }
    
    collideWithLevel(levelData);    
}

void Zombie::init(float speed, glm::vec2 pos)
{
    // Set up color - white so it doesn't affect the texture
    color_ = Bengine::ColorRGBA8(255,255,255,255);

    health_ = 100.f;
    speed_ = speed;
    position_ = pos;
    
    textureID_ = Bengine::ResourceManager::getTexture("Game/Textures/Zombie.png").id;
}

Human* Zombie::getNearestHuman(std::vector<Human *> &humans)
{
    Human* closestHuman = nullptr;
    float smallestDistance= 100000;
    
    for (int i =0; i < humans.size(); i++) {
        glm::vec2 distVec = humans[i]->getPosition() - position_;
        float distance = glm::length(distVec);
        if( distance < smallestDistance){
            smallestDistance = distance;
            closestHuman = humans[i];
        }
    }
    return  closestHuman;
}

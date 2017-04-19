//
//  Zombie.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Zombie.hpp"

#include "Human.hpp"

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombie)
{
    Human* closestHuman = getNearestHuman(humans);
    
    if( closestHuman != nullptr){
        glm::vec2 direction = glm::normalize(closestHuman->getPosition() - position_);
        position_ += direction * speed_;
    }
    
    collideWithLevel(levelData);    
}

void Zombie::init(float speed, glm::vec2 pos)
{
    // Set up color
    color_.r = 0;
    color_.g = 160;
    color_.b = 0;
    color_.a = 255;
    
    health_ = 100.f;
    
    speed_ = speed;
    position_ = pos;
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

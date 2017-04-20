//
//  Human.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Human.hpp"

#include <random>
#include <ctime>

#include <glm/gtx/rotate_vector.hpp>

Human::Human() {}

Human::~Human() {}

void Human::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombie, float deltaTime)
{
    position_ += direction_ * speed_ * deltaTime;
    
    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randRotate (-0.2f, 0.2f);
    
    if (frames_ == 20){
        direction_ = glm::rotate(direction_, randRotate(randomEngine));
        frames_ = 0;
    }
    else
        frames_++;
    
    
    if(collideWithLevel(levelData))
        direction_ = glm::rotate(direction_, randRotate(randomEngine));
        
}

void Human::init(float speed, glm::vec2 pos)
{
    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randDir (-1.0f, 1.0f);
    
    // Set up human's health
    health_ = 20.f;
    
    // Set up color
    color_ = Bengine::ColorRGBA8(200,0,200,255);
    
    speed_ = speed;
    position_ = pos;
    // Get random direction
    direction_ = glm::vec2( randDir(randomEngine), randDir(randomEngine));
    // Make sure direction isn't 0
    if( direction_.length() == 0)
        direction_ = glm::vec2(1.0f, 0.0f);
    // Normalize direction
    direction_ = glm::normalize(direction_);
}

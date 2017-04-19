//
//  Bullet.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 19/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Bullet.hpp"

#include "ResourceManager.hpp"
#include "Vertex.h"

#include "Human.hpp"
#include "Zombie.hpp"
#include "Level.hpp"

Bullet::Bullet(float damage, glm::vec2 position, glm::vec2 direction, float speed):
damage_(damage), position_(position), direction_(direction), speed_(speed)
{
    
}

Bullet::~Bullet()
{

}

bool Bullet::update(const std::vector<std::string>& levelData, float deltaTime)
{
    position_ += direction_ * speed_ * deltaTime;
    return collideWithWorld(levelData);
}

void Bullet::draw(Bengine::SpriteBatch &spriteBatch)
{
    glm::vec4 destRect(position_.x + BULLET_RADIUS,
                       position_.y + BULLET_RADIUS,
                       BULLET_RADIUS*2,
                       BULLET_RADIUS*2);
    glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);
    Bengine::ColorRGBA8 color(75,75,75,255);
    
    spriteBatch.draw(destRect, uvRect, Bengine::ResourceManager::getTexture("Game/Textures/circle.png").id, 0.f, color);
}

bool Bullet::collideWithAgent(Agent *agent)
{
    glm::vec2 centerPosAgent = agent->getPosition() + glm::vec2( AGENT_RADIUS);
    glm::vec2 centerPosBullet = position_;
    
    glm::vec2 distVec = centerPosAgent - centerPosBullet;
    
    const float MIN_DISTANCE = AGENT_RADIUS  + BULLET_RADIUS;
    
    float distance = glm::length(distVec);
    
    float collisionDepth = MIN_DISTANCE - distance;
    
    if( collisionDepth > 0){
        return true;
    }
    return false;
}

bool Bullet::collideWithWorld(const std::vector<std::string> &levelData)
{
    glm::ivec2 gridPosition;
    gridPosition.x = floor(position_.x / (float)TILE_WIDTH);
    gridPosition.y = floor(position_.y / (float)TILE_WIDTH);
    
    // If we are outside the world just return
    if (gridPosition.x < 0 || gridPosition.x > levelData[0].size() || gridPosition.y < 0 || gridPosition.y > levelData.size())
        return true;
    
    return (levelData[gridPosition.y][gridPosition.x] != '.');
}

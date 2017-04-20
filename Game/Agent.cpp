//
//  Agent.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Agent.hpp"

#include <algorithm>

#include "ResourceManager.hpp"
#include "Level.hpp"

Agent::Agent() {}

Agent::~Agent() {}

void Agent::draw( Bengine::SpriteBatch& spriteBatch )
{
    static int textureID = Bengine::ResourceManager::getTexture("Game/Textures/circle.png").id;
    
    const glm::vec4 uvRect(0.0f, 0.0f, 1.f, 1.f);
    
    glm::vec4 destRect(position_.x,
                       position_.y,
                       AGENT_WIDTH,
                       AGENT_WIDTH);
    
    spriteBatch.draw(destRect, uvRect, textureID, 0, color_);
}

bool Agent::applyDamage(float damage)
{
    health_ -=damage;
    if( health_<=0){
        return true;
    }
    return false;
}

bool Agent::collideWithLevel(const std::vector<std::string> &levelData)
{
    std::vector<glm::vec2> collideTilePosition;
    
    // Check four corners
    // First corner
    checkTilePosition(levelData,
                      collideTilePosition,
                      position_.x,
                      position_.y);
    // Second corner
    checkTilePosition(levelData,
                      collideTilePosition,
                      position_.x  + AGENT_WIDTH,
                      position_.y);
    // Third corner
    checkTilePosition(levelData,
                      collideTilePosition,
                      position_.x,
                      position_.y + AGENT_WIDTH);
    // Fourth corner
    checkTilePosition(levelData,
                      collideTilePosition,
                      position_.x + AGENT_WIDTH,
                      position_.y + AGENT_WIDTH);

    // Do the collision
    for(int i=0; i< collideTilePosition.size(); i++){
        collideWithTile(collideTilePosition[i]);
    }
    return (collideTilePosition.size()!=0);
}

bool Agent::collideWithAgent(Agent* agent)
{
    glm::vec2 centerPosA = position_ + glm::vec2( AGENT_RADIUS);
    glm::vec2 centerPosB = agent->getPosition() + glm::vec2( AGENT_RADIUS);

    glm::vec2 distVec = centerPosA - centerPosB;
    
    const float MIN_DISTANCE = AGENT_RADIUS * 2.f;

    float distance = glm::length(distVec);
    
    float collisionDepth = MIN_DISTANCE - distance;
    
    if( collisionDepth > 0){
        glm::vec2 collisionDepthVec = glm::normalize(distVec)*collisionDepth;
        
        position_ += collisionDepthVec / 2.f;
        agent->position_ -= collisionDepthVec / 2.f;
        return true;
    }
    return false;
}

void Agent::checkTilePosition(const std::vector<std::string> &levelData, std::vector<glm::vec2> &collideTilePosition, float x, float y)
{
    glm:: vec2 cornerPos = glm::vec2( floor(x / (float)TILE_WIDTH),
                                      floor(y / (float)TILE_WIDTH));
    
    // If we are outside the world just return
    if (cornerPos.x < 0 || cornerPos.x > levelData[0].size() || cornerPos.y < 0 || cornerPos.y > levelData.size())
        return;
    
    
    if( levelData[cornerPos.y][cornerPos.x] != '.')
        collideTilePosition.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
}

// AABB collision
void Agent::collideWithTile(glm::vec2 tilePosition)
{
    const float TILE_RADIUS = (float)TILE_WIDTH/2.f;
    const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;
    
    glm::vec2 centerPlayerPos = position_ + glm::vec2(AGENT_RADIUS);
    
    glm::vec2 distVec = centerPlayerPos - tilePosition;
    
    float xDepth = MIN_DISTANCE - std::abs(distVec.x);
    float yDepth = MIN_DISTANCE - std::abs(distVec.y);
    
   

    // if true we are colliding
    if( xDepth > 0 || yDepth > 0)
    {
        if (std::max(xDepth, 0.f) < std::max(yDepth,0.f)) {
            if( distVec.x < 0)
                position_.x -= xDepth;
            else
                position_.x += xDepth;
        }
        else{
            if( distVec.y < 0)
                position_.y -= yDepth;
            else
                position_.y += yDepth;
        }
    }
}

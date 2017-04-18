//
//  Agent.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Agent.hpp"

#include "ResourceManager.hpp"
#include "Level.hpp"

Agent::Agent()
{

}

Agent::~Agent()
{
}

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

void Agent::collideWithLevel(const std::vector<std::string> &levelData)
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
    
}

void Agent::checkTilePosition(const std::vector<std::string> &levelData, std::vector<glm::vec2> &collideTilePosition, float x, float y)
{
    glm:: vec2 cornerPos = glm::vec2( floor(x / (float)TILE_WIDTH),
                                      floor(y / (float)TILE_WIDTH));
    if( levelData[cornerPos.y][cornerPos.x] != '.')
        collideTilePosition.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
}

// AABB collision
void Agent::collideWithTile(glm::vec2 tilePosition)
{
    const float AGENT_RADIUS = (float)AGENT_WIDTH/2.f;
    const float TILE_RADIUS = (float)TILE_WIDTH/2.f;
    const float MIN_DISTANCE = AGENT_RADIUS - TILE_RADIUS;
    
    glm::vec2 distVec = position_ - tilePosition;
    
    float xDepth = MIN_DISTANCE - distVec.x;
    float yDepth = MIN_DISTANCE - distVec.y;
    
    float absXDepth = std::abs(xDepth);
    float absYDepth = std::abs(yDepth);

    
    // if true we are colliding
    if( xDepth > 0 || yDepth > 0)
    {
        if (xDepth < yDepth) {
            position_ += absXDepth;
        }
        else{
            position_ += absYDepth;
        }
    }

}

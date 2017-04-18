//
//  Agent.hpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Agent_hpp
#define Agent_hpp

#include <glm/glm.hpp>

#include "SpriteBatch.hpp"

class Zombie;
class Human;

const int AGENT_WIDTH = 60;


class Agent
{
public:
    Agent();
    virtual ~Agent();

    virtual void update(const std::vector<std::string>& levelData,
                        std::vector<Human*>& humans,
                        std::vector<Zombie*>& zombie) = 0;
    
    void collideWithLevel(const std::vector<std::string>& levelData);
    
    void draw( Bengine::SpriteBatch& spriteBatch);
    
    // Getters
    glm::vec2 getPosition() const { return position_; }
    
protected:
    void checkTilePosition(const std::vector<std::string> &levelData, std::vector<glm::vec2>& collideTilePosition, float x, float y);
    
    void collideWithTile(glm::vec2 tilePosition);
    
    glm::vec2 position_;
    float speed_;
    Bengine::Color color_;
    
};
#endif /* Agent_hpp */

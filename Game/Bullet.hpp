//
//  Bullet.hpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 19/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <glm/glm.hpp>
#include <vector>

#include "SpriteBatch.hpp"

class Human;
class Zombie;
class Agent;

const int BULLET_RADIUS = 5;

class Bullet
{
public:
    Bullet(float damage, glm::vec2 position, glm::vec2 direction, float speed);
    ~Bullet();

    // When update returns true we delete the bullet
    bool update(const std::vector<std::string>& levelData, float deltaTime);
    
    void draw( Bengine::SpriteBatch& spriteBatch );
    
    bool collideWithAgent(Agent* agent);
    
    // Getters
    float getDamage() const { return damage_; }
    glm::vec2 getPosition() const { return position_;}
    
private:
    bool collideWithWorld(const std::vector<std::string>& levelData);
    
    float damage_;
    glm::vec2 position_;
    glm::vec2 direction_;
    float speed_;
};
#endif /* Bullet_hpp */

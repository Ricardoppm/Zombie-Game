//
//  Player.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Player.hpp"

#include <SDL2/SDL.h>

Player::Player()
{
}

Player::~Player()
{

}

void Player::init(float speed, glm::vec2 position, Bengine::InputManager* inputManager)
{
    speed_ = speed;
    position_ = position;
    color_.r = 0;
    color_.g = 0;
    color_.b = 190;
    color_.a = 255;
    inputManager_ = inputManager;
}

void Player::update( const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombie )
{
    if( inputManager_->isKeyPressed(SDLK_w)){
        position_.y += speed_;
    }
    else if( inputManager_->isKeyPressed(SDLK_s)){
        position_.y -= speed_;
    }
    
    if( inputManager_->isKeyPressed(SDLK_d)){
        position_.x += speed_; 
    }
    else if( inputManager_->isKeyPressed(SDLK_a)){
        position_.x -= speed_;
    }
    
    collideWithLevel(levelData);    
}

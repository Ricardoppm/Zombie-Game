//
//  Player.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Player.hpp"

#include <SDL2/SDL.h>

#include "Gun.hpp"

Player::Player():
currentGun_(-1)
{
}

Player::~Player()
{

}

void Player::init(float speed, glm::vec2 position, Bengine::InputManager* inputManager, Bengine::Camera2D* camera,std::vector<Bullet>* bullets)
{
    speed_ = speed;
    position_ = position;
    color_ = Bengine::ColorRGBA8(0,0,190,255);
    inputManager_ = inputManager;
    camera_ = camera;
    bullets_ = bullets;
    health_ = 100;
}

void Player::addGun(Gun *gun)
{
    guns_.push_back(gun);
    // Auto-equip if empty
    if (currentGun_==-1) {
        currentGun_=0;
    }
}

void Player::update( const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombie, float deltaTime)
{
    if( inputManager_->isKeyDown(SDLK_w)){
        position_.y += speed_ * deltaTime;
    }
    else if( inputManager_->isKeyDown(SDLK_s)){
        position_.y -= speed_ * deltaTime;
    }
    
    if( inputManager_->isKeyDown(SDLK_d)){
        position_.x += speed_ * deltaTime;
    }
    else if( inputManager_->isKeyDown(SDLK_a)){
        position_.x -= speed_ * deltaTime;
    }
    
    if( inputManager_->isKeyDown(SDLK_1) && guns_.size() >=1){
        currentGun_ = 0;
    }else if( inputManager_->isKeyDown(SDLK_2) && guns_.size() >=2){
        currentGun_ = 1;
    }else if( inputManager_->isKeyDown(SDLK_3) && guns_.size() >=3){
        currentGun_ = 2;
    }
    
    if( currentGun_!=-1){
        glm::vec2 mouseCoords = camera_->convertScreenToWorld(inputManager_->getMouseCoords());
        
        glm::vec2 centerPosition = position_  + glm::vec2(AGENT_RADIUS);
        
        glm::vec2 direction = glm::normalize(mouseCoords - centerPosition);

        
        guns_[currentGun_]->update(inputManager_->isKeyDown(SDL_BUTTON_LEFT),
                                   centerPosition,
                                   direction,
                                   *bullets_,
                                   deltaTime);
    }

    
    collideWithLevel(levelData);    
}

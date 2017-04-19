//
//  Player.hpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "InputManager.hpp"
#include "Camera2D.hpp"

#include <vector>

#include "Human.hpp"
#include "Bullet.hpp"

class Gun;

class Player : public Human
{
public:
    Player();
    ~Player();
    
    void init(float speed, glm::vec2 position, Bengine::InputManager* inputManager, Bengine::Camera2D* camera, std::vector<Bullet>* bullets);
    
    void update(const std::vector<std::string>& levelData,
                std::vector<Human*>& humans,
                std::vector<Zombie*>& zombie,
                float deltaTime) override;
    
    void addGun(Gun* gun);
    
private:
    Bengine::InputManager* inputManager_;
    Bengine::Camera2D* camera_;
    
    std::vector<Bullet>* bullets_;
    std::vector<Gun*> guns_;
    int currentGun_;
};

#endif /* Player_hpp */

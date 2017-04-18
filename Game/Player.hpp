//
//  Player.hpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Human.hpp"

#include "InputManager.hpp"

class Player : public Human
{
public:
    Player();
    ~Player();
    
    void init(float speed, glm::vec2 position, Bengine::InputManager* inputManager);
    
    void update(const std::vector<std::string>& levelData,
                std::vector<Human*>& humans,
                std::vector<Zombie*>& zombie);
    
private:
    Bengine::InputManager* inputManager_;
    
};

#endif /* Player_hpp */

//
//  Zombie.hpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Zombie_hpp
#define Zombie_hpp

#include "Agent.hpp"


class Zombie : public Agent
{
public:
    Zombie();
    ~Zombie();
    
    virtual void update(const std::vector<std::string>& levelData,
                        std::vector<Human*>& humans,
                        std::vector<Zombie*>& zombie,
                        float deltaTime) override;
    
    void init(float speed, glm::vec2 pos);
    
private:
    Human* getNearestHuman(std::vector<Human*>& humans);
};
#endif /* Zombie_hpp */

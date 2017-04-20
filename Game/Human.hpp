//
//  Human.hpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Human_hpp
#define Human_hpp

#include "Agent.hpp"

class Human : public Agent
{
public:
    Human();
    virtual ~Human();
    
    virtual void update(const std::vector<std::string>& levelData,
                        std::vector<Human*>& humans,
                        std::vector<Zombie*>& zombie,
                        float deltaTime) override;
    
    void init(float speed, glm::vec2 pos);
    
private:
    glm::vec2 direction_;
    int frames_ = 0;
};
#endif /* Human_hpp */

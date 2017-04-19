//
//  Gun.hpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 19/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Gun_hpp
#define Gun_hpp

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Bullet.hpp"

class Gun
{
public:
    Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletSpeed, float bulletDamage);
    ~Gun();
    
    void update(bool isMouseDown , const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets);
    
    
private:
    
    void fire( const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets);

    std::string name_;
    
    int fireRate_; // Fire rate in terms of frames
    
    float spread_; // accuracy
    
    int bulletsPerShot_;
    
    float bulletSpeed_;
    
    float bulletDamage_;
    
    int frameCounter_;
    
};
#endif /* Gun_hpp */

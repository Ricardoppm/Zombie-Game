//
//  Level.hpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Level_hpp
#define Level_hpp

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "SpriteBatch.hpp"

const int TILE_WIDTH = 64;

class Level
{
public:
    // Load the level
    Level(const std::string& filePath);
    ~Level();
    
    void draw();
    
    // Getters
    glm::vec2 getStartPlayerPos() const { return startPlayerPosition_;}
    const std::vector<glm::vec2>& getStartZombiePos() const { return zombieStartPositions_; }
    const std::vector<std::string>& getLevelData() const { return levelData_; }
    
private:
    std::vector<std::string> levelData_;
    int numHumans_;
    
    Bengine::SpriteBatch spriteBatch_;

    glm::vec2 startPlayerPosition_;
    std::vector< glm::vec2> zombieStartPositions_;
    
};

#endif /* Level_hpp */

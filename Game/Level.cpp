//
//  Level.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 18/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Level.hpp"

#include <fstream>

#include "ResourceManager.hpp"
#include "errors.hpp"

Level::Level(const std::string& filePath)
{
    std::ifstream file;
    file.open(filePath);
    if( file.fail()){
        Bengine::fatalError("Failed to open level: " + filePath);
    }
    
    std::string temp;
    // get number of humans
    file >> temp >> numHumans_;
    std::getline(file, temp);
    
    while(std::getline(file, temp)){
        levelData_.push_back(temp);
    }
    
    spriteBatch_.init();
    spriteBatch_.begin();
    
    glm::vec4 uvRect(0,0,1,1);
    Bengine::Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    
    for(int y = 0; y< levelData_.size(); y++){
        for (int x = 0; x < levelData_[y].size(); x++) {
            
            // get destination vec
            glm::vec4 destRect(x*TILE_WIDTH, y*TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            
            // Process tile
            switch (levelData_[y][x]) {
                case 'G':
                    spriteBatch_.draw(destRect,
                                      uvRect,
                                      Bengine::ResourceManager::getTexture("Game/Textures/glass.png").id,
                                      0.f,
                                      color);
                    break;
                
                case 'B':
                case 'R':
                    spriteBatch_.draw(destRect,
                                      uvRect,
                                      Bengine::ResourceManager::getTexture("Game/Textures/red_bricks.png").id,
                                      0.f,
                                      color);
                    break;
                    
                case 'L':
                    spriteBatch_.draw(destRect,
                                      uvRect,
                                      Bengine::ResourceManager::getTexture("Game/Textures/light_bricks.png").id,
                                      0.f,
                                      color);
                    break;
                    
                case 'Z':
                    zombieStartPositions_.emplace_back(x*TILE_WIDTH, y*TILE_WIDTH);
                    levelData_[y][x]='.'; // so we don't collide with a Z
                    break;
                    
                case '@':
                    startPlayerPosition_.x = x * TILE_WIDTH;
                    startPlayerPosition_.y = y * TILE_WIDTH;
                    levelData_[y][x]='.'; // So we don't collide with a @
                    break;
                    
                default:
                    break;
            }
        }
    }
    spriteBatch_.end();
}

void Level::draw()
{
    spriteBatch_.renderBatch();
}

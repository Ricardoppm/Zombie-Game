//
//  MainGame.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 08/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef MainGame_hpp
#define MainGame_hpp

#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#include <iostream>
#include <vector>

#include "Sprite.hpp"
#include "GLSLProgram.hpp"
#include "Window.hpp"
#include "Camera2D.hpp"
#include "SpriteBatch.hpp"
#include "InputManager.hpp"
#include "Timing.hpp"

#include "Level.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

class Zombie;

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
    MainGame();
    ~MainGame();
    
    // Runs the game
    void run();
    
private:
    // Initializes the core systems
    void initSystems();
    
    // Initializes shaders
    void initShaders();
    
    // Processes input
    void processInput();
    
    // Main game Loop
    void gameLoop();
    
    // Draws game
    void drawGame();
    
    // Initializes the level and sets up actors
    void initLevel();
    
    // Updates all agents
    void updateAgents(float deltaTime);
    
    // Updates Bullets
    void updateBullets(float deltaTime);
    
    // Verifies win conditions
    void checkVictory();
    
    
    int _screenWidth;
    int _screenHeight;
    
    GameState _gameState;
        
    Bengine::Window _window;
    Bengine::GLSLProgram _colorProgram;
    Bengine::Camera2D _camera;
    Bengine::InputManager _inputManager;
    Bengine::FpsLimiter _fpsLimiter;
    Bengine::SpriteBatch agentSpriteBatch_;
    
    std::vector<Level*> levels_;
    int currentLevel_;
    
    std::vector<Human*> humans_;
    std::vector<Zombie*> zombies_;
    std::vector<Bullet> bullets_;

    Player* player_;
    
    // FPS 
    float _fps;
    float _maxFPS;
    
    // Game Stats
    int numHumansKilled_;
    int numZombiesKilled_;

};

#endif /* MainGame_hpp */

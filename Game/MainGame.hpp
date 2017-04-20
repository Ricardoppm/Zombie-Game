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
#include "SpriteFont.hpp"
#include "AudioEngine.hpp"
#include "ParticleEngine2D.hpp"
#include "ParticleBatch2D.hpp"

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
    
    // Draws the HUD
    void drawHud();
    
    // Initializes the level and sets up actors
    void initLevel();
    
    // Updates all agents
    void updateAgents(float deltaTime);
    
    // Updates Bullets
    void updateBullets(float deltaTime);
    
    // Verifies win conditions
    void checkVictory();
    
    // Add blood particles
    void addBlood(const glm::vec2& position, int numParticles);
    
    
    int screenWidth_ = 800;
    int screenHeight_ = 600;
    
    GameState gameState_ = GameState::PLAY;
        
    Bengine::Window window_;
    Bengine::GLSLProgram colorProgram_;
    Bengine::InputManager inputManager_;
    Bengine::FpsLimiter fpsLimiter_;
    Bengine::SpriteFont* spriteFont_;
    Bengine::AudioEngine audioEngine_;
    
    Bengine::SpriteBatch agentSpriteBatch_;
    Bengine::SpriteBatch hudSpriteBatch_;

    Bengine::Camera2D camera_; // Main Camera
    Bengine::Camera2D hudCamera_; // HUD Camera

    Bengine::ParticleEngine2D particleEngine_;
    Bengine::ParticleBatch2D* bloodParticleBatch_;
    
    std::vector<Level*> levels_;
    int currentLevel_ = 0;
    
    std::vector<Human*> humans_;
    std::vector<Zombie*> zombies_;
    std::vector<Bullet> bullets_;

    Player* player_ = nullptr;
    
    // FPS 
    float fps_;
    float maxFPS_ = 60.f;
    
    // Game Stats
    int numHumansKilled_;
    int numZombiesKilled_;
};

#endif /* MainGame_hpp */

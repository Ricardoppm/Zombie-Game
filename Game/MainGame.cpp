//
//  MainGame.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 08/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "MainGame.hpp"

#include <ctime>
#include <random>

#include "errors.hpp"
#include "Bengine.hpp"
#include "ResourceManager.hpp"

#include "Zombie.hpp"
#include "Gun.hpp"

const float HUMAN_SPEED = 1.f;
const float ZOMBIE_SPEED = 1.3f;
const float PLAYER_SPEED = 5.f;

MainGame::MainGame() :
    _screenWidth(800),
    _screenHeight(600),
    _gameState(GameState::PLAY),
    _maxFPS(60.f),
    currentLevel_(0),
    player_(nullptr)
{

}

MainGame::~MainGame()
{
    
}

void MainGame::run()
{
    initSystems();
    
    initLevel();
    
    gameLoop();
}

void MainGame::initSystems()
{
    Bengine::init();
    
    _window.create("Zombie Game", _screenWidth, _screenHeight, 0);
    glClearColor(0.7f, 0.7f, 0.7f, 1.f);
            
    initShaders();
    
    agentSpriteBatch_.init();

    _fpsLimiter.init(_maxFPS);
    
    _camera.init(_screenWidth, _screenHeight);

}

void MainGame::initLevel()
{
    // level 1
    levels_.push_back(new Level("Game/Levels/level1.txt"));
    
    // Init player
    player_ = new Player();
    player_->init(PLAYER_SPEED, levels_[0]->getStartPlayerPos(), &_inputManager, &_camera, &bullets_);
    humans_.push_back(player_);
    
    // Give gun to player
    const float BULLET_SPEED = 20.f;
    player_->addGun(new Gun("Glock", 20, 1, 0.1f, 30, BULLET_SPEED));
    player_->addGun(new Gun("Shotgun", 40, 10, 1.f, 4, BULLET_SPEED));
    player_->addGun(new Gun("mp5", 5, 1, 0.2f, 20, BULLET_SPEED));

    // Set up random generator
    std::mt19937 randomEngine;
    randomEngine.seed(time(nullptr));
    std::uniform_int_distribution<int> randX (2, levels_[currentLevel_]->getWidth() - 2);
    std::uniform_int_distribution<int> randY (2, levels_[currentLevel_]->getHeight() - 2);
    
    // Add all random humans
    for (int i = 0; i < levels_[currentLevel_]->getNumHumans(); i++) {
        humans_.push_back(new Human());
        glm::vec2 position( randX(randomEngine) * TILE_WIDTH , randY(randomEngine) * TILE_WIDTH);
        humans_.back()->init(HUMAN_SPEED, position);
    }
    
    // Add all zombies
    auto zombiePositions = levels_[currentLevel_]->getStartZombiePos();
    for (int i = 0; i < zombiePositions.size(); i++) {
        zombies_.push_back(new Zombie());
        zombies_.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
    }
    
    numHumansKilled_ = 0;
    numZombiesKilled_ = 0;
}

void MainGame::initShaders()
{
    _colorProgram.compileShaders("Game/Shaders/textureShading.vert", "Game/Shaders/textureShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

void MainGame::updateAgents(float deltaTime)
{
    // Update all humans
    for (int i = 0; i < humans_.size(); i++) {
        humans_[i]->update(levels_[currentLevel_]->getLevelData(),
                           humans_,
                           zombies_,
                           deltaTime);
    }
    
    // Update all zombies
    for (int i = 0; i < zombies_.size(); i++) {
        zombies_[i]->update(levels_[currentLevel_]->getLevelData(),
                           humans_,
                           zombies_,
                            deltaTime);
    }
    
    // Update Collisions
    
    // Zombie  collisions
    for (int i = 0; i < zombies_.size(); i++){
        // Other zombies
        for (int j = i+1; j < zombies_.size(); j++)
            zombies_[i]->collideWithAgent( zombies_[j]);
        // Collide with humans
        for (int k = 1; k < humans_.size(); k++){
            if(zombies_[i]->collideWithAgent( humans_[k])){
                // add zombie
                zombies_.push_back( new Zombie());
                zombies_.back()->init(ZOMBIE_SPEED, humans_[k]->getPosition());
                // remove zombie
                delete humans_[k];
                humans_[k] = humans_.back();
                humans_.pop_back();
            }
        }
        
        // Collide with player
        if( zombies_[i]->collideWithAgent(player_)){
            Bengine::fatalError("You Lose!");
        }
    }
    
    // Human - Human collisions
    for (int i = 0; i < humans_.size(); i++)
        for (int j = i+1; j < humans_.size(); j++)
            humans_[i]->collideWithAgent( humans_[j]);
}

void MainGame::updateBullets(float deltaTime)
{
    // Update and collide with world
    for (int i = 0; i < bullets_.size();) {
        // if update retuns true, bullet collided with wall -> delete it
        if(bullets_[i].update(levels_[currentLevel_]->getLevelData(), deltaTime)){
            bullets_[i] = bullets_.back();
            bullets_.pop_back();
        }
        else{
            i++;
        }
    }
    
    bool wasBulletRemoved = false;
    
    // Collide with agents
    for (int i = 0; i < bullets_.size();i++) {
        // Loop through zombies
        for (int j = 0; j < zombies_.size();) {
            if( bullets_[i].collideWithAgent(zombies_[j])){
                // Damage zombie and kill it if health is depleted
                if(zombies_[j]->applyDamage( bullets_[i].getDamage())){
                    delete zombies_[j];
                    zombies_[j] = zombies_.back();
                    zombies_.pop_back();
                    numZombiesKilled_++;
                }
                else{
                    j++;
                }
                
                // Remove bullet
                bullets_[i] = bullets_.back();
                bullets_.pop_back();
                wasBulletRemoved = true;
                
                // Since bullet was removed, no need for further checking
                break;
            }
            else{
                j++;
            }
        }
        if( wasBulletRemoved)
            continue;
        // Loop through humans
        for (int j = 1; j < humans_.size();) {
            if( bullets_[i].collideWithAgent(humans_[j])){
                // Damage human and kill it if health is depleted
                if(humans_[j]->applyDamage( bullets_[i].getDamage())){
                    delete humans_[j];
                    humans_[j] = humans_.back();
                    humans_.pop_back();
                    numHumansKilled_++;
                }
                else{
                    j++;
                }
                
                // Remove bullet
                bullets_[i] = bullets_.back();
                bullets_.pop_back();
                
                // Since bullet was removed, no need for further checking
                break;
            }
            else{
                j++;
            }
        }
    }

}

void MainGame::checkVictory()
{
    if( zombies_.empty()){
        std::cout << "*** You win ***\n";
        std::cout << "You killed " << numHumansKilled_ << " humans and " << numZombiesKilled_ << " zombies\n";
        std::cout << "There are " << humans_.size()-1 << "/" << levels_[currentLevel_]->getNumHumans() << " civilians remaining!\n";
        
        Bengine::fatalError("");
    }
}

void MainGame::processInput()
{
    const float CAMERA_SPEED = 8.f;
    const float CAMERA_SCALESPEED = 0.2f;

    SDL_Event e;
    
    while(SDL_PollEvent(&e)){
        switch (e.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
                
            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoords(e.motion.x, e.motion.y);
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                _inputManager.pressKey(e.button.button);
                break;
                
            case SDL_MOUSEBUTTONUP:
                _inputManager.releaseKey(e.button.button);
                break;
                
            case SDL_KEYDOWN:
                _inputManager.pressKey(e.key.keysym.sym);
                break;
                
            case SDL_KEYUP:
                _inputManager.releaseKey(e.key.keysym.sym);
                break;
        }
    }
    
    if( _inputManager.isKeyDown(SDLK_w)){
        _camera.setPosition( _camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED) );
    }
    if( _inputManager.isKeyDown(SDLK_s)){
        _camera.setPosition( _camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED) );
    }
    if( _inputManager.isKeyDown(SDLK_a)){
        _camera.setPosition( _camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0) );
    }
    if( _inputManager.isKeyDown(SDLK_d)){
        _camera.setPosition( _camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0) );
    }
    if( _inputManager.isKeyDown(SDLK_q)){
        _camera.setScale( _camera.getScale() + CAMERA_SCALESPEED );
    }
    if( _inputManager.isKeyDown(SDLK_e)){
        _camera.setScale( _camera.getScale() - CAMERA_SCALESPEED );
    }
    
    if( _inputManager.isKeyDown(SDL_BUTTON_LEFT)){
        glm::vec2 mouseCoords = _inputManager.getMouseCoords();
        mouseCoords = _camera.convertScreenToWorld(mouseCoords);
        std::cout << mouseCoords.x << " , " << mouseCoords.y << std::endl;
        
        glm::vec2 playerPosition(0.f);
        
        glm::vec2 direction = mouseCoords - playerPosition;
        direction = glm::normalize(direction);
        
        
    }
    
}

void MainGame::gameLoop()
{
    const int MAX_PHYSICS_STEPS = 5;
    
    const int MS_PER_SECOND = 1000;
    const float DESIRED_FPS = 60;
    const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
    const float MAX_DELTA_TIME = 1.f;
    
    float previousTicks = SDL_GetTicks();
    
    while (_gameState!= GameState::EXIT) {
        _fpsLimiter.begin();
        
        float newTicks = SDL_GetTicks();
        float frameTime = newTicks - previousTicks;
        previousTicks = newTicks;
        float totalDeltaTime = frameTime / DESIRED_FRAMETIME;
        checkVictory();
        
        _inputManager.update();
        
        processInput();
        
        _camera.setPosition(player_->getPosition());
        _camera.update();
        
        int i = 0;
        while( totalDeltaTime > 0.f && i < MAX_PHYSICS_STEPS){
            float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
            
            updateAgents(deltaTime);
            updateBullets(deltaTime);
            
            totalDeltaTime -= deltaTime;
            i++;
        }
        
        drawGame();

        _fps = _fpsLimiter.end();
        
        static int frameCounter = 0;
        frameCounter++;
        if( frameCounter == 10000){
            std::cout << _fps << std::endl;
            frameCounter = 0;
        }
    }
}

void MainGame::drawGame()
{
    // set base depth to 1.0
    glClearDepth(1.0);
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // clear screen
    
    // Bind shader that is to be used
    _colorProgram.use();
    
    // Make sure the shader uses texture 0
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);
    

    // Set uniform variable camera
    GLint cameraLocation = _colorProgram.getUniformLocation("transformationMatrix");
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
    
    // Draw level
    levels_[currentLevel_]->draw();
    
    agentSpriteBatch_.begin();
    
    // Draw Humans
    for (int i = 0; i < humans_.size(); i++) {
        humans_[i]->draw(agentSpriteBatch_);
    }
    
    // Draw Humans
    for (int i = 0; i < zombies_.size(); i++) {
        zombies_[i]->draw(agentSpriteBatch_);
    }
    
    // Draw Bullets
    for (int i = 0; i < bullets_.size(); i++) {
        bullets_[i].draw(agentSpriteBatch_);
    }
    
    agentSpriteBatch_.end();
    agentSpriteBatch_.renderBatch();
    
    _colorProgram.unuse();
    
    _window.swapBuffer();
}




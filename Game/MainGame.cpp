//
//  MainGame.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 08/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "MainGame.hpp"

#include "errors.hpp"
#include "Bengine.hpp"
#include "ResourceManager.hpp"

#include "Zombie.hpp"

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
    player_->init(4, levels_[0]->getStartPlayerPos(), &_inputManager);
    
    humans_.push_back(player_);
}

void MainGame::initShaders()
{
    _colorProgram.compileShaders("Game/Shaders/textureShading.vert", "Game/Shaders/textureShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

void MainGame::updateAgents()
{
    // Update all humans
    for (int i = 0; i < humans_.size(); i++) {
        humans_[i]->update(levels_[currentLevel_]->getLevelData(),
                           humans_,
                           zombies_);
    }
    // Update all zombies
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
    
    if( _inputManager.isKeyPressed(SDLK_w)){
        _camera.setPosition( _camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED) );
    }
    if( _inputManager.isKeyPressed(SDLK_s)){
        _camera.setPosition( _camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED) );
    }
    if( _inputManager.isKeyPressed(SDLK_a)){
        _camera.setPosition( _camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0) );
    }
    if( _inputManager.isKeyPressed(SDLK_d)){
        _camera.setPosition( _camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0) );
    }
    if( _inputManager.isKeyPressed(SDLK_q)){
        _camera.setScale( _camera.getScale() + CAMERA_SCALESPEED );
    }
    if( _inputManager.isKeyPressed(SDLK_e)){
        _camera.setScale( _camera.getScale() - CAMERA_SCALESPEED );
    }
    
    if( _inputManager.isKeyPressed(SDL_BUTTON_LEFT)){
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
    while (_gameState!= GameState::EXIT) {
        
        _fpsLimiter.begin();
        
        processInput();
        
        _camera.setPosition(player_->getPosition());
        _camera.update();
        
        updateAgents();
        
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
    agentSpriteBatch_.end();
    agentSpriteBatch_.renderBatch();
    
    _colorProgram.unuse();
    
    _window.swapBuffer();
}




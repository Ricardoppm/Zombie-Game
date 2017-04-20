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

MainGame::MainGame() {}

MainGame::~MainGame() {}

void MainGame::run()
{
    initSystems();
    
    initLevel();
    
    gameLoop();
}

void MainGame::initSystems()
{
    Bengine::init();
    
    window_.create("Zombie Game", screenWidth_, screenHeight_, 0);
    glClearColor(0.7f, 0.7f, 0.7f, 1.f);
            
    initShaders();
    
    agentSpriteBatch_.init();
    hudSpriteBatch_.init();
    
    // initialize spriteFont
    spriteFont_ = new Bengine::SpriteFont("Game/Fonts/raleway/Raleway-Medium.ttf", 64);

    fpsLimiter_.init(maxFPS_);
    
    camera_.init(screenWidth_, screenHeight_);
    hudCamera_.init(screenWidth_, screenHeight_);
    hudCamera_.setPosition(glm::vec2(screenWidth_/2, screenHeight_/2));
}

void MainGame::initLevel()
{
    // level 1
    levels_.push_back(new Level("Game/Levels/level2.txt"));
    
    // Init player
    player_ = new Player();
    player_->init(PLAYER_SPEED, levels_[0]->getStartPlayerPos(), &inputManager_, &camera_, &bullets_);
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
    colorProgram_.compileShaders("Game/Shaders/textureShading.vert", "Game/Shaders/textureShading.frag");
    colorProgram_.addAttribute("vertexPosition");
    colorProgram_.addAttribute("vertexColor");
    colorProgram_.addAttribute("vertexUV");
    colorProgram_.linkShaders();
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

    SDL_Event e;
    
    while(SDL_PollEvent(&e)){
        switch (e.type) {
            case SDL_QUIT:
                gameState_ = GameState::EXIT;
                break;
                
            case SDL_MOUSEMOTION:
                inputManager_.setMouseCoords(e.motion.x, e.motion.y);
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                inputManager_.pressKey(e.button.button);
                break;
                
            case SDL_MOUSEBUTTONUP:
                inputManager_.releaseKey(e.button.button);
                break;
                
            case SDL_KEYDOWN:
                inputManager_.pressKey(e.key.keysym.sym);
                break;
                
            case SDL_KEYUP:
                inputManager_.releaseKey(e.key.keysym.sym);
                break;
        }
    }
    
    if( inputManager_.isKeyDown(SDLK_w)){
        camera_.setPosition( camera_.getPosition() + glm::vec2(0.0, CAMERA_SPEED) );
    }
    if( inputManager_.isKeyDown(SDLK_s)){
        camera_.setPosition( camera_.getPosition() + glm::vec2(0.0, -CAMERA_SPEED) );
    }
    if( inputManager_.isKeyDown(SDLK_a)){
        camera_.setPosition( camera_.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0) );
    }
    if( inputManager_.isKeyDown(SDLK_d)){
        camera_.setPosition( camera_.getPosition() + glm::vec2(CAMERA_SPEED, 0.0) );
    }

    
    if( inputManager_.isKeyDown(SDL_BUTTON_LEFT)){
        glm::vec2 mouseCoords = inputManager_.getMouseCoords();
        mouseCoords = camera_.convertScreenToWorld(mouseCoords);
        std::cout << mouseCoords.x << " , " << mouseCoords.y << std::endl;
        
        glm::vec2 playerPosition(0.f);
        
        glm::vec2 direction = mouseCoords - playerPosition;
        direction = glm::normalize(direction);
        
        
    }
    
}

void MainGame::gameLoop()
{
    // Helpful Constants
    const int MAX_PHYSICS_STEPS = 5;
    const int MS_PER_SECOND = 1000;
    const float DESIRED_FPS = 60;
    const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
    const float MAX_DELTA_TIME = 1.f;
    
    // Used to cap fps
    float previousTicks = SDL_GetTicks();
    
    // Zoomout the camera by 4x
    const float CAMERA_SCALE = 1.f / 4.f;
    camera_.setScale(CAMERA_SCALE);

    
    while (gameState_ != GameState::EXIT) {
        fpsLimiter_.begin();
        
        float newTicks = SDL_GetTicks();
        float frameTime = newTicks - previousTicks;
        previousTicks = newTicks;
        float totalDeltaTime = frameTime / DESIRED_FRAMETIME;
        checkVictory();
        
        inputManager_.update();
        
        processInput();
        
        camera_.setPosition(player_->getPosition());
        camera_.update();
        
        hudCamera_.update();
        
        int i = 0;
        while( totalDeltaTime > 0.f && i < MAX_PHYSICS_STEPS){
            float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
            
            updateAgents(deltaTime);
            updateBullets(deltaTime);
            
            totalDeltaTime -= deltaTime;
            i++;
        }
        
        drawGame();

        fps_ = fpsLimiter_.end();
        
        static int frameCounter = 0;
        frameCounter++;
        if( frameCounter == 300){
            std::cout << fps_ << std::endl;
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
    colorProgram_.use();
    
    // Make sure the shader uses texture 0
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = colorProgram_.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);
    

    // Set uniform variable camera
    GLint cameraLocation = colorProgram_.getUniformLocation("transformationMatrix");
    glm::mat4 cameraMatrix = camera_.getCameraMatrix();
    glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
    
    // Draw level
    levels_[currentLevel_]->draw();
    
    agentSpriteBatch_.begin();
    
    const glm::vec2 agentDims( AGENT_WIDTH);
    
    // Draw Humans
    for (int i = 0; i < humans_.size(); i++) {
        // Check is human is within camera view, if true draw
        if( camera_.isBoxInView(humans_[i]->getPosition(), agentDims)){
            humans_[i]->draw(agentSpriteBatch_);
        }
    }
    
    // Draw zombie
    for (int i = 0; i < zombies_.size(); i++) {
        // Check is zombie is within camera view, if true draw
        if( camera_.isBoxInView(zombies_[i]->getPosition(), agentDims)){
            zombies_[i]->draw(agentSpriteBatch_);
        }
    }
    
    // Draw Bullets
    for (int i = 0; i < bullets_.size(); i++) {
        bullets_[i].draw(agentSpriteBatch_);
    }
    
    
    
    agentSpriteBatch_.end();
    agentSpriteBatch_.renderBatch();
    
    // Render heads up display
    drawHud();
    
    colorProgram_.unuse();
    
    window_.swapBuffer();
}

void MainGame::drawHud()
{
    std::string humanText("Humans Remaining: ");
    humanText.append(std::to_string(humans_.size()));
    
    std::string zombieText("Zombies Remaining: ");
    zombieText.append(std::to_string(zombies_.size()));


    // Set uniform variable camera
    GLint cameraLocation = colorProgram_.getUniformLocation("transformationMatrix");
    glm::mat4 cameraMatrix = hudCamera_.getCameraMatrix();
    glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
    
    hudSpriteBatch_.begin();
    
    spriteFont_->draw(hudSpriteBatch_,
                      humanText.c_str(),
                      glm::vec2(10,10),
                      glm::vec2(0.5f),
                      0.0f,
                      Bengine::ColorRGBA8(255,255,255,255));
    
    spriteFont_->draw(hudSpriteBatch_,
                      zombieText.c_str(),
                      glm::vec2(10,50),
                      glm::vec2(0.5f),
                      0.0f,
                      Bengine::ColorRGBA8(255,255,255,255));
    
    hudSpriteBatch_.end();
    
    hudSpriteBatch_.renderBatch();
}




//
//  Timing.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 17/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Timing.hpp"

#include <SDL2/SDL.h>

namespace Bengine {
    
    FpsLimiter::FpsLimiter(): _maxFPS(60.f){}
    
    void FpsLimiter::init(float maxFPS)
    {
        setTargetFPS(maxFPS);
    }
    
    void FpsLimiter::setTargetFPS(float maxFPS){ _maxFPS = maxFPS; }
    
    void FpsLimiter::begin()
    {
        _startTicks = SDL_GetTicks();
    }
    
    float FpsLimiter::end()
    {
        calculateFPS();
        
        float frameTicks = SDL_GetTicks() - _startTicks;
        // Limit FPS to maxFPS
        if( 1000.0f/_maxFPS > frameTicks){
            SDL_Delay(1000.0f/_maxFPS - frameTicks);
        }
        
        return _fps;
    }
    
    void FpsLimiter::calculateFPS()
    {
        static const int NUM_SAMPLES = 10;
        static float frameTimes[NUM_SAMPLES];
        static int currentFrame = 0;
        static float previousTicks = SDL_GetTicks();
        
        float currentTicks;
        currentTicks = SDL_GetTicks();
        
        _frameTime = currentTicks - previousTicks;
        frameTimes[ currentFrame % NUM_SAMPLES] = _frameTime;
        
        previousTicks = currentTicks;
        
        int count;
        currentFrame++;
        
        if( currentFrame < NUM_SAMPLES){
            count = currentFrame;
        }
        else{
            count = NUM_SAMPLES;
        }
        
        float frameTimeAverage = 0.f;
        for(int i = 0; i < count ; i++){
            frameTimeAverage += frameTimes[i];
        }
        frameTimeAverage/=count;
        
        if(frameTimeAverage>0){
            _fps = 1000.f / frameTimeAverage;
        }
        else{
            _fps = 60.f;
        }
    }
}

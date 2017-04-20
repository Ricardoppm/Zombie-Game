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
    
    FpsLimiter::FpsLimiter(){}
    
    void FpsLimiter::init(float maxFPS)
    {
        setTargetFPS(maxFPS);
    }
    
    void FpsLimiter::setTargetFPS(float maxFPS){ maxFPS_ = maxFPS; }
    
    void FpsLimiter::begin()
    {
        startTicks_
        = SDL_GetTicks();
    }
    
    float FpsLimiter::end()
    {
        calculateFPS();
        
        float frameTicks = SDL_GetTicks() - startTicks_;
        // Limit FPS to maxFPS
        if( 1000.0f/maxFPS_ > frameTicks){
            SDL_Delay(1000.0f/maxFPS_ - frameTicks);
        }
        
        return fps_;
    }
    
    void FpsLimiter::calculateFPS()
    {
        static const int NUM_SAMPLES = 10;
        static float frameTimes[NUM_SAMPLES];
        static int currentFrame = 0;
        static float previousTicks = SDL_GetTicks();
        
        float currentTicks;
        currentTicks = SDL_GetTicks();
        
        frameTime_ = currentTicks - previousTicks;
        frameTimes[ currentFrame % NUM_SAMPLES] = frameTime_;
        
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
            fps_ = 1000.f / frameTimeAverage;
        }
        else{
            fps_ = 60.f;
        }
    }
}

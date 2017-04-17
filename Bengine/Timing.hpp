//
//  Timing.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 17/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Timing_hpp
#define Timing_hpp

namespace Bengine {
    
    class FpsLimiter
    {
    public:
        FpsLimiter();
        void init(float maxFPS);
        
        void setTargetFPS(float maxFPS);
        
        void begin();
        // end will return the fps
        float end();
    
    private:
        void calculateFPS();
        
        
        // FPS calculation
        float _fps;
        float _frameTime;
        float _maxFPS;

        unsigned int _startTicks;
    };
}
#endif /* Timing_hpp */

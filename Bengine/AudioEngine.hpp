//
//  AudioEngine.hpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 20/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef AudioEngine_hpp
#define AudioEngine_hpp

#include <SDL2_mixer/SDL_mixer.h>
#include <string>
#include <map>

namespace Bengine {
    
    class SoundEffect
    {
    public:
        friend class AudioEngine;
        
        /// Plays the effect audio file
        /// @param loops : if loops = -1, loop forever,
        /// otherwise play it loops + 1 times
        void play(int loops = 0);
        
    private:
        Mix_Chunk* chunk_ = nullptr;
    };
    
    class Music
    {
    public:
        friend class AudioEngine;
        
        /// Plays the music audio file
        /// @param loops : if loops = -1, loop forever,
        /// otherwise play it loops times
        void play(int loops = 1);
        
        static void pause();
        static void stop();
        static void resume();
        
    private:
        Mix_Music* music_ = nullptr;
    };
    
    class AudioEngine
    {
    public:
        AudioEngine();
        ~AudioEngine();
    
        void init();
        
        void destroy();
        
        SoundEffect loadSoundEffect(const std::string& filePath);
        
        Music loadMusic( const std::string& filePath);
        
    private:
        bool isInitialized_ = false;
        
        std::map<std::string, Mix_Chunk*> effectMap_;
        std::map<std::string, Mix_Music*> musicMap_;

    };
}

#endif /* AudioEngine_hpp */

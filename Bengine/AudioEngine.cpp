//
//  AudioEngine.cpp
//  Zombie-Game
//
//  Created by Ricardo Martins on 20/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "AudioEngine.hpp"

#include "errors.hpp"

namespace Bengine {
    // SoundEffect functions
    void SoundEffect::play(int loops)
    {
        if(Mix_PlayChannel(-1, chunk_, loops) == -1){
            // TODO improve override method, use oldest channel
            // Override channel 0 if all occupied
            if(Mix_PlayChannel(0, chunk_, loops) == -1){
                Bengine::fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
            }
        }
    }
    
    // Music funtions
    void Music::play(int loops)
    {
        if(Mix_PlayMusic(music_, loops) == -1){
            Bengine::fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
        }
    }
    
    void Music::pause() { Mix_PauseMusic(); }
    
    void Music::stop(){ Mix_HaltMusic(); }
    
    void Music::resume(){ Mix_ResumeMusic(); }
    
    // AudioEngine function
    AudioEngine::AudioEngine(){}
    
    AudioEngine::~AudioEngine()
    {
        destroy();
    }
    
    void AudioEngine::init()
    {
        if (isInitialized_) {
            Bengine::fatalError("Tried to  initialize AudioEngine twice!");
        }
        // Initialize Mixer
        // MIX_INIT_FAC , MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
        if( Mix_Init(MIX_INIT_MP3 || MIX_INIT_OGG) == -1){
            Bengine::fatalError("Mix_init error: " + std::string(Mix_GetError()));
        }
        
        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1){
            Bengine::fatalError("Mix_init error: " + std::string(Mix_GetError()));
        }
        isInitialized_ = true;
    }
    
    void AudioEngine::destroy()
    {
        if( isInitialized_){
            isInitialized_ = false;
            for (auto& it : effectMap_) {
                Mix_FreeChunk(it.second);
            }
            for (auto& it : musicMap_) {
                Mix_FreeMusic(it.second);
            }
            effectMap_.clear();
            musicMap_.clear();
            
            Mix_CloseAudio();
            Mix_Quit();
        }
    }
    
    SoundEffect AudioEngine::loadSoundEffect(const std::string &filePath)
    {
        SoundEffect effect;
        
        auto it = effectMap_.find(filePath);
        if( it == effectMap_.end()){
            // Sound effect needs to be loaded
            Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
            if( chunk == nullptr){
                Bengine::fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
            }
            
            effectMap_[filePath] = chunk;
            effect.chunk_ = chunk;
        }
        else{
            effect.chunk_ = it->second;
        }
        return effect;
    }
    
    Music AudioEngine::loadMusic(const std::string &filePath)
    {
        Music music;
        
        auto it = musicMap_.find(filePath);
        if( it == musicMap_.end()){
            // Sound effect needs to be loaded
            Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
            if( mixMusic == nullptr){
                Bengine::fatalError("Mix_LoadMUS error: " + std::string(Mix_GetError()));
            }
            
            musicMap_[filePath] = mixMusic;
            music.music_ = mixMusic;
        }
        else{
            music.music_ = it->second;
        }
        return music;
    }
}

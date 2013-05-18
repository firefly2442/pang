#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class IAudioProvider
{
public:
    virtual ~IAudioProvider() {}
    virtual void PlaySound(std::string filename) = 0;
    virtual void PlaySong(std::string filename, bool looping) = 0;
    virtual void StopAllSounds() = 0;

    virtual bool IsSoundPlaying() = 0;
    virtual bool IsSongPlaying() = 0;
};
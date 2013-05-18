#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "IAudioProvider.h"

class ServiceLocator
{
public:
    static IAudioProvider* GetAudio()  {
        return _audioProvider;
    } const

    static void RegisterServiceLocator(IAudioProvider *provider)
    {
        _audioProvider = provider;
    }

private:
    static IAudioProvider * _audioProvider;
};


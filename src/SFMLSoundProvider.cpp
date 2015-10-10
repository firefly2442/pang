#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "SFMLSoundProvider.h"
#include "SoundFileCache.h"
#include "Logger.h"

#include <stdexcept>

SFMLSoundProvider::SFMLSoundProvider() :
    _currentSongName("")
{
}

void SFMLSoundProvider::PlaySound(std::string filename)
{
    int availChannel = -1;
    for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
    {
        if(_currentSounds[i].getStatus() != sf::Sound::Playing)
        {
            availChannel = i;
            break;
        }
    }

    // If all sound channels are in use, do nothing for now
    if(availChannel != -1)
    {
        try
        {
            _currentSounds[availChannel] = _soundFileCache.GetSound(filename);
            _currentSounds[availChannel].play();
        }
        catch(SoundNotFoundException& snfe)
        {
            // ERROR, file wasnt found, should handle error here
            ERROR << "sound file not found.";
			///@todo: fix me
        }
    }


}

void SFMLSoundProvider::PlaySong(std::string filename, bool looping)
{
    sf::Music * currentSong;
    try
    {
        currentSong = _soundFileCache.GetSong(filename);
    }
    catch(SoundNotFoundException&)
    {
        // This one is dire, means we couldn't find or load the selected song
        ERROR << "sound not found exception";
        // So, lets exit!
        return;
    }
    // See if prior song is playing still, if so, stop it
    if(_currentSongName != "")
    {
        try
        {
            sf::Music* priorSong = _soundFileCache.GetSong(_currentSongName);
            if(priorSong->getStatus() != sf::Sound::Stopped)
            {
                priorSong->stop();
            }
        }
        catch(SoundNotFoundException&)
        {
            // Do nothing, this exception isn't dire.  It simply means the previous sound we were
            // trying to stop wasn't located.
            WARN << "sound attempting to stop not found";
        }

    }
    _currentSongName = filename;
    currentSong->setLoop(looping);
    currentSong->play();
}

void SFMLSoundProvider::StopAllSounds()
{
    for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
    {
        _currentSounds[i].stop();
    }

    if(_currentSongName != "")
    {
        sf::Music * currentSong = _soundFileCache.GetSong(_currentSongName);
        if(currentSong->getStatus() == sf::Sound::Playing)
        {
            currentSong->stop();
        }
    }
}

bool SFMLSoundProvider::IsSoundPlaying()
{
    for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
    {
        if(_currentSounds[i].getStatus() == sf::Sound::Playing)
            return true;
    }
    return false;
}


bool SFMLSoundProvider::IsSongPlaying()
{
    if(_currentSongName != "")
    {
        return _soundFileCache.GetSong(_currentSongName)->getStatus() == sf::Music::Playing;
    }
    return false;
}



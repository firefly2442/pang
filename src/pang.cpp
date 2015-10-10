
////////////////////////////////////////////////////////////
// Main Headers
// These are in place of the precompiled header
////////////////////////////////////////////////////////////
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>
////////////////////////////////////////////////////////////


#include "Game.h"


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{

    Game::Start();

    return EXIT_SUCCESS;
}

///@todo figure out the desktop resolution and use that instead of defaulting
//to this set resolution and aspect ratio
int Game::width = 800;
int Game::height = 600;


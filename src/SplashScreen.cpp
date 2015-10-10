#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <sfeMovie/Movie.hpp>

#include <map>
#include <iostream>
#include <cassert>


#include "SplashScreen.h"
#include "Game.h"
#include "Logger.h"

void SplashScreen::Show(sf::RenderWindow &renderWindow)
{
    // Create and open intro movie
	sfe::Movie movie;
	//4:3 aspect ratio video file, OGG Theora format
	if (!movie.openFromFile("./resources/movies/pang_intro.ogg"))
		ERROR << "Unable to open intro movie!";

    // Scale movie to the window drawing area
	movie.fit(0, 0, renderWindow.getSize().x, renderWindow.getSize().y);

	movie.play();

    sf::Event event;
    while(true)
    {
        while(renderWindow.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed
                    || event.type == sf::Event::MouseButtonPressed
                    || event.type == sf::Event::Closed )
            {
                INFO << "Grabbed user interaction on SplashScreen, continuing on...";
                return;
            }
        }

        if(movie.getStatus() == sfe::Stopped) {
            return;
        }

		movie.update();

        renderWindow.clear();
        renderWindow.draw(movie);
        renderWindow.display();
    }
}

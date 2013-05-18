#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>


#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow &renderWindow)
{
	sf::Font font;
	if (!font.loadFromFile("resources/font/linden_hill.otf")) {
		std::cout << "Unable to load font" << std::endl;
	}

	sf::Text text("Pang", font, 40);
	text.setPosition(800/3, 600/3);

	renderWindow.draw(text);

	renderWindow.display();

    sf::Event event;
    while(true)
    {
        while(renderWindow.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed
                    || event.type == sf::Event::MouseButtonPressed
                    || event.type == sf::Event::Closed )
            {
                std::cout << "Grabbed user interaction on SplashScreen, continuing on..." << std::endl;
                return;
            }
        }
    }
}

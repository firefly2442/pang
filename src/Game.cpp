#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>

#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "SFMLSoundProvider.h"
#include "ServiceLocator.h"
#include "AIPaddle.h"

void Game::Start(void)
{
    if(_gameState != Uninitialized)
        return;

    _mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pang");

    //_mainWindow.SetFramerateLimit(60);

    SFMLSoundProvider soundProvider;
    ServiceLocator::RegisterServiceLocator(&soundProvider);

	// use "sndfile-info" and "ogginfo" to check validity of .ogg files
    soundProvider.PlaySong("resources/sound/Soundtrack.ogg", true);

    PlayerPaddle *player1 = new PlayerPaddle();
    player1->SetPosition((SCREEN_WIDTH/2)-45, 500);

    AIPaddle *player2 = new AIPaddle();
    player2->SetPosition((SCREEN_WIDTH/2)-45, 30);

    GameBall *ball = new GameBall();
    ball->SetPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

    _gameObjectManager.Add("Paddle1", player1);
    _gameObjectManager.Add("Paddle2", player2);
    _gameObjectManager.Add("Ball", ball);

    _gameState= Game::ShowingSplash;

    std::cout << "Showing Splash Screen" << std::endl;

    while(!IsExiting())
    {
        GameLoop();
    }

	// close down app at this point
	// @TODO: look into memory management and cleanup, is this needed with smart pointers?
	// we don't want memory leaks!
    _mainWindow.close();
}

bool Game::IsExiting()
{
    if(_gameState == Game::Exiting)
        return true;
    else
        return false;
}

sf::RenderWindow& Game::GetWindow()
{
    return _mainWindow;
}

void Game::GameLoop()
{
    sf::Event currentEvent;
    _mainWindow.pollEvent(currentEvent);

    switch(_gameState)
    {
		case Game::ShowingMenu:
		{
		    ShowMenu();
		    break;
		}
		case Game::ShowingSplash:
		{
		    ShowSplashScreen();
		    break;
		}
		case Game::Playing:
		{
		    _mainWindow.clear(sf::Color(255,0,0));

		    _gameObjectManager.UpdateAll();
		    _gameObjectManager.DrawAll(_mainWindow);

		    _mainWindow.display();

		    if(currentEvent.type == sf::Event::Closed)
		    {
		        _gameState = Game::Exiting;
		    }

		    if (currentEvent.type == sf::Event::KeyPressed)
		    {
		        if (currentEvent.key.code == sf::Keyboard::Escape)
		            ShowMenu();
		    }
		    break;
		}
    }
}

void Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    splashScreen.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
    switch(result)
    {
		case MainMenu::Play:
		{
		    std::cout << "Starting gameplay..." << std::endl;
		    _gameState = Game::Playing;
		    break;
		}
		case MainMenu::Exit:
		{
		    std::cout << "Exiting..." << std::endl;
		    _gameState = Game::Exiting;
		    break;
		}
    }
}


const GameObjectManager& Game::GetGameObjectManager()
{
    return Game::_gameObjectManager;
}


Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;

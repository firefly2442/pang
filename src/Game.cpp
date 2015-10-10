#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>

#include "Game.h"
#include "MainMenu.h"
#include "PreferencesMenu.h"
#include "SplashScreen.h"
#include "SFMLSoundProvider.h"
#include "ServiceLocator.h"
#include "AIPaddle.h"
#include "Logger.h"

void Game::Start(void)
{
    if(_gameState != Uninitialized)
        return;

    _mainWindow.create(sf::VideoMode(Game::width, Game::height, 32), "Pang");

    //_mainWindow.SetFramerateLimit(60);

    ServiceLocator::RegisterServiceLocator(&soundProvider);

	// use "sndfile-info" and "ogginfo" to check validity of .ogg files
    soundProvider.PlaySong("resources/sound/Soundtrack.ogg", true);

    PlayerPaddle *player1 = new PlayerPaddle();
    player1->SetPosition((Game::width/2)-45, Game::height-50);

    AIPaddle *player2 = new AIPaddle();
    player2->SetPosition((Game::width/2)-45, 30);

    GameBall *ball = new GameBall();
    ball->SetPosition(Game::width/2, Game::height/2);

    _gameObjectManager.Add("Paddle1", player1);
    _gameObjectManager.Add("Paddle2", player2);
    _gameObjectManager.Add("Ball", ball);

    _gameState= Game::ShowingSplash;

    INFO << "Showing Splash Screen";

    while(!IsExiting())
    {
        GameLoop();
    }

	// close down app at this point
	///@todo: look into memory management and cleanup, is this needed with smart pointers?
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
		case Game::ShowingPreferencesMenu:
		{
		    ShowPreferences();
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
		        if (currentEvent.key.code == sf::Keyboard::Escape) {
		            ///@todo: pause game here instead of going back to main menu
		            _gameState = Game::ShowingMenu;
		        }
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
		    INFO << "Starting gameplay...";
		    _gameState = Game::Playing;
		    break;
		}
		case MainMenu::Preferences:
		{
		    INFO << "Opening preferences menu...";
		    _gameState = Game::ShowingPreferencesMenu;
		    break;
		}
		case MainMenu::Exit:
		{
		    INFO << "Exiting...";
		    _gameState = Game::Exiting;
		    break;
		}
    }
}

void Game::ShowPreferences()
{
    PreferencesMenu prefMenu;
    prefMenu.Show(_mainWindow);

    _gameState = ShowingMenu;
}


const GameObjectManager& Game::GetGameObjectManager()
{
    return Game::_gameObjectManager;
}


SFMLSoundProvider Game::soundProvider;
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;

bool PreferencesMenu::playingMusic = true;
bool PreferencesMenu::fullscreenMode = false;

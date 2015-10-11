#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "PlayerPaddle.h"
#include "GameBall.h"
#include "GameObjectManager.h"
#include "SFMLSoundProvider.h"

class Game
{

public:
    static void Start();
    static sf::RenderWindow& GetWindow();
    const static sf::Event& GetInput();
    const static GameObjectManager& GetGameObjectManager();

    static SFMLSoundProvider soundProvider;

    static int width;
    static int height;


private:
    static bool IsExiting();
    static void GameLoop();

    static void ShowSplashScreen();
    static void ShowMenu();
    static void ShowPreferences();

    enum GameState
    {
        Uninitialized,
        ShowingSplash,
        Paused,
        ShowingMenu,
        ShowingPreferencesMenu,
        SetupPlaying,
        Playing,
        Exiting
    };

    static GameState _gameState;
    static sf::RenderWindow _mainWindow;

    static GameObjectManager _gameObjectManager;
};


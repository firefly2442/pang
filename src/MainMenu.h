#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

// Including SFGUI.hpp includes the entire SFGui system
#include <SFGUI/SFGUI.hpp>

class MainMenu
{

public:
    enum MenuResult
    {
        Nothing,
        Exit,
        Preferences,
        Play
    };


    MenuResult Show(sf::RenderWindow& window);

private:
    MenuResult GetMenuResponse(sf::RenderWindow& window);
    void ClickPlay();
    void ClickPref();
    void ClickExit();

    MenuResult clickedMenuValue;


    sfg::SFGUI sfgui;
    sfg::Window::Ptr sfguiWindow;
};

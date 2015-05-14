#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

// Including SFGUI.hpp includes the entire SFGui system
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

class PreferencesMenu
{

public:
    enum PreferencesResult
    {
        Nothing,
        Sound,
        Fullscreen,
        Resolution,
        Back
    };

    static bool playingMusic;
    static bool fullscreenMode;

    void Show(sf::RenderWindow& window);

private:
    void GetMenuResponse(sf::RenderWindow& window);
    void ClickSound();
    void ClickFullscreen();
    void ClickResolution();
    void ClickBack();
    void ResetWindowResolution();

    PreferencesResult clickedValue;

    struct Resolution {
        int width;
        int height;
    };

    std::vector<struct Resolution> resolutions;

    sfg::CheckButton::Ptr soundToggle;
    sfg::ComboBox::Ptr resolutionComboBox;
    sfg::CheckButton::Ptr fullscreenToggle;

    sfg::SFGUI sfgui;
    sfg::Window::Ptr sfguiWindow;
};

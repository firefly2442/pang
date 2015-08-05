#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>

#include "PreferencesMenu.h"
#include "Game.h"


void PreferencesMenu::Show(sf::RenderWindow& window)
{
    //Use SFGUI to create menu

    // We have to do this because we don't use SFML to draw.
    window.resetGLStates();

    clickedValue = Nothing;

    sfguiWindow = sfg::Window::Create();
    sfguiWindow->SetTitle("Preferences");

	// this sets the minimum size of the window
	sfguiWindow->SetRequisition(sf::Vector2f((float)Game::width*.8, (float)Game::height*.8));

    // Since only being able to add one widget to a window is very limiting
    // there are Box widgets. They are a subclass of the Container class and
    // can contain an unlimited amount of child widgets. Not only that, they
    // also have the ability to lay out your widgets nicely.

    //New widgets will be incrementally added vertically
    sfg::Box::Ptr box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    sfg::Box::Ptr box_res = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

    soundToggle = sfg::CheckButton::Create("Sound");
    sfg::Label::Ptr resolutionLabel = sfg::Label::Create("Resolution:");
    resolutionComboBox = sfg::ComboBox::Create();
    fullscreenToggle = sfg::CheckButton::Create("Fullscreen");
    sfg::Button::Ptr backButton = sfg::Button::Create("Back");

    // Create a separator.
	sfg::Separator::Ptr separator = sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL);

    soundToggle->GetSignal(sfg::ToggleButton::OnToggle).Connect(std::bind(&PreferencesMenu::ClickSound, this));
    resolutionComboBox->GetSignal(sfg::ComboBox::OnSelect).Connect(std::bind(&PreferencesMenu::ClickResolution, this));
    fullscreenToggle->GetSignal(sfg::ToggleButton::OnToggle).Connect(std::bind(&PreferencesMenu::ClickFullscreen, this));
    backButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PreferencesMenu::ClickBack, this));

    //set sound toggle based on preferences
    if (playingMusic)
        soundToggle->SetActive(true);

    //set fullscreen toggle based on preferences
    if (fullscreenMode)
        fullscreenToggle->SetActive(true);

    // list of all the video modes available for fullscreen
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
        if (mode.bitsPerPixel == 32) {
            std::string resolution = std::to_string(mode.width) + "x" + std::to_string(mode.height);
            resolutionComboBox->AppendItem(resolution);
            struct Resolution res;
            res.width = mode.width;
            res.height = mode.height;
            resolutions.push_back(res);
            if (mode.width == Game::width && mode.height == Game::height)
                resolutionComboBox->SelectItem(i);
        }
    }

    box->Pack(soundToggle);

    box_res->Pack(resolutionLabel, false, false);
    box_res->Pack(resolutionComboBox, false, true); //don't expand

    box->Pack(box_res, false, true);
    box->Pack(fullscreenToggle);

    // Add separator to box and set not to expand.
	box->Pack(separator, false, true);

	box->Pack(backButton, false, true); //don't expand

    box->SetSpacing(5.0f);

    sfguiWindow->Add(box);

    GetMenuResponse(window);
}

void PreferencesMenu::ClickSound()
{
    clickedValue = Sound;

	if(soundToggle->IsActive()) {
        Game::soundProvider.PlaySong("resources/sound/Soundtrack.ogg", true);
        playingMusic = true;
	}
	else {
        Game::soundProvider.StopAllSounds();
        playingMusic = false;
	}
}

void PreferencesMenu::ClickFullscreen()
{
    if(fullscreenToggle->IsActive()) {
        fullscreenMode = true;
    } else {
        fullscreenMode = false;
    }
    ResetWindowResolution();
    clickedValue = Fullscreen;
}

void PreferencesMenu::ClickResolution()
{
    ResetWindowResolution();
    clickedValue = Resolution;
}

void PreferencesMenu::ClickBack()
{
    resolutions.clear();

    clickedValue = Back;
}

void PreferencesMenu::ResetWindowResolution()
{
    //get selected resolution
    struct Resolution res;
    res = resolutions.at(resolutionComboBox->GetSelectedItem());

    if(fullscreenToggle->IsActive()) {
        Game::GetWindow().create(sf::VideoMode(res.width, res.height, 32), "Pang", sf::Style::Fullscreen);
    } else {
        Game::GetWindow().create(sf::VideoMode(res.width, res.height, 32), "Pang");
    }

    //set Game resolution properties
    Game::width = res.width;
    Game::height = res.height;
    std::cout << "Setting resolution: " << res.width << "x" << res.height << std::endl;

    //Reset SFGUI elements window size
    //@TODO: this doesn't seem to change the size
    sfguiWindow->SetRequisition(sf::Vector2f((float)Game::width*.8, (float)Game::height*.8));

    Game::GetWindow().resetGLStates();
}


void  PreferencesMenu::GetMenuResponse(sf::RenderWindow& window)
{
    sf::Event event;

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            sfguiWindow->HandleEvent(event);

            // user closes window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (clickedValue == Back)
        {
            //@TODO cleanup pointers and other things in memory?
            return;
        }

        sfguiWindow->Update(1.0f);
        window.clear();
        sfgui.Display(window);
        window.display();
    }
}

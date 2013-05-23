#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>


#include "MainMenu.h"


MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
    //Use SFGUI to create menu

    // We have to do this because we don't use SFML to draw.
    window.resetGLStates();

    clickedMenuValue = Nothing;

    sfguiWindow = sfg::Window::Create();
    sfguiWindow->SetTitle("Pang Main Menu");

	// this sets the minimum size of the window
	sfguiWindow->SetRequisition(sf::Vector2f(300.f, 100.f));

    // Since only being able to add one widget to a window is very limiting
    // there are Box widgets. They are a subclass of the Container class and
    // can contain an unlimited amount of child widgets. Not only that, they
    // also have the ability to lay out your widgets nicely.

    sfg::Box::Ptr box;
    //New widgets will be incrementally added vertically
    box = sfg::Box::Create(sfg::Box::VERTICAL);

    sfg::Button::Ptr playButton = sfg::Button::Create();
    sfg::Button::Ptr prefButton = sfg::Button::Create();
    sfg::Button::Ptr exitButton = sfg::Button::Create();
    playButton->SetLabel("Play Pang");
    prefButton->SetLabel("Preferences");
    exitButton->SetLabel("Exit");

    playButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&MainMenu::ClickPlay, this);
    prefButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&MainMenu::ClickPref, this);
    exitButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&MainMenu::ClickExit, this);

    box->Pack(playButton);
    box->Pack(prefButton);
    box->Pack(exitButton);

    box->SetSpacing(5.0f);

    sfguiWindow->Add(box);

    return GetMenuResponse(window);
}

void MainMenu::ClickPlay()
{
    clickedMenuValue = Play;
}

void MainMenu::ClickPref()
{
    clickedMenuValue = Preferences;
}

void MainMenu::ClickExit()
{
    clickedMenuValue = Exit;
}


MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
    sf::Event event;

    sfguiWindow->Refresh();

    while(true)
    {
        while(window.pollEvent(event))
        {
            if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) ||
                    event.type == sf::Event::Closed
              ) {
                window.close();
            }

            sfguiWindow->HandleEvent(event);
        }

        if (clickedMenuValue != Nothing)
        {
            //@TODO cleanup pointers and other things in memory?
            return clickedMenuValue;
        }

        sfguiWindow->Update(0.f);
        window.clear();
        sfgui.Display(window);
        window.display();
    }
}

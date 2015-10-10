#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>

#include "PlayerPaddle.h"
#include "Game.h"
#include "Logger.h"


PlayerPaddle::PlayerPaddle() :
    _velocity(0),
    _maxVelocity(600.0f)
{
    //constructor
    Load("resources/paddle.png");
    assert(IsLoaded());

    GetSprite().setOrigin(GetSprite().getLocalBounds().width/2, GetSprite().getLocalBounds().height/2);
}


PlayerPaddle::~PlayerPaddle()
{
    //destructor
}

void PlayerPaddle::Draw(sf::RenderWindow &rw)
{
    VisibleGameObject::Draw(rw);
}

float PlayerPaddle::GetVelocity() const
{
    return _velocity;
}

void PlayerPaddle::Update(float elapsedTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _velocity-= 3.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _velocity+= 3.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _velocity= 0.0f;
    } else {
		if (_velocity > 0) {
			_velocity-= 3.0f;
		} else {
			_velocity+= 3.0f;
		}
	}

    if(_velocity > _maxVelocity)
        _velocity = _maxVelocity;

    if(_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;


    sf::Vector2f pos = this->GetPosition();

    if (pos.x  < GetSprite().getLocalBounds().width/2 || pos.x > (Game::width - GetSprite().getLocalBounds().width/2))
    {
        _velocity = -_velocity; // Bounce by current velocity in opposite direction
    }

    GetSprite().move(_velocity * elapsedTime, 0);
}

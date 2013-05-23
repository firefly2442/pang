#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>
#include <cmath>

#include "GameBall.h"
#include "Game.h"


GameBall::GameBall() :
    _velocity(230.0f), //pixels per second speed
    _elapsedTimeSinceStart(0.0f)
{
    //constructor
    Load("resources/ball.png");
    assert(IsLoaded());

    GetSprite().setOrigin(15,15);

    //Generates a random number between 1 and 360.
    float random_integer = std::rand() % 360 + 1;
    _angle = random_integer;
    std::cout << "Angle: " << _angle << std::endl;
}


GameBall::~GameBall()
{
    //destructor
}

//Parameter is the time since last frame in seconds. VERY small number.
void GameBall::Update(float elapsedTime)
{
    //std::cout << "Time since last frame: " << elapsedTime << std::endl;
    _elapsedTimeSinceStart += elapsedTime;

    // Delay game from starting until 3 seconds have passed
    if (_elapsedTimeSinceStart < 3.0f)
        return;

    float moveAmount = _velocity  * elapsedTime;

    float moveByX = LinearVelocityX(_angle) * moveAmount;
    float moveByY = LinearVelocityY(_angle) * moveAmount;


    //collide with the left side of the screen
    if (GetPosition().x + moveByX <= 0 + GetWidth()/2 || GetPosition().x + GetHeight()/2 + moveByX >= Game::width)
    {
        //Ricochet!
        _angle = 360.0f - _angle;
        if (_angle > 260.0f && _angle < 280.0f)
            _angle += 20.0f;
        if (_angle > 80.0f && _angle < 100.0f)
            _angle += 20.0f;

        moveByX = -moveByX;
    }

    PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
    if (player1 != NULL)
    {
        sf::Rect<float> p1BB = player1->GetBoundingRect();

        if (p1BB.intersects(GetBoundingRect()))
        {
            _angle =  360.0f - (_angle - 180.0f);
            if (_angle > 360.0f)
                _angle -= 360.0f;

            moveByY = -moveByY;

            // Make sure ball isn't inside paddle
            if (GetBoundingRect().width > player1->GetBoundingRect().top)
            {
                SetPosition(GetPosition().x,player1->GetBoundingRect().top - GetWidth()/2 -1 );
            }

            // Now add "English" based on the players velocity.
            float playerVelocity = player1->GetVelocity();

            if (playerVelocity < 0)
            {
                // moving left
                _angle -= 20.0f;
                if(_angle < 0 )
                    _angle = 360.0f - _angle;
            }
            else if(playerVelocity > 0)
            {
                _angle += 20.0f;
                if(_angle > 360.0f)
                    _angle = _angle - 360.0f;
            }

            _velocity += 5.0f;
        }

        if (GetPosition().y - GetHeight()/2 <= 0)
        {
            _angle =  180 - _angle;
            moveByY = -moveByY;
        }

        if(GetPosition().y + GetHeight()/2 + moveByY >= Game::height)
        {
            std::cout << "Moving to middle screen..." << std::endl;
            // move to middle of the screen for now and randomize angle
            GetSprite().setPosition(Game::width/2, Game::height/2);
            _angle = (std::rand()%360)+1;
            _velocity = 230.0f;
            _elapsedTimeSinceStart = 0.0f;
        }

        GetSprite().move(moveByX,moveByY);
    } else {
        std::cout << "Something bad happened with the casting..." << std::endl;
    }
}

float GameBall::LinearVelocityX(float angle)
{
    angle -= 90;
    if (angle < 0)
        angle = 360 + angle;
    //@todo Use BOOST Pi constant
    return (float)std::cos( angle * ( 3.1415926 / 180.0f ));
}

float GameBall::LinearVelocityY(float angle)
{
    angle -= 90;
    if (angle < 0)
        angle = 360 + angle;
    //@todo Use BOOST Pi constant
    return (float)std::sin( angle * ( 3.1415926 / 180.0f ));
}

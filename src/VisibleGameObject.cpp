#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>


#include "VisibleGameObject.h"
#include "Logger.h"


VisibleGameObject::VisibleGameObject()
    : _isLoaded(false)
{
    //constructor
}


VisibleGameObject::~VisibleGameObject()
{
    //destructor
}

void VisibleGameObject::Load(std::string filename)
{
    if(_texture.loadFromFile(filename) == false)
    {
        _filename = "";
        _isLoaded = false;
    }
    else
    {
        _filename = filename;
        _sprite.setTexture(_texture);
        _isLoaded = true;
    }
}

float VisibleGameObject::GetHeight() const
{
    return _sprite.getLocalBounds().height;
}

float VisibleGameObject::GetWidth() const
{
    return _sprite.getLocalBounds().width;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
    return _sprite.getGlobalBounds();
}

void VisibleGameObject::Draw(sf::RenderWindow &renderWindow)
{
    if(_isLoaded)
    {
        renderWindow.draw(_sprite);
    }
}

void VisibleGameObject::Update(float elapsedTime)
{

}

void VisibleGameObject::SetPosition(float x, float y)
{
    if(_isLoaded)
    {
        _sprite.setPosition(x,y);
    }
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
    if (_isLoaded)
    {
        return _sprite.getPosition();
    }
    return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
    return _sprite;
}

bool VisibleGameObject::IsLoaded() const
{
    return _isLoaded;
}

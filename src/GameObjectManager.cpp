#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>



#include "GameObjectManager.h"


///@TODO look into using Boost smart pointers instead

GameObjectManager::GameObjectManager()
{
    //constructor
}

GameObjectManager::~GameObjectManager()
{
    //destructor
    //Documentation on std::for_each:
    //http://msdn.microsoft.com/en-us/library/e5sk9w9k.aspx
    std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
    _gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name)
{
    std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
    if (results != _gameObjects.end() )
    {
        delete results->second; //second refers to the second element in the std::pair
        _gameObjects.erase(results);
    }
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
    std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
    if (results == _gameObjects.end())
        return NULL;
    return results->second; //second refers to the second element in the std::pair

}

int GameObjectManager::GetObjectCount() const
{
    return _gameObjects.size();
}


void GameObjectManager::DrawAll(sf::RenderWindow &renderWindow)
{
    std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
    while (itr != _gameObjects.end())
    {
        itr->second->Draw(renderWindow);
        itr++;
    }
}

void GameObjectManager::UpdateAll()
{
    std::map<std::string,VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
    float timeDelta = clock.restart().asSeconds();

    while(itr != _gameObjects.end())
    {
        itr->second->Update(timeDelta);
        itr++;
    }

}

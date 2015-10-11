#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>



#include "GameObjectManager.h"
#include "Logger.h"


GameObjectManager::GameObjectManager()
{
    //constructor
}

GameObjectManager::~GameObjectManager()
{
    //destructor
    //Documentation on std::for_each:
    //http://msdn.microsoft.com/en-us/library/e5sk9w9k.aspx
    //std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
    ///@todo make absolutely sure that our unique_ptr objects are cleaned up
}

void GameObjectManager::Add(std::string name, std::unique_ptr<VisibleGameObject> gameObject)
{
    _gameObjects.insert(std::pair<std::string, std::unique_ptr<VisibleGameObject>>(name, std::move(gameObject)));
}

void GameObjectManager::Remove(std::string name)
{
    std::map<std::string, std::unique_ptr<VisibleGameObject>>::iterator results = _gameObjects.find(name);
    if (results != _gameObjects.end())
    {
        _gameObjects.erase(results);
    }
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
    std::map<std::string, std::unique_ptr<VisibleGameObject>>::const_iterator results = _gameObjects.find(name);
    if (results == _gameObjects.end())
        return NULL;
    return results->second.get(); //second refers to the second element in the std::pair
}

int GameObjectManager::GetObjectCount() const
{
    return _gameObjects.size();
}


void GameObjectManager::DrawAll(sf::RenderWindow &renderWindow)
{
    std::map<std::string, std::unique_ptr<VisibleGameObject>>::const_iterator itr = _gameObjects.begin();
    while (itr != _gameObjects.end())
    {
        itr->second->Draw(renderWindow);
        itr++;
    }
}

void GameObjectManager::UpdateAll()
{
    std::map<std::string, std::unique_ptr<VisibleGameObject>>::const_iterator itr = _gameObjects.begin();
    float timeDelta = clock.restart().asSeconds();

    while(itr != _gameObjects.end())
    {
        itr->second->Update(timeDelta);
        itr++;
    }

}

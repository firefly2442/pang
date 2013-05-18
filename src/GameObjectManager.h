#pragma once

#include "VisibleGameObject.h"

class GameObjectManager
{
public:
    GameObjectManager();
    ~GameObjectManager();

    void Add(std::string name, VisibleGameObject* gameObject);
    void Remove(std::string name);
    int GetObjectCount() const;
    VisibleGameObject* Get(std::string name) const;

    void DrawAll(sf::RenderWindow &renderWindow);
    void UpdateAll();

private:
    //std::map is a key/value pair, keys need to be unique!
    //In this case, the key is the name and the value is the game object
    std::map<std::string, VisibleGameObject*> _gameObjects;

    sf::Clock clock;

    //A functor
    //http://en.wikipedia.org/wiki/Function_object
    //A functor is simply an object that can be called like a function.
    //This is facilitated by overloading the function operator ()
    struct GameObjectDeallocator
    {
        void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
        {
            delete p.second; //second refers to the second element in the std::pair
        }
    };
};

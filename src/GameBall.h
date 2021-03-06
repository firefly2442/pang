#pragma once

#include "VisibleGameObject.h"


class GameBall : public VisibleGameObject
{
public:
    GameBall();
    virtual ~GameBall();

    void Update(float);
    void Reset();

private:
    float _velocity; //pixels per second speed
    float _angle;
    float _elapsedTimeSinceStart;

    float LinearVelocityX(float angle);
    float LinearVelocityY(float angle);
};


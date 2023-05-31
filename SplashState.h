#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "State.h"

namespace game
{
    class SplashState : public State
    {
    public:
        SplashState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef _data;

        sf::Clock _clock;

        sf::Sprite _background;
    };
}
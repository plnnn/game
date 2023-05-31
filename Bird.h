#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Game.h"
#include <vector>

namespace game
{
    class Bird
    {
    public:
        Bird(GameDataRef data);

        void DrawBird();
        void Animate(float dt);
        void Update(float dt);
        void Tap();
        const sf::Sprite &GetSprite() const;
    private:
        GameDataRef _data;

        sf::Sprite _birdSprite;

        std::vector < sf::Texture > _animationFrames;
        unsigned int _animationIterator;

        sf::Clock _clock;
        sf::Clock _movementClock;

        int _birdState;
        float _rotation;
    };
}
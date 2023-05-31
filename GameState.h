#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"
#include "State.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"
#include "HUD.h"

namespace game
{
    class GameState : public State
    {
    public:
        GameState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef _data;

        sf::Sprite _background;

        Pipe *pipe;
        Land *land;
        Bird *bird;
        Collision collision;
        Flash *flash;
        HUD *hud;

        sf::Clock clock;

        int _gameState;

        int _score;

        sf::SoundBuffer _hitSoundBuffer;
        sf::SoundBuffer _pointSoundBuffer;
        sf::SoundBuffer _wingSoundBuffer;

        sf::Sound _hitSound;
        sf::Sound _pointSound;
        sf::Sound _wingSound;
    };
}
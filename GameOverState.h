#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "State.h"
#include "DEFINITIONS.h"

namespace game
{
    class GameOverState : public State
    {
    public:
        GameOverState(GameDataRef data, int score);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef _data;

        sf::Sprite _background;

        sf::Sprite _gameOverTitle;
        sf::Sprite _gameOverContainer;
        sf::Sprite _retryButton;
        sf::Sprite _medal;

        sf::Text _scoreText;
        sf::Text _highScoreText;

        int _score;
        int _highScore;
    };
}
#include <sstream>
#include <iostream>

#include "GameState.h"
#include "GameOverState.h"

#include "DEFINITIONS.h"

namespace game
{
    GameState::GameState(GameDataRef data) : _data(data) {}

    void GameState::Init()
    {
        if (!_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
        {
            std::cout << "Error loading hit sound" << std::endl;
        }

        if (!_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
        {
            std::cout << "Error loading point sound" << std::endl;
        }

        if (!_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
        {
            std::cout << "Error loading wing sound" << std::endl;
        }

        _hitSound.setBuffer(_hitSoundBuffer);
        _hitSound.setVolume(0.5);
        _pointSound.setBuffer(_pointSoundBuffer);
        _pointSound.setVolume(0.5);
        _wingSound.setBuffer(_wingSoundBuffer);
        _wingSound.setVolume(0.5);

        _data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
        _data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
        _data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
        _data->assets.LoadTexture("Land", LAND_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
        _data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);

        _data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

        pipe = new Pipe(_data);
        land = new Land(_data);
        bird = new Bird(_data);
        flash = new Flash(_data);
        hud = new HUD(_data);

        _background.setTexture(_data->assets.GetTexture("Game Background"));

        _score = 0;
        hud->UpdateScore(_score);

        _gameState = GameStates::eReady;
    }

    void GameState::HandleInput()
    {
        sf::Event event;

        while (_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                _data->window.close();
            }

            if (_data->input.IsSpriteClicked(_background, sf::Mouse::Left, _data->window))
            {
                if (_gameState != GameStates::eGameOver)
                {
                    _gameState = GameStates::ePlaying;
                    bird->Tap();

                    _wingSound.play();
                }
            }
        }
    }

    void GameState::Update(float dt)
    {
        if (_gameState != GameStates::eGameOver)
        {
            bird->Animate(dt);
            land->MoveLand(dt);
        }

        if (_gameState == GameStates::ePlaying)
        {
            pipe->MovePipes(dt);

            if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
            {
                pipe->RandomizePipeOffset();

                pipe->SpawnBottomPipe();
                pipe->SpawnTopPipe();
                pipe->SpawnScoringPipe();

                clock.restart();
            }

            bird->Update(dt);

            auto landSprites = land->GetSprites();
            for (int i = 0; i < landSprites.size(); ++i)
            {
                if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, landSprites.at(i), 1.0f))
                {
                    _gameState = GameStates::eGameOver;

                    clock.restart();

                    _hitSound.play();
                }
            }

            auto pipeSprites = pipe->GetSprites();
            for (int i = 0; i < pipeSprites.size(); ++i)
            {
                if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, pipeSprites.at(i), 1.0f))
                {
                    _gameState = GameStates::eGameOver;

                    clock.restart();

                    _hitSound.play();
                }
            }

            if (_gameState == GameStates::ePlaying)
            {
                auto &scoringSprites = pipe->GetScoringSprites();
                for (int i = 0; i < scoringSprites.size(); ++i)
                {
                    if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, scoringSprites.at(i), 1.0f))
                    {
                        _score++;
                        hud->UpdateScore(_score);
                        scoringSprites.erase(scoringSprites.begin() + i);

                        _pointSound.play();
                    }
                }
            }
        }

        if (_gameState == GameStates::eGameOver)
        {
            flash->Show(dt);

            if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_STATE)
            {
                _data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);
            }
        }
    }

    void GameState::Draw(float dt)
    {
        _data->window.clear();

        _data->window.draw(_background);
        pipe->DrawPipes();
        land->DrawLand();
        bird->DrawBird();
        flash->Draw();
        hud->Draw();

        _data->window.display();
    }
}



























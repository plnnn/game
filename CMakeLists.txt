cmake_minimum_required(VERSION 3.23)
project(game)

set(CMAKE_CXX_STANDARD 14)
set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

add_executable(game main.cpp State.h StateMachine.cpp StateMachine.h AssetManager.cpp AssetManager.h InputManager.cpp InputManager.h Game.cpp Game.h DEFINITIONS.h SplashState.cpp SplashState.h MainMenuState.cpp MainMenuState.h GameState.cpp GameState.h GameOverState.cpp GameOverState.h Pipe.cpp Pipe.h Land.cpp Land.h Bird.cpp Bird.h Collision.cpp Collision.h Flash.cpp Flash.h HUD.cpp HUD.h)

set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(game sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
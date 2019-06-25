cmake_minimum_required(VERSION 3.8.2)
project(Space)

find_package(SFML 2.5.0 COMPONENTS graphics audio REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Space ./Animation.cpp
./UFO.cpp
./State.cpp
./Game.cpp
./LoseMenuState.cpp
./PlayingState.cpp
./StateMachine.cpp
./MainMenuState.cpp
./Button.cpp
./Invaders.cpp
./InvaderBullet.cpp
./WinMenuState.cpp
./PlayerBullet.cpp
./Main.cpp
./Text.cpp
./Player.cpp
./FPSCounter.cpp
./PlaySound.cpp
./Shield.cpp)
target_link_libraries(Space sfml-graphics sfml-audio)

file(COPY res/ DESTINATION ${CMAKE_BINARY_DIR}/res)


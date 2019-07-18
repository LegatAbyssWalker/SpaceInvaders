cmake_minimum_required(VERSION 3.0.2)
project(Space)

find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(Space ./UFO.cpp
./State.cpp
./StateMachine.cpp
./Game.cpp
./LoseMenuState.cpp
./PlayingState.cpp
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
./Shield.cpp
./Animation.cpp
./OStringText.cpp
./ToggleKey.cpp)
target_link_libraries(Space sfml-graphics sfml-audio)

file(COPY res/ DESTINATION ${CMAKE_BINARY_DIR}/res)


cmake_minimum_required(VERSION 3.0.2)
project(Space)

find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(Space .Animation.cpp
./Button.cpp
./Entity.cpp
./FPSCounter.cpp
./Game.cpp
./Invader.cpp
./InvaderBullet.cpp
./Button.cpp
./InvaderManager.cpp
./InvaderBullet.cpp
./Main.cpp
./MainMenuState.cpp
./OStringText.cpp
./PlaySound.cpp
./Player.cpp
./PlayerBullet.cpp
./PlayingState.cpp
./Shield.cpp
./StateMachine.cpp
./Text.cpp
./Textbox.cpp
./UFO.cpp)
target_link_libraries(Space sfml-graphics sfml-audio)

file(COPY res/ DESTINATION ${CMAKE_BINARY_DIR}/res)


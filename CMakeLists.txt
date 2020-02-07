cmake_minimum_required(VERSION 3.0.2)
project(Space)

find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(Space 
./Animation.cpp
./Button.cpp
./Entity.cpp
./FPSCounter.cpp
./Game.cpp
./Invader.cpp
./InvaderBullet.cpp
./InvaderManager.cpp
./Main.cpp
./MainMenuState.cpp
./OStringText.cpp
./Player.cpp
./PlayerBullet.cpp
./PlayingState.cpp
./PlaySound.cpp
./Shield.cpp
./Sound.cpp
./State.cpp
./StateMachine.cpp
./Text.cpp
./Textbox.cpp
./UFO.cpp)
target_link_libraries(Space sfml-graphics sfml-audio)

file(COPY res/ DESTINATION ${CMAKE_BINARY_DIR}/res)


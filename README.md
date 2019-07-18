# SpaceInvaders
* A recreation of _Space Invaders_ in C++/SFML. 
* Recreated by David A.K.A. LegatAbyssWalker


# Dependancies
* **SFML** Version **2.5.0** or **higher**!
* **C++17** with a **supporting compiler**!

# Current Version
* Version 1.2

# New Information with Current Version
* Used unique pointers for the `Player` and `Invaders` class.
* `MainMenuState` class objects `Text` and `Buttons` are now no longer pointers but simple objects.
* `Semi-Accurate sprite speeds to the original game.
* Better buttons style.
* Exact sounds to the original _Space Invaders_ game.
* Decreased the invader shooting code in `PlayingState.cpp` to around 10 lines of code using if statements and for loops.
* UFO's now give random points.
* Points are kept after winning game, however the points are then removed when you enter the _Main Menu_ or you quit the game.
* Better invader management using for loops.  
* Removed the `WinMenuState` and `LoseMenuState`. 
* Invaders change speed and song when there is now only one invader left on screen.
* Changed definition names in `MoreInfo.h`. 
* Changed sound names in the _res/souds/..._ folder. 
* Overall more organized code. 

# Current Ideas
* None.

# Bug Fixes
* UFO now leaves the screen entirely.
* Sounds are now only playing whenever needed to.

# More
* Youtube Channel                » www.YouTube.com/LegitMegaWalls-52
* Youtube Video of Creating Game » https://www.youtube.com/watch?v=aUVq3uuxbTM&t=20s
* Github                         » https://github.com/LegatLastAbyssWalker

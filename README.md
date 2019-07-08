# SpaceInvaders
A recreation of _Space Invaders_ in C++/SFML. 
Consisting of Aliens, UFO's, Player, Sounds, States, and more! Enjoy!
P.S., this is not a good version of the actual game and there are many bugs, but this is at least a good start!


# Dependancies
* **SFML** Version **2.5.0** or **higher**!
* **C++17** with a **supporting compiler**!

# Current Version
* Version 1.0 Released!

# New Information with Current Version
* Used a different for loop approach.
  - Before _int x = 0; x < example.size(); x++_, after _auto &example : example_.
* Redesigned the invader movements!
  - Timings are no longer used.
  - Using ticks for down movement.
  - Invaders move down when they touch a wall.
* Redesigned the invader shootings!
  - Only one timer.
  - Uses new _isInvaderDead()_ function to determine which invader can shoot.
  - Faster shootings from the invaders.
* Larger screen size.
* Score and lives system.
* Space Invaders font implimented.
* Sprites now have a *ORIGIN* for easier detection.
* Bullets now update to determine if they are on the screen or not.
* No longer limited timings for bullet use! Can use bullet once the current bullet touches something.
* Semi-accurate speeds for sprites.

# Current Ideas
* Finding and implimenting the IRL Space Invaders background song.
* Different point system for each invader.
* Add more flexibility in invader management.
* Record of the high score.
* Shields having accurate destruction as in the original game.

# Bug Fixes
* Fixed Minor Bugs

# More
* Youtube Channel                » www.YouTube.com/LegitMegaWalls-52
* Youtube Video of Creating Game » https://www.youtube.com/watch?v=aUVq3uuxbTM&t=20s
* Github                         » https://github.com/LegatLastAbyssWalker

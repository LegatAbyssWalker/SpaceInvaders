# SpaceInvaders
* A recreation of _Space Invaders_ in C++/SFML. 
* Recreated by David A.K.A. LegatAbyssWalker

# Dependancies
* **SFML** Version **2.5.0** or **higher**!
* **C++17** with a **supporting compiler**!

# Current Version
* Version **1.3**

# New Information on Current Version
* Finally uses an `InvaderManager` class to manage the `Invader` and `InvaderBullet` classes!
* New collision detection system!
* UFO movemnet is no longer based off of timings but simple logic.
* UFO appearances random timings with the `Random.h` and `chrono` header files!
* Better shield positioning.
* Used more `std::unique_ptr<...>` for classes.
* New animation system! **NOT USED IN THE GAME**
* Renamed `res/sounds/background/...` background names (switch 0 and 1).
* `Invader` and `Shield` classes are now **deleted** once collided with!
* Removed the `ToggleKey` class.
* Added an `Entity` class to store any entity data.
* Uses an enum class to determine `InvaderType`.
* Invaders now shoot multiple bullet once the amount of invaders are less than 20. 
* Multiple invader bullets!
* Changed the `PlaySound` class to a simple `Sound` class.
* Deleted and replicated unnecessary code.
* Added collision with `PlayerBullet` to `InvaderBullet`. 
* Replaced `int` keyword with `size_t`. 

# Warnings
* I have little-to-none experience in CMake, so unfortuntely my files cannot be in folders. Also, the **CMake.txt** file might not work correctly because, again, I have little-to-none experience in CMake. 

# Bugs
* `PlayerBullet` sometimes shoots twice for no reason. 

# Credits
* Kiroma » https://github.com/kiroma
  - Helping me with a lot of the code and teaching me the rights from wrongs.
* JoaoBapt » https://github.com/JoaoBaptMG
  - Helping me with the `InvaderManager` class and new collision detection system (also bug fixes).

# Media
* Youtube Channel                
  - » https://youtube.com/c/LegatAbyssWalker
* Youtube Video of Creating the **Original** Game (Version 0.1) 
  - » https://www.youtube.com/watch?v=aUVq3uuxbTM&t=20s
* Github                         
  - » https://github.com/LegatLastAbyssWalker

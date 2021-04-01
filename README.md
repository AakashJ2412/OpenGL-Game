# 2D OpenGL Game
## Computer Graphics Assignment-1

This assignment involves creating a 2D game using basic openGL functionality. It is done in C++, and all implementations besides OpenGL are coded from scratch using C++ STLs.

#### Installation

The project requires the GLEW, GLM, and GLFW libraries primarily. The other libraries are locally present in the sources folder. Please ensure these are working properly in the system.
Once the libraries are in order, these steps will help setup the build folder and create the executable:

```
mkdir build
cd build
cmake ..
make
./Maze_run
```

#### About Game

This game is created in the spirit of Among Us. The player starts of in the center of a randomly generated maze (done using the sidewinder algorithm). The player has two tasks to complete, the first of which activates powerups and obstacles that respectively increases or decreases the players score. The player is being constantly chased by an imposter, which is moving optimally by using breadth-first search(BFS). The second task, when reached, destroys the imposter. The goal of the game is to finish the two tasks and then exit the game.

#### Features

This game creates a random maze every time on startup. All initial object positions are randomly generated.
The imposter movement is optimally generated and is configured to mvoe centrally in cells. Thus, it can't be 'tricked' into a corner or dead end.
The game has a HUD in the top left corner that displays current game stats. In addition, there is an appropriate end game depending on victory/defeat.

#### Parameters

The keys to control the player are:

- W: Move up
- A: Move left
- S: Move down
- D: Move right

By pressing 'q', the player can exit the game at any time.

<br>
##
Aakash Jain
Roll No- 2019101028
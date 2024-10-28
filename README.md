# Endless Tetris

This project is a C++ OpenGL-based version of the classic Tetris game, with continuous gameplay until the game-over condition is met. The game includes different Tetromino shapes with rotation, vibrant colors, and basic control instructions on the start screen.

## Features

- **Seven Tetromino Types**: I, O, T, S, Z, J, and L with unique colors.
- **Continuous Gameplay**: Blocks automatically fall until they can no longer be placed.
- **User Controls**: Arrow keys for movement and rotation.
- **Start Screen**: Displays game controls and instructions before starting.
- **Game Over Notification**: Message displayed when there are no moves left.

## Setup and Installation

1. Ensure you have **OpenGL** and **GLUT** libraries installed.

2. Clone this repository to your local environment:

```bash
   git clone https://github.com/mintyspider/endless-tetris.git
```

3. Navigate to the project directory:

```bash
cd endless-tetris
```

4. Compile the code with a C++ compiler that supports OpenGL and GLUT, for example:

```bash
g++ tetris.cpp -o tetris -lGL -lGLU -lglut
```

5. Run the compiled program:

```bash
./tetris
```

## Controls

+ Enter - Start the game.
+ Esc - Exit the game.
+ Left Arrow - Move the current Tetromino left.
+ Right Arrow - Move the current Tetromino right.
+ Down Arrow - Accelerate the fall of the current Tetromino.
+ Up Arrow - Rotate the current Tetromino.

## How to Play

+ Run the game and press Enter to start.
+ Use the arrow keys to position and rotate the falling blocks to complete rows.
+ When a row is completely filled, it disappears, and the remaining blocks shift down.
+ The game ends when blocks stack to the top of the screen.

## Files

+ FreeglutApp.cpp: Contains the main game logic and rendering code.
+ GLUT/include/GL: Path for including GLUT, which can be adjusted based on your setup.

## Notes

+ The game has a retro-inspired color scheme for each Tetromino.
+ The timer function manages the continuous block descent, creating a sense of progression.
+ The game field is reset, and a new game starts when the current game is over and Enter is pressed again.

## Dependencies
OpenGL and GLUT: Graphics libraries for rendering and input handling.

## License
This project is licensed under the MIT License.
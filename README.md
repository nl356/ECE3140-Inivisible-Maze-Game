# CS 3420 Final Project
## Maze game
Invisible maze is a game that generates a maze based on a user-inputted seed number and allows the user to solve it. 
The player's interaction with the game is primarily visual, with the player's position displayed on an LED matrix. It is also a bit of a memory game where the maze is "invisible" and the player will have to keep track of where the walls in the maze are relative to their position on the LED matrix. 

Players interact with the game through a serial interface to a simple controller on a computer (the WASD keys)


### Wiring notes:
| PIN         | Port            | Notes |
| ----------- | ----------------| ------|
| PTD1        | SPI0_SCK        | CLK   |
| PTD3        | SPI0_SIN        | MISO  |
| PTD2        | SPI0_SOUT       | MOSI  |
| PTD0        | SPI0_PCS0       | CS    |

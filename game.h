/*
 * game.h
 *
 * Game state initialization and update functions.
 */

#ifndef GAME_H_
#define GAME_H_

#include "mbed.h"
#include "maze.h"


/*---------------------------------------------------------------
  Game state types
 *---------------------------------------------------------------*/

/**
 * Type of the game state.
 */
typedef struct {
	maze_t* maze;
	point_t curr_pos;
	uint game_complete;
	uint turns;
} state_t;



/*---------------------------------------------------------------
  Game state functions
 *---------------------------------------------------------------*/

/**
 * Converts a character to direction.
 */
direction interpret(char c);

/** 
 * Initializes the game with player's current position 
 * at the start of the maze (0,0). 
 */
state_t* init_state();

/**
 * Takes a step in the maze using an inputed direction
 * Updates state's current x and y position, but
 * only if move is possible, otherwise no updates.
 */
void take_step(direction x, state_t* state);

#endif /* GAME_H_ */

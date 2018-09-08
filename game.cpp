/*
 * game.cpp
 *
 */

#include "game.h"

/*---------------------------------------------------------------
  Game state functions
 *---------------------------------------------------------------*/

// Interprets user stroke to direction 
direction interpret(char c) {
	switch (c){
		case 's': return SOUTH;
		case 'a': return WEST;
		case 'w': return NORTH;
		case 'd': return EAST;
		default:  return NONE;
	}
}


// Updates the game state
void take_step (direction x, state_t* state) {
	step(x, &(state->curr_pos));
	return;
}


// Initializes state
state_t* init_state() {
	state_t* state = (state_t*) malloc(sizeof(state_t));
	maze_t* game_maze = init();
	
	state->maze = game_maze;
	point_t start = {0, 0};
	state->curr_pos = start;
	state->game_complete = 0;
	state->turns = 0;

	return state;
}

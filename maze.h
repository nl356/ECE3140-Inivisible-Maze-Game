/*
 * maze.h
 *
 * Maze generation and access functions.
 */

#ifndef MAZE_H_
#define MAZE_H_

#include "mbed.h"


/*---------------------------------------------------------------
  Maze types
 *---------------------------------------------------------------*/

/**
 * Type of the location in the maze.
 */
typedef struct {
	int x;
	int y;
} point_t;

/**
 * The set of movement directions.
 */
enum direction {NORTH, SOUTH, EAST, WEST, NONE};

/**
 * Each cell is encoded as a bit-string where
 * N - 1000
 * S - 0100
 * E - 0010
 * W - 0001
 *
 * where 1 indicates the cell is open in that direction
 * and 0 indicates there is a wall. Use or to create
 * combinations of directions like: N | E = NE (1010)
 */
typedef uint8_t cell;

/**
 * Type of a maze grid.
 */
typedef cell grid_t [8][8];

/**
 * The type of a maze.
 */
typedef struct {
	grid_t grid;
	point_t start;
	point_t exit;
} maze_t;



/*---------------------------------------------------------------
  Maze constants
 *---------------------------------------------------------------*/

extern int HEIGHT;
extern int WIDTH;


/*---------------------------------------------------------------
  Maze functions
 *---------------------------------------------------------------*/

/**
 * Translates a direction to the bit-string representation as
 * described in the specification of cell.
 */
cell mask_of(direction dir);

/**
 * Returns string representation of a direction.
 */
void print_direction(direction dir);

/**
 * Returns the opposite direction from a given direction.
 */
direction opposite(direction dir);

/**
 * Returns 1 if can move in the direction dir given the cell curr.
 */
bool can_move(direction dir, cell curr);

/**
 * Updates a point by moving in the specified direction.
 */
void step(direction dir, point_t* curr);

/**
 * Returns 1 if two points are equal.
 */
bool points_equal (point_t a, point_t b);

/**
 * Creates a randomly generated maze. Will return the same maze if srand
 * is seeded to the same value.
 */
maze_t* init();

#endif /* MAZE_H_ */


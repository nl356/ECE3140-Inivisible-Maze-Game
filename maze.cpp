/*
 * maze.cpp
 *
 */

#include "maze.h"

/*---------------------------------------------------------------
  Constants
 *---------------------------------------------------------------*/

int WIDTH = 8;
int HEIGHT = 8;


/*---------------------------------------------------------------
  Utility functions
 *---------------------------------------------------------------*/

// Directional abstraction - NSEW
cell mask_of(direction dir) {
	switch (dir){
	case NORTH: return 8;
	case SOUTH: return 4;
	case EAST: 	return 2;
	case WEST: 	return 1;
	default: 	return -1;
	}
}


// Gives opposite direction from a given direction
direction opposite(direction dir) {
	switch (dir){
	case NORTH: return SOUTH;
	case SOUTH: return NORTH;
	case EAST: 	return WEST;
	case WEST: 	return EAST;
	default: 	return NONE;
	}
}


// Prints the string representation of a direction
void print_direction(direction dir) {
	switch (dir) {
	case NORTH: printf("north"); break;
	case SOUTH: printf("south"); break;
	case EAST: 	printf("east"); break;
	case WEST:	printf("west"); break;
	default:	printf("none");
	}
	return;
}


// True if can move in a direction dir from cell curr
bool can_move(direction dir, cell curr) {
	return curr & mask_of(dir);
}


// Updates point_t curr based on given direction
void step(direction dir, point_t* curr) {
	switch (dir) {
	case NORTH: curr->y = (curr->y) - 1; break;
	case EAST: 	curr->x = (curr->x) + 1; break;
	case SOUTH: curr->y = (curr->y) + 1; break;
	case WEST: 	curr->x = (curr->x) - 1; break;
	default:	return;
	}
}


// Checks if two points are equal
bool points_equal (point_t a, point_t b) {
	return (a.x == b.x) && (a.y == b.y);
}

		
/*---------------------------------------------------------------
  Maze Generation
 *---------------------------------------------------------------*/

// Generate a maze via recursive backtracking
void backtrack(point_t pos, grid_t* grid) {
	direction dir[] = {NORTH, SOUTH, EAST, WEST};
	
	// Shuffle direction array via Fisher-Yates Shuffle
	for (int i = 3; i >= 0; i--) {
		 int j = rand() % (i + 1);
		 direction tmp = dir[j];
		 dir[j] = dir[i];
		 dir[i] = tmp;
	}

	for (int i = 0; i < 4; i++) {
		direction d = dir[i];
		// Go to next coordinate point_t
		point_t next = {pos.x, pos.y};
		step (d, &next);

		// Check if next cell is unvisited and in bounds
		if ((*grid)[next.y][next.x] == 0 &&
			0 <= next.x && next.x < WIDTH &&
			0 <= next.y && next.y < HEIGHT)
		{
			// Carve next cell
			(*grid)[next.y][next.x] = (*grid)[next.y][next.x] | mask_of(opposite(d));

			// Carve current cell
			(*grid)[pos.y][pos.x] = (*grid)[pos.y][pos.x] | mask_of(d);

			// Recursive Call
			backtrack(next, grid);
		}
	}
}


// Initialize a maze
maze_t* init() {
	// Allocate maze structure
	maze_t* maze = (maze_t*) calloc(1, sizeof(maze_t));
	
	// Set end position to (7,7)
	point_t end = {7,7};
	maze->exit = end;
	
	// Generate maze paths
	point_t start = {0, 0};
	backtrack(start, &(maze->grid));

	return maze;
}

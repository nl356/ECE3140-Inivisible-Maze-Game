/*
 * test.cpp
 *
 */

#include "test.h"

/* Test cases */

// A simple test for the LED matrix
// Requires that MATRIX device is initialized and enabled.
bool test_led() {
	printf("Starting LED test\n");

	// Flash all LEDs for 1 second
	mat.device_all_off(MATRIX);

	mat.device_all_on(MATRIX);
	wait(1);

	// Disable for 1 second
	mat.device_all_off(MATRIX);
	wait(1);

	// Flash each individual LED once
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			mat.write_digit(1, row + 1, 1 << col);
			wait(0.05);
		}
		mat.clear_digit(MATRIX, row + 1);
	}

	printf("Passed LED test\n");
	return true;
}


// Tests that initialization given the same seed results in the same maze.
bool test_init_maze() {
	printf("Starting maze init test\n");
	srand(0);
	maze_t* maze_1 = init();

	srand(0);
	maze_t* maze_2 = init();

	if (
		points_equal(maze_1->start, maze_2->start) &&
		points_equal(maze_1->exit, maze_2->exit)
	) {
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				if (maze_1->grid[y][x] != maze_2->grid[y][x]) {
					printf("Failed maze init test\n");
					return false;
				}
			}
		}
	} else {
		printf("Failed maze init test\n");
		return false;
	}

	printf("Passed maze init test\n");
	return true;
}


// Tests that opposite is giving the right directions
bool test_opposite() {
	printf("Starting opposite test\n");
	if (!(opposite(NORTH) == SOUTH)) {
		printf("Failed opposite direction test\n");
		return false;
	} else if (!(opposite(SOUTH) == NORTH)) {
		printf("Failed opposite direction test\n");
		return false;
	} else if (!(opposite(EAST) == WEST)) {
		printf("Failed opposite direction test\n");
		return false;
	} else if (!(opposite(WEST) == EAST)) {
		printf("Failed opposite direction test\n");
		return false;
	}
	printf("Passed opposite test\n");
	return true;
}

// Main test runner
void run_tests() {
	// Enable red LED during test
	led1.write(0);

	int passed = 0;
	int failed = 0;

	if (test_led()) {
		passed += 1;
	} else {
		failed += 1;
	}

	if (test_init_maze()) {
		passed += 1;
	} else {
		failed += 1;
	}

	if (test_opposite()) {
		passed += 1;
	} else {
		failed += 1;
	}

	if (passed) {
		printf("Passed %d tests\n", passed);
	}
	if (failed) {
		printf("Failed %d tests\n", failed);
	}
	printf("\n");

	wait(1);

	led1.write(1);
}

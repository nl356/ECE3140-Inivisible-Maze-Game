/*
 * main.cpp
 *
 */

#include "main.h"

/*---------------------------------------------------------------
  Device configuration
 *---------------------------------------------------------------*/

// Set up red LED
DigitalOut led1(LED1);

// Testing button
InterruptIn testButton(SW2);

// Play button
InterruptIn playButton(SW3);

// Set up serial over USB
Serial pc(USBTX, USBRX);

// Set up LED matrix on SPI0
Max7219 mat(PTD2, PTD3, PTD1, PTD0);

// Device number for LED matrix
uint8_t MATRIX = 1;

// Flag for board mode (0: play, 1: testing, 2: wait)
volatile int MODE = 2;


/*---------------------------------------------------------------
  Main game functions
 *---------------------------------------------------------------*/

void setTest() {
	MODE = 1;
}

void setPlay() {
	MODE = 0;
}

/*---------------------------------------------------------------
  Main game functions
 *---------------------------------------------------------------*/

// Prompts user until receives 'y' or 'n'
// Returns true if receives 'y' else false
bool yes_no() {
	while (true) {
		printf("y/n ");
		switch (pc.getc()) {
		case 'y':
		case 'Y':
			printf("\n");
			return true;
		case 'n':
		case 'N':
			printf("\n");
			return false;
		default:
			// prompt again for input
			printf("\ntype 'y' or 'n' ");
		}
	}
}


// Prints the state to console
void display(state_t* state) {

	maze_t* maze = state->maze;

	// Print top of maze
	printf(" ");
	for (int i = 0; i < WIDTH * 2 - 1; i++) {
		printf("_");
	}
	printf("\n");

	for (int i = 0; i < HEIGHT; i++) {
		printf("|");
		for (int j = 0; j < WIDTH; j++) {
			cell curr = maze->grid[i][j];

			if (can_move(SOUTH, curr)) {
				printf(" ");
			} else {
				printf("_");
			}

			if (can_move(EAST, curr)) {
				cell next = curr;
				if (j < WIDTH - 1) {
					next = maze->grid[i][j+1];
				}
				if (can_move(SOUTH, curr) | can_move(SOUTH, next)) {
					printf(" ");
				} else {
					printf("_");
				}
			} else {
				printf("|");
			}
		}
		printf("\n");
	}
}


// Individual game loop
void play (state_t* state){

	// While game is not completed yet (player hasn't arrived at finish)
	while (state->game_complete == 0){

		// Get current position
		point_t curr_p = state->curr_pos;
		cell curr_c = state->maze->grid[curr_p.y][curr_p.x];

		// If current position is the exit, game is finished
		if (points_equal(curr_p, state->maze->exit)) {
			state->game_complete = 1;

			printf("\nCongratulations! You have won in %d moves.\n", state->turns);

			// Blink LED matrix
			for (int i = 0; i < 10; i++) {
				mat.device_all_on(1);
				wait(0.1);

				mat.device_all_off(1);
				wait(0.1);
			}

			display(state);
			printf("\n");

			return;
		}

		printf("You're currently at position %d, %d\n", curr_p.y, curr_p.x);

		// Update LED
		mat.device_all_off(MATRIX);
		mat.write_digit(1, 1 + curr_p.x, 1 << curr_p.y);

		// Intended direction d and current cell
		printf("Input a direction: ");
		direction d = interpret(getchar());
		printf("\n");
		while (d == NONE) {
			printf("Try a valid direction (use WASD): ");
			d = interpret(getchar());
			printf("\n");
		}

		if (can_move(d, curr_c)) {
			// Update current position
			take_step(d, state);
		} else {
			printf("You can't go ");
			print_direction(d);
			printf(" here!\n");
		}

		printf("\n");

		state->turns = state->turns + 1;

	}
}

// Callback to start main game loop
void play_game() {
	// As for input to seed random generator if not testing
	printf("Enter a random number to setup the maze game: ");
	int seed;
	scanf("%20d", &seed);
	srand(seed);

	while (1) {
		printf("Welcome to the invisible maze!\n");

		mat.device_all_off(MATRIX);
		led1.write(1);

		printf("\n");

		state_t* state = init_state();

		printf("Do you want to see the maze? ");
		if (yes_no()) {
			printf("\n");
			display(state);
			wait(5);
			// Clear screen
			pc.putc(27);
			pc.printf("[2J");
			// Set cursor to home
			pc.putc(27);
			pc.printf("[H");
		}

		play(state);

		printf("Play again? ");
		if (yes_no()) {
			printf("\n");
			continue;
		} else {
			printf("\n");
			break;
		}
	}
}


// Initial game start up
int main() {
	// Configure the LED matrix
    max7219_configuration_t cfg = {
        .device_number = MATRIX,
        .decode_mode = 0,
        .intensity = Max7219::MAX7219_INTENSITY_8,
        .scan_limit = Max7219::MAX7219_SCAN_8
    };

    mat.init_device(cfg);
    mat.enable_device(MATRIX);
	mat.device_all_off(MATRIX);
	led1.write(1);

    // Bind callback functions to buttons
    testButton.rise(&setTest);
    playButton.rise(&setPlay);

    printf("Press SW2 to run tests or press SW3 to run game.\n");

	// Wait for button to be pressed to set mode
	while (MODE == 2);
	if (MODE == 1) {
		run_tests();
	} else {
		play_game();
	}

	while (true);
	return 0;
}

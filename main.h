/*
 * main.h
 *
 * Exposes some values from main used for testing.
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "mbed.h"
#include "max7219.h"
#include "maze.h"
#include "game.h"
#include "test.h"

// Expose red LED for tests
extern DigitalOut led1;

// Expose LED matrix on SPI0 for tests
extern Max7219 mat;

// Device number for LED matrix exposed for tests
extern uint8_t MATRIX;

#endif /* MAIN_H_ */

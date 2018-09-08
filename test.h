/*
 * test.h
 *
 * Test cases.
 */

#ifndef TEST_H_
#define TEST_H_

#include "main.h"

/**
 * A simple LED test.
 */
bool test_led();

/**
 * Maze initialization test.
 */
bool test_init_maze();


/**
 * Opposite direction function test.
 */
bool test_opposite();

/**
 * Main test runner.
 */
void run_tests();

#endif /* TEST_H_ */

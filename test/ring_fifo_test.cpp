/*
 * ring_fifo_test.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: fanl
 */
#include "CppUTest/TestHarness.h"
#include "CppUTest/MemoryLeakDetector.h"

extern "C" {
#include "chelper/ring_fifo.h"
#include "ring_fifo.c"
}

TEST_GROUP(ring_fifo)
{
	void setup()
	{
	}

	void teardown()
	{
	}
};

TEST(ring_fifo, instances)
{
	ring_fifo_t cut;

	ring_fifo_init(&cut, 1, 10);
	ring_fifo_deinit(&cut);

	uint8_t buffer_data[10];
	ring_fifo_init_buffer(&cut, buffer_data, 10, 1);
	ring_fifo_deinit(&cut);
}

TEST(ring_fifo, add_peek_full_pop)
{
	ring_fifo_t cut;

	ring_fifo_init(&cut, 5, 3);

	CHECK_FALSE(ring_fifo_peek(&cut));
	CHECK_FALSE(ring_fifo_is_full(&cut));
	CHECK_TRUE(ring_fifo_is_empty(&cut));

	ring_fifo_push(&cut, (BUFFER_PTR_RDOLY)"ABCD");

	CHECK_TRUE(ring_fifo_peek(&cut));
	CHECK_FALSE(ring_fifo_is_full(&cut));
	CHECK_FALSE(ring_fifo_is_empty(&cut));
	CHECK_EQUAL(*"ABCD", *ring_fifo_peek(&cut));

	ring_fifo_push(&cut, (BUFFER_PTR_RDOLY)"ABCD");
	CHECK_TRUE(ring_fifo_push(&cut, (BUFFER_PTR_RDOLY)"ABCD"));

	CHECK_TRUE(ring_fifo_is_full(&cut));
	CHECK_FALSE(ring_fifo_push(&cut, (BUFFER_PTR_RDOLY)"ABCD"));

	uint8_t ch;
	CHECK_TRUE(ring_fifo_pop(&cut, (BUFFER_PTR)&ch));
	CHECK_TRUE(ring_fifo_pop(&cut, NULL));
	CHECK_TRUE(ring_fifo_pop(&cut, NULL));
	CHECK_TRUE(ring_fifo_is_empty(&cut));
	CHECK_FALSE(ring_fifo_pop(&cut, NULL));

	ring_fifo_deinit(&cut);
}

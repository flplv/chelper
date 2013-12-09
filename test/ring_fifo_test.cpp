/*
 *    Copyright (c) 2013 Felipe Lavratti (felipe@andradeneves.com)
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *
 *    The above copyright notice and this permission notice shall be included in
 *    all copies or substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *    THE SOFTWARE.
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

TEST(ring_fifo, nocopy)
{
	ring_fifo_t cut;
	BUFFER_PTR pBuf;

	ring_fifo_init(&cut, 5, 3);

	CHECK_TRUE(ring_fifo_is_empty(&cut));

	pBuf = ring_fifo_zerocopy_push_start(&cut);
	memcpy(pBuf, (void *)"ABCD", 5);
	ring_fifo_zerocopy_push_finish(&cut);

	CHECK_FALSE(ring_fifo_is_empty(&cut));

	pBuf = ring_fifo_zerocopy_pop_start(&cut);
	STRCMP_EQUAL("ABCD", (const char *)pBuf);
	ring_fifo_zerocopy_pop_finish(&cut);

	CHECK_TRUE(ring_fifo_is_empty(&cut));

	ring_fifo_deinit(&cut);
}

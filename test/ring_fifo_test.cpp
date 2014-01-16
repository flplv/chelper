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
#include <pthread.h>
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

TEST(ring_fifo, nocopyfull)
{
	ring_fifo_t cut;
	BUFFER_PTR pBuf;

	ring_fifo_init(&cut, 5, 3);

	CHECK_TRUE(ring_fifo_is_empty(&cut));
	CHECK_FALSE(ring_fifo_is_full(&cut));

	pBuf = ring_fifo_zerocopy_push_start(&cut);
	memcpy(pBuf, (void *)"ABCD", 5);
	ring_fifo_zerocopy_push_finish(&cut);

	CHECK_FALSE(ring_fifo_is_full(&cut));
	CHECK_FALSE(ring_fifo_is_empty(&cut));

	pBuf = ring_fifo_zerocopy_push_start(&cut);
	memcpy(pBuf, (void *)"ABCD", 5);
	ring_fifo_zerocopy_push_finish(&cut);

	pBuf = ring_fifo_zerocopy_push_start(&cut);
	memcpy(pBuf, (void *)"ABCD", 5);
	ring_fifo_zerocopy_push_finish(&cut);

	CHECK_TRUE(ring_fifo_is_full(&cut));

	pBuf = ring_fifo_peek_at(&cut, 2);
	STRCMP_EQUAL("ABCD", (const char *)pBuf);

	ring_fifo_discard_last_push(&cut);

	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	memcpy(pBuf, (void *)"CBDA", 5);
	ring_fifo_zerocopy_push_finish(&cut);

	pBuf = ring_fifo_peek_at(&cut, 2);
	STRCMP_EQUAL("CBDA", (const char *)pBuf);

	CHECK_TRUE(ring_fifo_is_full(&cut));
	CHECK_FALSE(ring_fifo_is_empty(&cut));

	pBuf = ring_fifo_zerocopy_pop_start(&cut);
	STRCMP_EQUAL("ABCD", (const char *)pBuf);
	ring_fifo_zerocopy_pop_finish(&cut);

	CHECK_FALSE(ring_fifo_is_full(&cut));
	CHECK_FALSE(ring_fifo_is_empty(&cut));

	pBuf = ring_fifo_zerocopy_pop_start(&cut);
	STRCMP_EQUAL("ABCD", (const char *)pBuf);
	ring_fifo_zerocopy_pop_finish(&cut);

	pBuf = ring_fifo_zerocopy_pop_start(&cut);
	STRCMP_EQUAL("CBDA", (const char *)pBuf);
	ring_fifo_zerocopy_pop_finish(&cut);

	CHECK_FALSE(ring_fifo_is_full(&cut));
	CHECK_TRUE(ring_fifo_is_empty(&cut));

	ring_fifo_deinit(&cut);
}


TEST(ring_fifo, nocopymultiplepopstartandfinish)
{
	ring_fifo_t cut;
	BUFFER_PTR pBuf;
	int i, n;

	ring_fifo_init(&cut, 4, 3);

	n = 5;
	while (n--)
	{
		if (ring_fifo_is_full(&cut))
			ring_fifo_discard_last_push(&cut);

		pBuf = ring_fifo_zerocopy_push_start(&cut);
		memcpy(pBuf, (void *)&n, 4);
		ring_fifo_zerocopy_push_finish(&cut);
	}

	i = *(uint32_t *)ring_fifo_peek_at(&cut, 0);
	CHECK_EQUAL(4, i);

	i = *(uint32_t *)ring_fifo_peek_at(&cut, 1);
	CHECK_EQUAL(3, i);

	i = *(uint32_t *)ring_fifo_peek_at(&cut, 2);
	CHECK_EQUAL(0, i);


	i = *(uint32_t *)ring_fifo_zerocopy_pop_start(&cut);
	CHECK_EQUAL(4, i);
	i = *(uint32_t *)ring_fifo_zerocopy_pop_start(&cut);
	CHECK_EQUAL(4, i);
	ring_fifo_zerocopy_pop_finish(&cut);
	ring_fifo_zerocopy_pop_finish(&cut);
	ring_fifo_zerocopy_pop_finish(&cut);

	i = *(uint32_t *)ring_fifo_zerocopy_pop_start(&cut);
	CHECK_EQUAL(3, i);
	ring_fifo_zerocopy_pop_finish(&cut);

	i = *(uint32_t *)ring_fifo_zerocopy_pop_start(&cut);
	CHECK_EQUAL(0, i);
	ring_fifo_zerocopy_pop_finish(&cut);

	ring_fifo_deinit(&cut);
}

TEST(ring_fifo, nocopymultiplepushstartandfinish)
{
	ring_fifo_t cut;
	BUFFER_PTR pBuf;
	int i;

	ring_fifo_init(&cut, 4, 3);

	i = 4;
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	memcpy(pBuf, (void *)&i, 4);
	ring_fifo_zerocopy_push_finish(&cut);

	i = 5;
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	memcpy(pBuf, (void *)&i, 4);
	i = 6;
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	memcpy(pBuf, (void *)&i, 4);
	i = 7;
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	memcpy(pBuf, (void *)&i, 4);
	ring_fifo_zerocopy_push_finish(&cut);
	ring_fifo_zerocopy_push_finish(&cut);
	ring_fifo_zerocopy_push_finish(&cut);
	ring_fifo_zerocopy_push_finish(&cut);


	i = 2;
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	memcpy(pBuf, (void *)&i, 4);

	CHECK_FALSE(ring_fifo_is_full(&cut));

	ring_fifo_zerocopy_push_finish(&cut);

	CHECK_TRUE(ring_fifo_is_full(&cut));

	ring_fifo_discard_last_push(&cut);

	i = 3;
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	CHECK_FALSE(ring_fifo_is_full(&cut));
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	pBuf = ring_fifo_zerocopy_push_start(&cut);
	CHECK_TRUE(pBuf);
	memcpy(pBuf, (void *)&i, 4);
	ring_fifo_zerocopy_push_finish(&cut);

	CHECK_TRUE(ring_fifo_is_full(&cut));

	i = *(uint32_t *)ring_fifo_zerocopy_pop_start(&cut);
	CHECK_EQUAL(4, i);
	ring_fifo_zerocopy_pop_finish(&cut);

	i = *(uint32_t *)ring_fifo_zerocopy_pop_start(&cut);
	CHECK_EQUAL(7, i);
	ring_fifo_zerocopy_pop_finish(&cut);

	i = *(uint32_t *)ring_fifo_zerocopy_pop_start(&cut);
	CHECK_EQUAL(3, i);
	ring_fifo_zerocopy_pop_finish(&cut);

	ring_fifo_deinit(&cut);
}

void * thread_handler(void * arg)
{
	ring_fifo_t * cut = (ring_fifo_t *)arg;
	BUFFER_PTR pBuf;

	uint32_t n = 0x100;
	while (n)
	{
		if (ring_fifo_is_full(cut)) {
			pthread_yield();
			continue;
		}

		n--;

		pBuf = ring_fifo_zerocopy_push_start(cut);
		CHECK_TRUE(pBuf);

		*((uint32_t *)pBuf) = n;
		ring_fifo_zerocopy_push_finish(cut);
	}

	pthread_exit(NULL);
}


TEST(ring_fifo, concurrence)
{
	ring_fifo_t cut;
	BUFFER_PTR pBuf;

	ring_fifo_init(&cut, 4, 1);

	pthread_t thread;
	pthread_create(&thread, NULL, (void *(*)(void *))thread_handler, &cut);

	struct s_ring_fifo_private * icut = (struct s_ring_fifo_private *)&cut;
	icut->rd = 0xFFFFFF0; //Wrap around test
	icut->wr = 0xFFFFFF0;

	uint32_t n = 0x100;
	while (n)
	{
		if (ring_fifo_is_empty(&cut))
		{
			pthread_yield();
			continue;
		}

		n--;

		pBuf = ring_fifo_zerocopy_pop_start(&cut);
		CHECK_TRUE(pBuf);
		CHECK_EQUAL(n, *((uint32_t *)pBuf));
		ring_fifo_zerocopy_pop_finish(&cut);
	}

	pthread_join(thread, NULL);

	ring_fifo_deinit(&cut);
}

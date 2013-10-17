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
#include "chelper/fast_ring_fifo.h"
}

TEST_GROUP(fast_ring_fifo)
{
	void setup()
	{
	}

	void teardown()
	{
	}
};

TEST(fast_ring_fifo, read_write)
{
	fast_ring_fifo_t cut;

	char reference_buffer[] = "abcdefghijklmn";
	char buffer[16];

	fast_ring_fifo_init(&cut, 16);

	int i = 0;

	while (!fast_ring_fifo_full(&cut))
	{
		buffer[fast_ring_fifo_write_index(&cut)] = reference_buffer[i++];
		fast_ring_fifo_write_increment(&cut);
	}

	STRCMP_EQUAL(reference_buffer, buffer);
	CHECK_EQUAL(15, fast_ring_fifo_count(&cut));


	i = 0;

	while(!fast_ring_fifo_empty(&cut))
	{
		CHECK_EQUAL(reference_buffer[i++], buffer[fast_ring_fifo_read_index(&cut)]);
		fast_ring_fifo_read_increment(&cut);
	}

	int n = 3;
	while (n--)
	{
		i = 0;

		while (!fast_ring_fifo_full(&cut))
		{
			buffer[fast_ring_fifo_write_index(&cut)] = reference_buffer[i++];
			fast_ring_fifo_write_increment(&cut);
		}

		CHECK_EQUAL(15, fast_ring_fifo_count(&cut));


		i = 0;

		while(!fast_ring_fifo_empty(&cut))
		{
			CHECK_EQUAL(reference_buffer[i++], buffer[fast_ring_fifo_read_index(&cut)]);
			fast_ring_fifo_read_increment(&cut);
		}
	}
}

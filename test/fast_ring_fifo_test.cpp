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

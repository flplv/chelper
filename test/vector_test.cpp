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
#include "chelper/vector.h"
#include "vector.c"
}

TEST_GROUP(vector)
{
	vector_t cut;
	struct s_vector_private *icut;

	struct s_item{
		int32_t a;
		uint8_t b;
	} clone_vector[10];

	void setup()
	{
		icut = (struct s_vector_private *)&cut;
		vector_init(&cut, sizeof(struct s_item));
	}

	void teardown()
	{
		vector_deinit(&cut);
	}
};

TEST(vector, addAndRead)
{
	for (int var = 0; var < 10; ++var) {
		clone_vector[var].a = var;
		clone_vector[var].b = var%2;
		vector_add(&cut, (BUFFER_PTR_RDOLY)&clone_vector[var]);
		unsigned int n = vector_size(&cut);
		CHECK_EQUAL((unsigned)var+1, n);
	}

	struct s_item *read_item;
	read_item = (struct s_item *)vector_at(&cut, 8);
	CHECK_EQUAL(clone_vector[8].a, read_item->a);
	CHECK_EQUAL(clone_vector[8].b, read_item->b);
}

TEST(vector, addthree)
{
	CHECK_EQUAL(2, icut->buffer_total_slots);
	CHECK_EQUAL(0, icut->used_slots);
	vector_add(&cut, (uint8_t *)&clone_vector[0]);
	CHECK_EQUAL(1, icut->used_slots);
	vector_add(&cut, (uint8_t *)&clone_vector[0]);
	CHECK_EQUAL(2, icut->used_slots);
	vector_add(&cut, (uint8_t *)&clone_vector[0]);
	CHECK_EQUAL(3, icut->used_slots);
	CHECK_EQUAL(4, icut->buffer_total_slots);
}

TEST(vector, instance)
{
	CHECK_EQUAL(2, icut->buffer_total_slots);
}

TEST(vector, addmany_remove)
{
	vector_t vec;
	struct s_vector_private * ivec = ((struct s_vector_private *)vec);

	vector_init(&vec, sizeof(char));

	uint32_t str_size = strlen("abcdefghijklmnopqrstuvxywz") + 1;
	vector_add_many(&vec, (BUFFER_PTR_RDOLY)"abcdefghijklmnopqrstuvxywz", str_size);

	CHECK_EQUAL(str_size, ivec->used_slots);
	STRCMP_EQUAL("abcdefghijklmnopqrstuvxywz", (const char *)vector_data(&vec));

	vector_remove(&vec, 10); /* remove letter k */
	STRCMP_EQUAL("abcdefghijlmnopqrstuvxywz", (const char *)vector_data(&vec));

	vector_clear(&vec);
	CHECK_EQUAL(0, ivec->used_slots);
	CHECK_EQUAL((BUFFER_PTR)0, vector_at(&vec, 0));

	vector_add_many(&vec, (BUFFER_PTR_RDOLY)"abcdefghijklmnopqrstuvxywz", str_size);

	CHECK_EQUAL(str_size, ivec->used_slots);
	STRCMP_EQUAL("abcdefghijklmnopqrstuvxywz", (const char *)vector_data(&vec));

	vector_remove(&vec, 10); /* remove letter k */
	STRCMP_EQUAL("abcdefghijlmnopqrstuvxywz", (const char *)vector_data(&vec));

	vector_deinit(&vec);
}


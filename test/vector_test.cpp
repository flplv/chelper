/*
 * vector_test.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: fanl
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


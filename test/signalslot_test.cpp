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

extern "C" {
#include "chelper/helper_types.h"
#include "chelper/signalslot.h"
#include "chelper/signalslot2.h"
#include "chelper/signalslot_opaque.h"
#include "chelper/signalslot_data.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTest/MemoryLeakDetector.h"

TEST_GROUP(signalslot)
{
	signal_t signal;
	signal2_t signal2;
	signal_opaque_t signal_opaque;
	signal_data_t signal_data;
	slot_t slot;
	slot2_t slot2;
	slot_opaque_t slot_opaque;
	slot_data_t slot_data;

	void setup()
	{
		signal_init(&signal);
		slot_init(&slot);
		signal2_init(&signal2);
		slot2_init(&slot2);
		signal_opaque_init(&signal_opaque);
		slot_opaque_init(&slot_opaque);
		signal_data_init(&signal_data);
		slot_data_init(&slot_data);
		called = false;

	}

	void teardown()
	{
		signal_deinit(&signal);
		slot_deinit(&slot);
		signal2_deinit(&signal2);
		slot2_deinit(&slot2);
		signal_opaque_deinit(&signal_opaque);
		slot_opaque_deinit(&slot_opaque);
		signal_data_deinit(&signal_data);
		slot_data_deinit(&slot_data);
	}

	bool called;
	static void callme(TEST_GROUP_CppUTestGroupsignalslot * self)
	{
		self->called = true;
	}
	static void callme_opaque(TEST_GROUP_CppUTestGroupsignalslot * self, void * data)
	{
		if (data == (void *)self)
			self->called = true;
	}
	static void callme_data(TEST_GROUP_CppUTestGroupsignalslot * self, void * data, size_t size)
	{
		if (data == (void *)self && size == 10)
			self->called = true;
	}
};

TEST(signalslot, action)
{
	CHECK_FALSE(called);

	slot_set(&slot, (slot_func)callme, (slot_arg)this);
	slot_connect(&slot, &signal);
	signal_emit(&signal);

	slot_disconnect(&slot, &signal);
	CHECK_FALSE(signal_is_connected(&signal, &slot));

	CHECK_TRUE(called);
}

TEST(signalslot, action2)
{
	called = false;
	CHECK_FALSE(called);

	slot2_set(&slot2, (slot2_func)callme, (slot_arg)this);
	slot2_connect(&slot2, &signal2);
	signal2_emit(&signal2, 0, 0);

	slot2_disconnect(&slot2, &signal2);
	CHECK_FALSE(signal2_is_connected(&signal2, &slot2));

	CHECK_TRUE(called);
}

TEST(signalslot, action_opaque)
{
	called = false;
	CHECK_FALSE(called);

	slot_opaque_set(&slot_opaque, (slot_opaque_func)callme_opaque, (slot_arg)this);
	slot_opaque_connect(&slot_opaque, &signal_opaque);
	signal_opaque_emit(&signal_opaque, (void *)this);

	slot_opaque_disconnect(&slot_opaque, &signal_opaque);
	CHECK_FALSE(signal_opaque_is_connected(&signal_opaque, &slot_opaque));

	CHECK_TRUE(called);
}

TEST(signalslot, action_data)
{
	called = false;
	CHECK_FALSE(called);

	slot_data_set(&slot_data, (slot_data_func)callme_data, (slot_arg)this);
	slot_data_connect(&slot_data, &signal_data);
	signal_data_emit(&signal_data, (void *)this, 10);

	slot_data_disconnect(&slot_data, &signal_data);
	CHECK_FALSE(signal_data_is_connected(&signal_data, &slot_data));

	CHECK_TRUE(called);
}

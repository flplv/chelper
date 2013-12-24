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
#include "chelper/eventsystem.h"
#include "chelper/signalslot_opaque.h"
}

TEST_GROUP(eventsystem)
{
	event_loop_t cut;
	int called;

	void setup()
	{
		event_loop_init(&cut);
		called = 0;
	}

	void teardown()
	{
		event_loop_deinit(&cut);
	}

	static void callback (TEST_GROUP_CppUTestGroupeventsystem * self, void * data, size_t size)
	{
		self->called ++;
	}
};


TEST(eventsystem, loop)
{
	event_handler_t handle;
	slot_opaque_t slot;
	int tout = 10;

	slot_opaque_init(&slot);
	slot_opaque_set(&slot, (slot_opaque_func)TEST_GROUP_CppUTestGroupeventsystem::callback, this);

	event_handler_init(&handle);
	slot_opaque_connect(&slot, event_handler_signal(&handle));

	event_loop_queue_event(&cut, &handle);
	event_loop_queue_event(&cut, &handle);
	event_loop_queue_event(&cut, &handle);
	event_loop_queue_event(&cut, &handle);

	while (event_loop_has_pending_events(&cut) && tout--)
		event_loop_periodic(&cut);

	CHECK_EQUAL(10-4, tout);
	CHECK_EQUAL(4, called);

	slot_opaque_deinit(&slot);
	event_handler_deinit(&handle);
}

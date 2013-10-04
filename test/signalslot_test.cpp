
extern "C" {
#include "chelper/helper_types.h"
#include "chelper/signalslot.h"
#include "chelper/signalslot2.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTest/MemoryLeakDetector.h"

TEST_GROUP(signalslot)
{
	signal_t signal;
	signal2_t signal2;
	slot_t slot;
	slot2_t slot2;

	void setup()
	{
		signal_init(&signal);
		slot_init(&slot);
		signal2_init(&signal2);
		slot2_init(&slot2);
		called = false;

	}

	void teardown()
	{
		signal_deinit(&signal);
		slot_deinit(&slot);
		signal2_deinit(&signal2);
		slot2_deinit(&slot2);
//		DISABLE_INTERCEPTION;
	}

	bool called;
	static void callme(TEST_GROUP_CppUTestGroupsignalslot * self)
	{
		self->called = true;
	}
};

TEST(signalslot, action)
{
	CHECK_FALSE(called);

	slot_set(&slot, (slot_func)callme, (slot_arg)this);
	slot_connect(&slot, &signal);
	signal_emit(&signal);

	CHECK_TRUE(called);
}

TEST(signalslot, action2)
{
	called = false;
	CHECK_FALSE(called);

	slot2_set(&slot2, (slot2_func)callme, (slot_arg)this);
	slot2_connect(&slot2, &signal2);
	signal2_emit(&signal2, 0, 0);

	CHECK_TRUE(called);
}

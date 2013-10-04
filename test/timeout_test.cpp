
extern "C" {
#include "chelper/timeout.h"
#include <stdint.h>
}

#include "CppUTest/TestHarness.h"
#include "CppUTest/MemoryLeakDetector.h"

TEST_GROUP(timeout)
{
	void setup()
	{
	}

	void teardown()
	{
	}
};

TEST(timeout, test)
{
	timeout_t tout = timeout_init_cpy();

	uint32_t now = time_now();

	while (!timeout_check(&tout, 100));

	CHECK_TRUE( (now + 100) <= time_now() );
}

TEST(timeout, periodically_test)
{
	timeout_t tout = timeout_init_cpy();

	uint32_t now = time_now();

	while (!timeout_check_and_reinit(&tout, 100));
	CHECK_TRUE( (now + 100) <= time_now() );

	while (!timeout_check_and_reinit(&tout, 100));
	CHECK_TRUE( (now + 200) <= time_now() );

	while (!timeout_check_and_reinit(&tout, 100));
	CHECK_TRUE( (now + 300) <= time_now() );

	while (!timeout_check_and_reinit(&tout, 100));
	CHECK_TRUE( (now + 400) <= time_now() );
}

TEST(timeout, sleep_test)
{
	timeout_t tout = timeout_init_cpy();
	uint32_t now = time_now();
	timeout_sleep(&tout, 100);
	CHECK_TRUE( (now + 100*0.8) <= time_now() );
}

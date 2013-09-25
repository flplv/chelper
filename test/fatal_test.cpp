
extern "C" {
#include "chelper/helper_types.h"
#include "chelper/fatal.h"
}

#include "mocks/terminal_intercepter.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/MemoryLeakDetector.h"

TEST_GROUP(fatal)
{
	void setup()
	{
		fatal_terminal_output =  output_intercepter;
	}

	void teardown()
	{
		fatal_terminal_output =  _stdout_output_impl;
	}
};

TEST(fatal, test)
{
	fatal("Fim.");
	STRCMP_CONTAINS("Fatal", intercepted_output[1]);
	STRCMP_CONTAINS("Fim.", intercepted_output[0]);
}

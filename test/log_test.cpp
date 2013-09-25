extern "C" {

#include "chelper/log.h"
}
#include "mocks/terminal_intercepter.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/MemoryLeakDetector.h"

TEST_GROUP(log)
{
	my_log_t cut;
	struct s_my_log_private * icut;

	void setup()
	{
		icut = (struct s_my_log_private *)&cut;

		my_log_init(&cut, "TEST", MESSAGE);
		icut->stream_output = output_intercepter;
	}

	void teardown()
	{
		my_log_deinit(&cut);
	}
};

TEST(log, instance)
{
	my_log(MESSAGE, __FILE__, __LINE__, "message", &cut);
	STRCMP_CONTAINS("message", intercepted_output[3]);
	my_log(WARNING, __FILE__, __LINE__, "warning", &cut);
	STRCMP_CONTAINS("warning", intercepted_output[3]);
	my_log(ERROR, __FILE__, __LINE__, "error", &cut);
	STRCMP_CONTAINS("error", intercepted_output[3]);
}

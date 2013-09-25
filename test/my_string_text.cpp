#include "mocks/terminal_intercepter.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/MemoryLeakDetector.h"

extern "C" {

#include "chelper/my_string.h"
#include "my_string.c"
}

TEST_GROUP(my_string)
{
	my_string_t cut;
	void setup()
	{
		my_string_init(&cut);
	}

	void teardown()
	{
		my_string_deinit(&cut);
	}
};

TEST(my_string, instance)
{
	STRCMP_EQUAL("", my_string_get(&cut));
	my_string_set(&cut, "tweedledee ");
	STRCMP_EQUAL("tweedledee ", my_string_get(&cut));

	my_string_set(&cut, "tweedledee tweedledee");
	STRCMP_EQUAL("tweedledee tweedledee", my_string_get(&cut));

	my_string_set(&cut, "tweedledee tweedledee tweedledee tweedledee tweedledee tweedledee tweedledee tweedledee");
	STRCMP_EQUAL("tweedledee tweedledee tweedledee tweedledee tweedledee tweedledee tweedledee tweedledee", my_string_get(&cut));
}

/*
 * log_test.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: fanl
 */
#include "CppUTest/TestHarness.h"
#include "CppUTest/MemoryLeakDetector.h"

#define DEBUG

extern "C" {
#include "chelper/log.h"
#include "log.c"
}

char output[256];

static int test_stdout(const char * format,  va_list va)
{
	return vsprintf(output, format, va);
}

TEST_GROUP(log)
{
	void setup()
	{
		sys_stdout_impl = test_stdout;
	}

	void teardown()
	{
	}
};

TEST(log, info)
{
	set_sys_dbg_lvl(INFO);
	MSG_INFO("Testando a macro MSG_INFO", "log_test");
	STRCMP_CONTAINS("Testando a macro MSG_INFO", output);
	STRCMP_CONTAINS("log_test", output);
	STRCMP_CONTAINS("info", output);

	MSG_INFO("Testando a macro MSG_INFO com parametro %s", "log_test", "STRING");
	STRCMP_CONTAINS("Testando a macro MSG_INFO com parametro", output);
	STRCMP_CONTAINS("STRING", output);
	STRCMP_CONTAINS("log_test", output);
	STRCMP_CONTAINS("info", output);
}

TEST(log, warning)
{
	MSG_WARNING("Testando a macro MSG_WARNING", "log_test");
	STRCMP_CONTAINS("Testando a macro MSG_WARNING", output);
	STRCMP_CONTAINS("log_test", output);
	STRCMP_CONTAINS("warning", output);

	MSG_WARNING("Testando a macro MSG_WARNING com parametro %s", "log_test", "STRING");
	STRCMP_CONTAINS("Testando a macro MSG_WARNING com parametro", output);
	STRCMP_CONTAINS("STRING", output);
	STRCMP_CONTAINS("log_test", output);
	STRCMP_CONTAINS("warning", output);
}

TEST(log, critical)
{
	MSG_ERROR("Testando a macro MSG_ERROR", "log_test");
	STRCMP_CONTAINS("Testando a macro MSG_ERROR", output);
	STRCMP_CONTAINS("log_test", output);
	STRCMP_CONTAINS("error", output);

	MSG_ERROR("Testando a macro MSG_ERROR com parametro %s", "log_test", "STRING");
	STRCMP_CONTAINS("Testando a macro MSG_ERROR com parametro", output);
	STRCMP_CONTAINS("STRING", output);
	STRCMP_CONTAINS("log_test", output);
	STRCMP_CONTAINS("error", output);

	MSG_ERROR("Testando a macro MSG_ERROR com os parametros %s %s", "log_test", "STRING1", "STRING2");
	STRCMP_CONTAINS("Testando a macro MSG_ERROR com os parametros", output);
	STRCMP_CONTAINS("STRING1", output);
	STRCMP_CONTAINS("STRING2", output);
	STRCMP_CONTAINS("log_test", output);
	STRCMP_CONTAINS("error", output);
}

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

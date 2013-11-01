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

TEST_GROUP(log)
{
	void setup()
	{
		sys_set_interception(TRUE);
		enable_debug();
	}

	void teardown()
	{
		sys_set_interception(FALSE);
		disable_debug();
	}
};

TEST(log, info)
{
	set_sys_dbg_lvl(INFO);
	MSG_INFO("Testando a macro MSG_INFO", "log_test");
	STRCMP_CONTAINS("Testando a macro MSG_INFO", sys_get_intercepted_message());
	STRCMP_CONTAINS("log_test", sys_get_intercepted_message());
	STRCMP_CONTAINS("info", sys_get_intercepted_message());

	MSG_INFO("Testando a macro MSG_INFO com parametro %s", "log_test", "STRING");
	STRCMP_CONTAINS("Testando a macro MSG_INFO com parametro", sys_get_intercepted_message());
	STRCMP_CONTAINS("STRING", sys_get_intercepted_message());
	STRCMP_CONTAINS("log_test", sys_get_intercepted_message());
	STRCMP_CONTAINS("info", sys_get_intercepted_message());
}

TEST(log, warning)
{
	MSG_WARNING("Testando a macro MSG_WARNING", "log_test");
	STRCMP_CONTAINS("Testando a macro MSG_WARNING", sys_get_intercepted_message());
	STRCMP_CONTAINS("log_test", sys_get_intercepted_message());
	STRCMP_CONTAINS("warning", sys_get_intercepted_message());

	MSG_WARNING("Testando a macro MSG_WARNING com parametro %s", "log_test", "STRING");
	STRCMP_CONTAINS("Testando a macro MSG_WARNING com parametro", sys_get_intercepted_message());
	STRCMP_CONTAINS("STRING", sys_get_intercepted_message());
	STRCMP_CONTAINS("log_test", sys_get_intercepted_message());
	STRCMP_CONTAINS("warning", sys_get_intercepted_message());
}

TEST(log, critical)
{
	MSG_ERROR("Testando a macro MSG_ERROR", "log_test");
	STRCMP_CONTAINS("Testando a macro MSG_ERROR", sys_get_intercepted_message());
	STRCMP_CONTAINS("log_test", sys_get_intercepted_message());
	STRCMP_CONTAINS("error", sys_get_intercepted_message());

	MSG_ERROR("Testando a macro MSG_ERROR com parametro %s", "log_test", "STRING");
	STRCMP_CONTAINS("Testando a macro MSG_ERROR com parametro", sys_get_intercepted_message());
	STRCMP_CONTAINS("STRING", sys_get_intercepted_message());
	STRCMP_CONTAINS("log_test", sys_get_intercepted_message());
	STRCMP_CONTAINS("error", sys_get_intercepted_message());

	MSG_ERROR("Testando a macro MSG_ERROR com os parametros %s %s", "log_test", "STRING1", "STRING2");
	STRCMP_CONTAINS("Testando a macro MSG_ERROR com os parametros", sys_get_intercepted_message());
	STRCMP_CONTAINS("STRING1", sys_get_intercepted_message());
	STRCMP_CONTAINS("STRING2", sys_get_intercepted_message());
	STRCMP_CONTAINS("log_test", sys_get_intercepted_message());
	STRCMP_CONTAINS("error", sys_get_intercepted_message());
}

TEST(log, no_info)
{
	MSG_ERROR("Testando a macro MSG_ERROR","");
	set_sys_dbg_lvl(WARNING);
	MSG_INFO("Testando a macro MSG_INFO", "log_test");
	STRCMP_CONTAINS("Testando a macro MSG_ERROR", sys_get_intercepted_message());
}

TEST(log, no_debug)
{
	MSG_ERROR("Testando a macro MSG_ERROR","");
	set_sys_dbg_lvl(WARNING);
	disable_debug();
	MSG_WARNING("Testando a macro MSG_INFO", "log_test");
	STRCMP_CONTAINS("Testando a macro MSG_ERROR", sys_get_intercepted_message());
}

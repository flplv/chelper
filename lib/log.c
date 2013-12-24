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

#include "chelper/number.h"

#include "chelper/log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static int run_time_lvl = WARNING;
static bool debug = false;

int get_sys_dbg_lvl() {
	return run_time_lvl;
}

void set_sys_dbg_lvl(int level) {
	run_time_lvl = level;
}

void enable_debug() {
	debug = true;
}

void disable_debug() {
	debug = false;
}

bool get_debug_state() {
	return debug;
}

static int (*sys_stdout_impl)(const char *__restrict __format, _G_va_list __arg) = vprintf;

int sys_stdout(const char* format, ...) {
	va_list va;
	va_start(va, format);
	int i = sys_stdout_impl(format, va);
	va_end(va);
	return i;
}

#ifdef SYSTEM_UNIT_TEST

static char intercepted_output[512];

static int intercepted_stdout(const char * format,  va_list va)
{
	return vsprintf(intercepted_output, format, va);
}

void sys_set_interception(bool enabled)
{
	if (enabled)
		sys_stdout_impl = intercepted_stdout;
	else
		sys_stdout_impl = vprintf;
}

char * sys_get_intercepted_message()
{
	return intercepted_output;
}

#endif

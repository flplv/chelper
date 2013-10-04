#include "chelper/number.h"

#include "chelper/log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static int run_time_lvl = WARNING;

int get_sys_dbg_lvl() {
	return run_time_lvl;
}

void set_sys_dbg_lvl(int level) {
	run_time_lvl = level;
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

void sys_set_interception(BOOL enabled)
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

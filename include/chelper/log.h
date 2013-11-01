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

#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <syslog.h>
#include <chelper/helper_types.h>

enum dbg_log_lvl {
	INFO,
	WARNING,
	CRITICAL
};

int sys_stdout(const char* format, ...);
void set_sys_dbg_lvl(int level);
int get_sys_dbg_lvl();

#if defined(DEBUG)
	#define MSG_INFO(a, b, ...)			\
		do {				\
			if (get_sys_dbg_lvl() == INFO) {			\
				sys_stdout("\n%s:%d:info: "b":"a"\r\n", __FILE__, __LINE__, ##__VA_ARGS__);	\
			}	\
		} while(0)
	#define MSG_WARNING(a, b, ...)		sys_stdout("\n%s:%d:warning: "b":"a"\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
	#define MSG_ERROR(a, b, ...)		sys_stdout("\n%s:%d:error: "b":"a"\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
	#define MSG_INFO(a, b,...)			syslog(LOG_INFO, a, ##__VA_ARGS__)
	#define MSG_WARNING(a, b, ...)		syslog(LOG_WARNING, a, ##__VA_ARGS__)
	#define MSG_ERROR(a, b, ...)		syslog(LOG_ERR, a, ##__VA_ARGS__)
#endif

#ifdef SYSTEM_UNIT_TEST

void sys_set_interception(BOOL enabled);
char * sys_get_intercepted_message();

#endif

#endif /* LOG_H_ */


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

#ifdef __cplusplus 
extern "C" {
#endif

int sys_stdout(const char* format, ...);
void set_sys_dbg_lvl(int level);
int get_sys_dbg_lvl();
void enable_debug();
void disable_debug();
BOOL get_debug_state();

#ifdef SYSTEM_UNIT_TEST

void sys_set_interception(BOOL enabled);
char * sys_get_intercepted_message();

#endif

#ifdef __cplusplus 
}
#endif

#define MSG_INFO(msg, module_name, ...)			\
	do {				\
		if (get_debug_state()) {			\
			if (get_sys_dbg_lvl() == INFO)	\
				sys_stdout("\n%s:%d:info: "module_name": "msg"\r\n", __FILE__, __LINE__, ##__VA_ARGS__);	\
		} else {	\
			syslog(LOG_INFO, msg, ##__VA_ARGS__);	\
		}	\
	} while(0)
#define MSG_WARNING(msg, module_name, ...)		\
	do {				\
		if (get_debug_state()) {	\
			sys_stdout("\n%s:%d:warning: "module_name": "msg"\r\n", __FILE__, __LINE__, ##__VA_ARGS__);	\
		} else {	\
			syslog(LOG_WARNING, msg, ##__VA_ARGS__);	\
		}	\
	} while(0)
#define MSG_ERROR(msg, module_name, ...)		\
		do {	\
			if (get_debug_state()) {	\
				sys_stdout("\n%s:%d:error: "module_name": "msg"\r\n", __FILE__, __LINE__, ##__VA_ARGS__);	\
			} else {	\
				syslog(LOG_ERR, msg, ##__VA_ARGS__);	\
			}	\
		} while(0)

#endif /* LOG_H_ */


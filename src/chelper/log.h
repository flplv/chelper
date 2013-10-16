/*
 * debug.h
 *
 *  Created on: Dec 24, 2012
 *      Author: fanl
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


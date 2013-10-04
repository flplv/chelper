/*
 * fatal.c
 *
 *  Created on: Jan 20, 2013
 *      Author: fanl
 */

#include "chelper/log.h"

void fatal(const char * str)
{
	sys_stdout("\nFatal error: ");
	sys_stdout(str);
#if !defined SYSTEM_UNIT_TEST
	sys_stdout("\Execution is halted.");
	while(1);
#endif
}

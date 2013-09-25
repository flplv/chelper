/*
 * fatal.c
 *
 *  Created on: Jan 20, 2013
 *      Author: fanl
 */

#include "chelper/log.h"

void fatal(const char * str)
{
	fatal_terminal_output("\nFatal error: ");
	fatal_terminal_output(str);
#if !defined SYSTEM_UNIT_TEST
	fatal_terminal_output("\Execution is halted.");
	while(1);
#endif
}

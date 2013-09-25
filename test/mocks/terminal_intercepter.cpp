/*
 * logcapturer.cpp
 *
 *  Created on: Jan 19, 2013
 *      Author: fanl
 */

#include <string.h>
#include <stdio.h>

const char *intercepted_output[10];

int32_t output_intercepter(const char * str)
{
	int32_t i = 9;

	while (i>=1)
	{
		intercepted_output[i] = intercepted_output[i-1];
		i--;
	}
	intercepted_output[i] = str;

	return strlen(str);
}

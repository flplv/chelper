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

#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "chelper/number.h"

bool charactere_is_null(char c)
{
	if (c != '\0')
		return false;

	return true;
}

bool charactere_is_hex(char c)
{
	c = toupper(c);
	if (c > 'F')
		return false;
	if (c < '0')
		return false;
	if (c > '9' && c < 'A')
		return false;

	return true;
}

bool charactere_is_space(char c)
{
	c = toupper(c);
	if (c == ' ')
		return true;
	if (c == '\t')
		return true;
	if (c == '\n')
		return true;

	return false;
}

bool charactere_is_math_sig(char c)
{
	c = toupper(c);
	if (c == '+')
		return true;
	if (c == '-')
		return true;

	return false;
}

uint8_t charactere_hex_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return c-'0';

	c = toupper(c);
	if (c >= 'A' && c<= 'F')
		return c-'A'+10;

	return 0;
}

int32_t string_hex_to_int(const char* str)
{
	uint32_t i;
	char c;
	uint32_t size = strlen(str);
	bool started = false;
	int8_t signal = 1;
	uint32_t final_value = 0;

	for (i = 0; i < size; i++)
	{
		c = str[i];

		if (charactere_is_null(c))
		{
			return final_value*signal;

		}
		else if (charactere_is_space(c))
		{
			if (!started)
				continue;
			else
				return final_value*signal;
		}
		else if (charactere_is_math_sig(c))
		{
			if (!started)
			{
				started = true;
				if (c == '-')
					signal = -1;
			}
			else
				return final_value*signal;
		}
		else if (charactere_is_hex(c))
		{
			started = true;
			final_value *= 16;
			final_value += charactere_hex_to_int(c);
		}
	}

	return final_value*signal;
}

void int_to_string(int32_t number, char * target, size_t size)
{
	int32_t i = size -1;
	uint32_t j;

	target[i] = '\0';

	while(number && i--)
	{
		target[i] = number%10 + '0';
		number = number/10;
	}

	if (i<=0)
		return;

	for (j=0; j<(size-i); j++)
	{
		target[j] = target[j+i];
	}
}

bool charactere_is_printable(char c)
{
	if (c < ' ')
		return false;

	if (c > '~')
		return false;

	return true;
}


#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include "chelper/number.h"

BOOL charactere_is_null(char c)
{
	if (c != '\0')
		return FALSE;

	return TRUE;
}

BOOL charactere_is_hex(char c)
{
	c = toupper(c);
	if (c > 'F')
		return FALSE;
	if (c < '0')
		return FALSE;
	if (c > '9' && c < 'A')
		return FALSE;

	return TRUE;
}

BOOL charactere_is_space(char c)
{
	c = toupper(c);
	if (c == ' ')
		return TRUE;
	if (c == '\t')
		return TRUE;
	if (c == '\n')
		return TRUE;

	return FALSE;
}

BOOL charactere_is_math_sig(char c)
{
	c = toupper(c);
	if (c == '+')
		return TRUE;
	if (c == '-')
		return TRUE;

	return FALSE;
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
	BOOL started = FALSE;
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
				started = TRUE;
				if (c == '-')
					signal = -1;
			}
			else
				return final_value*signal;
		}
		else if (charactere_is_hex(c))
		{
			started = TRUE;
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

BOOL charactere_is_printable(char c)
{
	if (c < ' ')
		return FALSE;

	if (c > '~')
		return FALSE;

	return TRUE;
}

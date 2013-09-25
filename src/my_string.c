/*
 * my_string.c
 *
 *  Created on: Feb 27, 2013
 *      Author: fanl
 */
#include "chelper/my_string.h"
#include "chelper/checks.h"
#include "chelper/signalslot.h"

#define SIGNATURE_MY_STRING (ADDRESS_TO_SIGNATURE_CAST)&my_string_create

static void _expand(struct s_my_string *obj, size_t size)
{
	if (!obj->str_data)
	{
		obj->str_data = (char *)calloc(size, sizeof(char));
	}
	else
	{
		obj->str_data = (char *)realloc(obj->str_data, size * sizeof(char));
	}

	obj->mem_size = size;
}

static void _clear(struct s_my_string * obj)
{
	if (obj->str_data)
		free (obj->str_data);

	obj->str_data = (char*)calloc(1, sizeof(char));
	obj->str_len = 0;
	obj->mem_size = 1;
}

static void _set(struct s_my_string * obj, const char *str)
{
	char *my_str = obj->str_data;
	size_t len = 0;

	while(*str)
	{
		*my_str++ = *str++;
		len++;
	}
	*my_str = '\0';
	obj->str_len = len;
}


void my_string_init(my_string_t * cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK(obj, "my_string");

	obj->str_data = (char*)calloc(1, sizeof(char));
	obj->str_len = 0;
	obj->mem_size = 1;

	signal_init(&obj->update_signal);
}

void my_string_deinit(my_string_t *cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK(obj, "my_string");

	if (obj->str_data)
		free(obj->str_data);

	signal_deinit(&obj->update_signal);
}

void my_string_clear(my_string_t * cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK(obj, "my_string");

	_clear(obj);
}

void my_string_set(my_string_t *cobj, const char* str)
{
	size_t len;

	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK(obj, "my_string");

	len = my_strlen(str);

	if ((len+1) > obj->mem_size)
	{
		_clear(obj);
		_expand(obj, len*2);
	}

	_set(obj, str);

	signal_emit(&obj->update_signal);
}

const char* my_string_get(my_string_t* cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK_RETURN(obj, "my_string", NULL);

	return obj->str_data;
}

size_t my_string_len(my_string_t* cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK_RETURN(obj, "my_string", 0);

	return obj->str_len;
}

signal_t * my_string_get_update_signal(my_string_t * cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK_RETURN(obj, "my_string", NULL);

	return &obj->update_signal;
}

size_t my_strlen(const char* str)
{
	size_t len = 0;
	while (*str++)
		len++;
	return len;
}


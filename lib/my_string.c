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

#include <chelper/my_string.h>
#include <chelper/vector.h>
#include <chelper/checks.h>
#include <chelper/signalslot.h>

#define SIGNATURE_MY_STRING (ADDRESS_TO_SIGNATURE_CAST)&my_string_create


void my_string_init(my_string_t * cobj)
{
	struct s_my_string_private* obj = (struct s_my_string_private *)cobj;
	PTR_CHECK(obj, "my_string");

	vector_init(&obj->str_data, sizeof(char));
	signal_init(&obj->update_signal);
}

void my_string_deinit(my_string_t *cobj)
{
	struct s_my_string_private* obj = (struct s_my_string_private *)cobj;
	PTR_CHECK(obj, "my_string");

	signal_deinit(&obj->update_signal);
	vector_deinit(&obj->str_data);
}

void my_string_clear(my_string_t * cobj)
{
	struct s_my_string_private* obj = (struct s_my_string_private *)cobj;
	PTR_CHECK(obj, "my_string");

	vector_clear(&obj->str_data);
}

void my_string_set(my_string_t *cobj, const char* str)
{
	size_t len;

	struct s_my_string_private* obj = (struct s_my_string_private *)cobj;
	PTR_CHECK(obj, "my_string");

	len = my_strlen(str);

	vector_clear(&obj->str_data);
	vector_add_many(&obj->str_data, (BUFFER_PTR_RDOLY)str, len + 1);

	signal_emit(&obj->update_signal);
}

const char* my_string_data(my_string_t* cobj)
{
	struct s_my_string_private* obj = (struct s_my_string_private *)cobj;
	PTR_CHECK_RETURN(obj, "my_string", NULL);

	return (const char *)vector_data(&obj->str_data);
}

size_t my_string_len(my_string_t* cobj)
{
	struct s_my_string_private* obj = (struct s_my_string_private *)cobj;
	PTR_CHECK_RETURN(obj, "my_string", 0);

	return vector_size(&obj->str_data) - 1;
}

signal_t * my_string_update_signal(my_string_t * cobj)
{
	struct s_my_string_private* obj = (struct s_my_string_private *)cobj;
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


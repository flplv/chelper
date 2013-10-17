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

#include "chelper/helper_types.h"
#include "chelper/vector.h"
#include "chelper/checks.h"
#include "chelper/log.h"
#include <string.h>

static BUFFER_PTR _at(struct s_vector_private * obj, size_t pos)
{
	if (obj->used_slots == 0)
		return NULL;

	if (pos >= obj->used_slots)
		return NULL;

	return obj->buffer + obj->item_size * pos;
}

static void _add_one(struct s_vector_private * obj, BUFFER_PTR_RDOLY item)
{
	if (obj->used_slots == obj->buffer_total_slots)
	{
		obj->buffer = (uint8_t *)realloc(obj->buffer, obj->buffer_total_slots * 2 * obj->item_size);
		MEMORY_ALLOC_CHECK(obj->buffer);
		obj->buffer_total_slots *= 2;
	}

	memcpy( obj->buffer + (obj->used_slots * obj->item_size),
			item,
			obj->item_size );

	obj->used_slots++;
}

void vector_init(vector_t * cobj, size_t item_size)
{
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK(obj, "vector");

	obj->item_size = item_size;

	obj->buffer = (uint8_t *)calloc(2, obj->item_size);
	MEMORY_ALLOC_CHECK(obj->buffer);
	obj->buffer_total_slots = 2;

	obj->used_slots = 0;
}

void vector_deinit(vector_t *cobj)
{
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK(obj, "vector");

	if (obj->buffer) {
		free(obj->buffer);
		obj->buffer = NULL;
	}
}

void vector_clear(vector_t *cobj)
{
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK(obj, "vector");

	obj->used_slots = 0;
}

void vector_add(vector_t *cobj, BUFFER_PTR_RDOLY item)
{
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK(obj, "vector");

	_add_one(obj, item);
}

void vector_add_many(vector_t *cobj, BUFFER_PTR_RDOLY item, size_t count)
{
	size_t i;
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK(obj, "vector");

	for (i=0; i<count; i++)
		_add_one(obj, item + i * obj->item_size);
}

void vector_remove(vector_t *cobj, size_t pos)
{
	size_t i;
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK(obj, "vector");

	if (pos >= obj->used_slots)
		return;

	for (i=pos; i < (obj->used_slots - 1); i++)
	{
		BUFFER_PTR to = _at(obj, i);
		BUFFER_PTR_RDOLY from = _at(obj, i + 1);

		if (!to || !from)
			continue;

		memcpy(to, from, obj->item_size);
	}

	memset(_at(obj, obj->used_slots - 1), 0x00, obj->item_size);

	obj->used_slots --;
}

size_t vector_size(vector_t* cobj)
{
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK_RETURN(obj, "vector", 0);

	return obj->used_slots;
}

BUFFER_PTR vector_at(vector_t *cobj, size_t pos)
{
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK_RETURN(obj, "vector", NULL);

	return _at(obj, pos);
}

const void * vector_data(vector_t *cobj)
{
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK_RETURN(obj, "vector", NULL);

	return obj->buffer;
}

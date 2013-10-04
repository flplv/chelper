/*
 * vector.c
 *
 *  Created on: Feb 21, 2013
 *      Author: fanl
 */

#include "chelper/helper_types.h"
#include "chelper/vector.h"
#include "chelper/checks.h"
#include "chelper/log.h"
#include <string.h>


void vector_init(vector_t * cobj, uint32_t item_size)
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

void vector_add(vector_t *cobj, BUFFER_PTR_RDOLY item)
{
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK(obj, "vector");

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

uint32_t vector_size(vector_t* cobj)
{
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK_RETURN(obj, "vector", 0);

	return obj->used_slots;
}

BUFFER_PTR vector_at(vector_t *cobj, uint32_t pos)
{
	struct s_vector_private * obj = (struct s_vector_private *)cobj;
	PTR_CHECK_RETURN(obj, "vector", NULL);

	if (obj->used_slots == 0)
		return NULL;

	if (pos >= obj->used_slots)
		return NULL;

	return obj->buffer + obj->item_size * pos;
}

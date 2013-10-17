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
#include "chelper/ring_fifo.h"
#include "chelper/checks.h"
#include <string.h>

static BOOL _full(struct s_ring_fifo_private * obj)
{
	return obj->full;
}

static BOOL _empty(struct s_ring_fifo_private * obj)
{
	return (obj->rd == obj->wr) && !obj->full;
}

static BUFFER_PTR _rd_ptr(struct s_ring_fifo_private * obj)
{
	uint32_t offset;

	if (_empty(obj))
		return NULL;

	offset = (obj->rd % obj->num_fifo_slots) * obj->element_size;

	return obj->buffer + offset;
}

static BUFFER_PTR _wr_ptr(struct s_ring_fifo_private * obj)
{
	uint32_t offset;

	if (_full(obj))
		return NULL;

	offset = (obj->wr % obj->num_fifo_slots) * obj->element_size;

	return obj->buffer + offset;
}

void ring_fifo_init(ring_fifo_t * cobj, size_t element_size, int32_t num_of_elements)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK(obj, "ring_fifo");

	obj->client_buffer = NULL;
	obj->own_buffer = (BUFFER_PTR)malloc(num_of_elements * element_size);
	obj->buffer = obj->own_buffer;
	obj->element_size = element_size;
	obj->num_fifo_slots = num_of_elements;
	obj->rd = 0;
	obj->wr = 0;
	obj->full = FALSE;
}

void ring_fifo_init_buffer(ring_fifo_t * cobj, BUFFER_PTR buffer, size_t buffer_size, size_t element_size)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK(obj, "ring_fifo");

	obj->own_buffer = NULL;
	obj->client_buffer = buffer;
	obj->buffer = obj->client_buffer;
	obj->element_size = element_size;
	obj->num_fifo_slots = buffer_size / element_size;
	obj->rd = 0;
	obj->wr = 0;
	obj->full = TRUE;
}

void ring_fifo_deinit(ring_fifo_t *cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK(obj, "ring_fifo");

	obj->buffer = NULL;
	obj->client_buffer = NULL;

	if (obj->own_buffer) {
		free (obj->own_buffer);
		obj->own_buffer = NULL;
	}
}

BOOL ring_fifo_is_full(ring_fifo_t *cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", FALSE);

	return _full(obj);
}

BOOL ring_fifo_is_empty(ring_fifo_t *cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", TRUE);

	return _empty(obj);
}


BUFFER_PTR ring_fifo_peek(ring_fifo_t *cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", NULL);

	return _rd_ptr(obj);
}

BOOL ring_fifo_pop(ring_fifo_t *cobj, BUFFER_PTR to)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", FALSE);

	if (_empty(obj))
		return FALSE;

	if (to)
		memcpy(to, _rd_ptr(obj), obj->element_size);

	obj->rd++;

	if (obj->rd == obj->wr)
		obj->full = FALSE;

	return TRUE;
}

BOOL ring_fifo_push(ring_fifo_t *cobj, BUFFER_PTR_RDOLY copy_src)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", FALSE);

	if (_full(obj))
		return FALSE;

	if (!copy_src)
		return FALSE;

	memcpy(_wr_ptr(obj), copy_src, obj->element_size);

	obj->wr++;

	if (obj->wr%obj->num_fifo_slots == obj->rd%obj->num_fifo_slots)
		obj->full = TRUE;

	return TRUE;
}


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

static bool _empty(struct s_ring_fifo_private * obj)
{
	return (obj->rd == obj->wr);
}

static bool _full(struct s_ring_fifo_private * obj)
{
	if (_empty(obj))
		return false;

	return ( ((obj->wr - obj->rd) >= obj->num_fifo_slots) ? true : false);
}

static BUFFER_PTR _rd_ptr(struct s_ring_fifo_private * obj)
{
	uint32_t offset;

	if (_empty(obj))
		return NULL;

	offset = (obj->rd % obj->num_fifo_slots) * obj->element_size;

	return obj->buffer + offset;
}

static bool _discard_last_wr(struct s_ring_fifo_private * obj)
{
	if (obj->nocp_push_started)
		return false;

	if (_empty(obj))
		return false;

	obj->wr--;

	return true;
}

static BUFFER_PTR _wr_ptr(struct s_ring_fifo_private * obj)
{
	uint32_t offset;

	offset = (obj->wr % obj->num_fifo_slots) * obj->element_size;

	return obj->buffer + offset;
}

#ifdef CHELPER_ALLOW_MALLOC
void ring_fifo_init(ring_fifo_t * cobj, size_t element_size, int32_t num_of_elements)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK(obj, "ring_fifo");

	obj->own_buffer = (BUFFER_PTR)malloc(element_size * num_of_elements);
	obj->num_fifo_slots = num_of_elements;
	obj->client_buffer = NULL;
	obj->buffer = obj->own_buffer;
	obj->element_size = element_size;
	obj->rd = 0;
	obj->wr = 0;
	obj->nocp_pop_started = false;
	obj->nocp_push_started = false;

}
#endif

void ring_fifo_init_buffer(ring_fifo_t * cobj, BUFFER_PTR buffer, size_t buffer_size, size_t element_size)
{
	size_t num_of_elements;
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK(obj, "ring_fifo");

	num_of_elements = buffer_size / element_size;

	obj->num_fifo_slots = num_of_elements;

	obj->own_buffer = NULL;
	obj->client_buffer = buffer;
	obj->buffer = obj->client_buffer;
	obj->element_size = element_size;
	obj->rd = 0;
	obj->wr = 0;
	obj->nocp_pop_started = false;
	obj->nocp_push_started = false;
}

void ring_fifo_deinit(ring_fifo_t *cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK(obj, "ring_fifo");

	obj->buffer = NULL;
	obj->client_buffer = NULL;

#ifdef CHELPER_ALLOW_MALLOC
	if (obj->own_buffer) {
		free (obj->own_buffer);
		obj->own_buffer = NULL;
	}
#endif
}

bool ring_fifo_is_full(ring_fifo_t *cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", false);

	return _full(obj);
}

bool ring_fifo_is_empty(ring_fifo_t *cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", true);

	return _empty(obj);
}

uint32_t ring_fifo_count(ring_fifo_t *cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", false);

	return obj->wr - obj->rd;
}


BUFFER_PTR ring_fifo_peek(ring_fifo_t *cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", NULL);

	return _rd_ptr(obj);
}

bool ring_fifo_pop(ring_fifo_t *cobj, BUFFER_PTR to)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", false);

	if (_empty(obj))
		return false;

	if (to)
		memcpy(to, _rd_ptr(obj), obj->element_size);

	obj->rd++;

	return true;
}

bool ring_fifo_push(ring_fifo_t *cobj, BUFFER_PTR_RDOLY copy_src)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", false);

	if (_full(obj))
		return false;

	if (!copy_src)
		return false;

	memcpy(_wr_ptr(obj), copy_src, obj->element_size);

	obj->wr++;

	return true;
}

bool ring_fifo_discard_last_push(ring_fifo_t *cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", false);

	return _discard_last_wr(obj);
}


BUFFER_PTR ring_fifo_zerocopy_pop_start(ring_fifo_t * cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", NULL);

	if (_empty(obj))
		return NULL;

	obj->nocp_pop_started = true;

	return _rd_ptr(obj);
}

void ring_fifo_zerocopy_pop_finish(ring_fifo_t * cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK(obj, "ring_fifo");

	if (!obj->nocp_pop_started)
		return;

	obj->rd++;

	obj->nocp_pop_started = false;
}

BUFFER_PTR ring_fifo_zerocopy_push_start(ring_fifo_t * cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", NULL);

	if (_full(obj))
		return NULL;

	obj->nocp_push_started = true;

	return _wr_ptr(obj);
}

void ring_fifo_zerocopy_push_finish(ring_fifo_t * cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK(obj, "ring_fifo");

	if (!obj->nocp_push_started)
		return;

	obj->wr++;
	obj->nocp_push_started = false;
}

BUFFER_PTR ring_fifo_buffer_start(ring_fifo_t * cobj)
{
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", NULL);

	return (obj->buffer);
}

BUFFER_PTR ring_fifo_peek_at(ring_fifo_t * cobj, int pos)
{
	uint32_t offset;
	struct s_ring_fifo_private * obj = (struct s_ring_fifo_private *)cobj;
	PTR_CHECK_RETURN(obj, "ring_fifo", NULL);

	if (pos < 0)
		return NULL;

	if ((unsigned)pos >= obj->num_fifo_slots)
		return NULL;

	offset = (pos % obj->num_fifo_slots) * obj->element_size;

	return obj->buffer + offset;
}

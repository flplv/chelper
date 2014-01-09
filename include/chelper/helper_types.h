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

#ifndef HELPER_TYPES_H_
#define HELPER_TYPES_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif
#ifndef bool
#define bool uint32_t
#endif
#ifndef __SIZE_TYPE__
typedef unsigned int size_t;
#endif

#define BUFFER_PTR_RDOLY const uint8_t *
#define BUFFER_PTR uint8_t *

typedef uint32_t timeout_t;

struct s_vector_private
{
	size_t item_size;
	uint32_t used_slots;
	uint32_t buffer_total_slots;
	uint8_t * buffer;
};
typedef uint8_t vector_t[sizeof(struct s_vector_private)];

struct s_ring_fifo_private
{
	uint8_t * client_buffer;
	uint8_t * own_buffer;
	uint8_t * buffer;
	size_t buffer_size;
	size_t element_size;
	uint32_t num_fifo_slots;
	bool full;
	uint32_t rd;
	uint32_t wr;
	bool nocp_pop_started;
	bool nocp_push_started;
};
typedef uint8_t ring_fifo_t[sizeof(struct s_ring_fifo_private)];

typedef void * slot_arg;
typedef void(*slot_func)(slot_arg);
typedef void(*slot2_func)(slot_arg, size_t, size_t);
typedef void(*slot_data_func)(slot_arg, void *, size_t);
typedef void(*slot_opaque_func)(slot_arg, void *);

struct s_signal_private
{
	vector_t slots_vector;
};
typedef uint8_t signal_t[sizeof(struct s_signal_private)];
typedef uint8_t signal2_t[sizeof(struct s_signal_private)];
typedef uint8_t signal_data_t[sizeof(struct s_signal_private)];
typedef uint8_t signal_opaque_t[sizeof(struct s_signal_private)];

struct s_slot_private
{
	slot_func func;
	slot_arg arg0;
	bool set;
};
typedef uint8_t slot_t[sizeof(struct s_slot_private)];

struct s_slot2_private
{
	slot2_func func;
	slot_arg arg0;
	bool set;
};
typedef uint8_t slot2_t[sizeof(struct s_slot2_private)];

struct s_slot_data_private
{
	slot_data_func func;
	slot_arg arg0;
	bool set;
};
typedef uint8_t slot_data_t[sizeof(struct s_slot_data_private)];

struct s_slot_opaque_private
{
	slot_opaque_func func;
	slot_arg arg0;
	bool set;
};
typedef uint8_t slot_opaque_t[sizeof(struct s_slot_opaque_private)];

struct s_my_string
{
	vector_t str_data;
	signal_t update_signal;
};
typedef uint8_t my_string_t[sizeof(struct s_my_string)];


#endif /* HELPER_TYPES_H_ */

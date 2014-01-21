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

#ifndef PRIVATE_HELPER_TYPES_H_
#define PRIVATE_HELPER_TYPES_H_

/*
 * All types defined in this header should never be directly referenced nor
 * have its member accessed by external code. These are private data belonging to
 * internal modules only.
 *
 * Each of these structs has a non forward typedef meant to be allocated by client
 * code and used only through chelper's public functions.
 */

struct s_vector_private
{
	size_t item_size;
	uint32_t used_slots;
	uint32_t buffer_total_slots;
	uint8_t * buffer;
};

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

struct s_signal_private
{
	struct s_vector_private slots_vector;
};

struct s_slot_private
{
	slot_func func;
	slot_arg arg0;
	bool set;
};

struct s_slot2_private
{
	slot2_func func;
	slot_arg arg0;
	bool set;
};

struct s_slot_data_private
{
	slot_data_func func;
	slot_arg arg0;
	bool set;
};

struct s_slot_opaque_private
{
	slot_opaque_func func;
	slot_arg arg0;
	bool set;
};

struct s_my_string_private
{
	struct s_vector_private str_data;
	struct s_signal_private update_signal;
};

#endif /* PRIVATE_HELPER_TYPES_H_ */

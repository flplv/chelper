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

typedef void * slot_arg;
typedef void(*slot_func)(slot_arg);
typedef void(*slot2_func)(slot_arg, size_t, size_t);
typedef void(*slot_data_func)(slot_arg, void *, size_t);
typedef void(*slot_opaque_func)(slot_arg, void *);

#include "private_helper_types.h"

typedef uint32_t timeout_t;

typedef struct s_vector_private vector_t;

typedef struct s_ring_fifo_private ring_fifo_t;

typedef struct s_signal_private signal_t;
typedef struct s_signal_private signal2_t;
typedef struct s_signal_private signal_data_t;
typedef struct s_signal_private signal_opaque_t;

typedef struct s_slot_private slot_t;

typedef struct s_slot2_private slot2_t;

typedef struct s_slot_data_private slot_data_t;

typedef struct s_slot_opaque_private slot_opaque_t;

typedef struct s_my_string_private my_string_t;


#endif /* HELPER_TYPES_H_ */

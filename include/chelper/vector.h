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

#ifndef VECTOR_H_
#define VECTOR_H_

#include <chelper/helper_types.h>

#ifdef __cplusplus
extern "C" {
#endif

void vector_init(vector_t *, size_t item_size);
void vector_deinit(vector_t *);

size_t vector_size(vector_t *);
BUFFER_PTR vector_at(vector_t *, size_t pos);

void vector_add(vector_t *, BUFFER_PTR_RDOLY item);
void vector_add_many(vector_t *, BUFFER_PTR_RDOLY item, size_t count);
void vector_remove(vector_t *, size_t pos);
void vector_clear(vector_t *);

const void * vector_data(vector_t *);

#ifdef __cplusplus
}
#endif

#endif /* VECTOR_H_ */

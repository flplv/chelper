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

#ifndef MY_STRING_H_
#define MY_STRING_H_

#include <chelper/helper_types.h>
#include <chelper/signalslot.h>

#ifdef __cplusplus 
extern "C" {
#endif


void my_string_init(my_string_t *);
void my_string_deinit(my_string_t *);

void my_string_set(my_string_t *, const char *);
const char *my_string_get(my_string_t *);
void my_string_clear(my_string_t *);

size_t my_string_len(my_string_t *);

signal_t * my_string_get_update_signal(my_string_t * obj);

size_t my_strlen(const char* str);

#ifdef __cplusplus 
}
#endif

#endif /* MY_STRING_H_ */

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

#include <stdbool.h>
#include "chelper/signalslot_opaque.h"
#include "chelper/vector.h"
#include "chelper/checks.h"
#include "chelper/log.h"

#define s_slot_private s_slot_opaque_private

#define slot_func slot_opaque_func

#define signal_func_decl(name) signal_opaque_##name
#define slot_func_decl(name) slot_opaque_##name

#define signal_t   signal_opaque_t
#define slot_t   slot_opaque_t

#define slot_func_args slot_opaque_t * cobj, void * data, size_t size
#define signal_func_args signal_opaque_t * cobj, void * data, size_t size

#define signal_slot_func_args_variable , data, size

#define signal_string "signal_opaque"
#define slot_string "slot_opaque"

#include "./signalslot.cbody"

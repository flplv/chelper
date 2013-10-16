#ifndef RINGFIFO_H_
#define RINGFIFO_H_

#include <chelper/helper_types.h>

void ring_fifo_init(ring_fifo_t *, size_t element_size, int32_t num_of_elements);
void ring_fifo_init_buffer(ring_fifo_t *, BUFFER_PTR buffer, size_t buffer_size, size_t element_size);
void ring_fifo_deinit(ring_fifo_t *);

BOOL ring_fifo_is_full(ring_fifo_t *);
BOOL ring_fifo_is_empty(ring_fifo_t *);

BUFFER_PTR ring_fifo_peek(ring_fifo_t *);
BOOL ring_fifo_pop(ring_fifo_t *, BUFFER_PTR to);

BOOL ring_fifo_push(ring_fifo_t *, BUFFER_PTR_RDOLY copy_src);


#endif /* RINGFIFO_H_ */

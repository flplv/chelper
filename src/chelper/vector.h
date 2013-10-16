#ifndef VECTOR_H_
#define VECTOR_H_

#include <chelper/helper_types.h>

void vector_init(vector_t *, size_t item_size);
void vector_deinit(vector_t *);

size_t vector_size(vector_t *);
BUFFER_PTR vector_at(vector_t *, size_t pos);

void vector_add(vector_t *, BUFFER_PTR_RDOLY item);
void vector_add_many(vector_t *, BUFFER_PTR_RDOLY item, size_t count);
void vector_remove(vector_t *, size_t pos);
void vector_clear(vector_t *);

const void * vector_data(vector_t *);

#endif /* VECTOR_H_ */

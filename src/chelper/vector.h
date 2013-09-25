#ifndef VECTOR_H_
#define VECTOR_H_

#include "helper_types.h"

void vector_init(vector_t *, uint32_t item_size);
void vector_deinit(vector_t *);

void vector_add(vector_t *, BUFFER_PTR_RDOLY item);
uint32_t vector_size(vector_t *);
BUFFER_PTR vector_at(vector_t *, uint32_t pos);

#endif /* VECTOR_H_ */

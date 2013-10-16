#ifndef MY_STRING_H_
#define MY_STRING_H_

#include <chelper/helper_types.h>
#include <chelper/signalslot.h>

void my_string_init(my_string_t *);
void my_string_deinit(my_string_t *);

void my_string_set(my_string_t *, const char *);
const char *my_string_get(my_string_t *);
void my_string_clear(my_string_t *);

size_t my_string_len(my_string_t *);

signal_t * my_string_get_update_signal(my_string_t * obj);

size_t my_strlen(const char* str);


#endif /* MY_STRING_H_ */

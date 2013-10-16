#ifndef NUMBER_H_
#define NUMBER_H_

#include <chelper/helper_types.h>

BOOL charactere_is_null(char c);
BOOL charactere_is_hex(char c);
BOOL charactere_is_space(char c);
BOOL charactere_is_math_sig(char c);
BOOL charactere_is_printable(char c);
uint8_t charactere_hex_to_int(char c);
int32_t string_hex_to_int(const char* str);
void int_to_string(int32_t number, char * target, size_t size);

#define MAX(__1__, __2__) (((__1__)>(__2__))?(__1__):(__2__))
#define MIN(__1__, __2__) (((__1__)<(__2__))?(__1__):(__2__))
#define SIG(__num__) ((((int)__num__)>0)?(1):(-1))

#endif /* NUMBER_H_ */

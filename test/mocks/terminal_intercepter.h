extern "C" {
#include "chelper/fatal.h"
}

extern const char *intercepted_output[];

int output_intercepter(const char * str);

extern "C" {
extern int _stdout_output_impl(const char * str);
}

#define ENABLE_INTERCEPTION fatal_terminal_output = output_intercepter
#define DISABLE_INTERCEPTION fatal_terminal_output = _stdout_output_impl

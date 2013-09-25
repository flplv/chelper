/*
 * debug.h
 *
 *  Created on: Dec 24, 2012
 *      Author: fanl
 */

#ifndef LOG_H_
#define LOG_H_

#include "helper_types.h"

enum e_log_lvl {
	ERROR,
	WARNING,
	MESSAGE
};

struct s_my_log_private
{
	const char *module_tag;
	enum e_log_lvl default_my_log_level;
	int (*stream_output)(const char *);
};
typedef uint8_t my_log_t[sizeof(struct s_my_log_private)];

void my_log_init(my_log_t * const obj, const char * title, enum e_log_lvl default_lvl);
void my_log_deinit(my_log_t * const obj);

void my_log(enum e_log_lvl, const char *file, int line, const char *, my_log_t *);
void my_log_continue(const char *, my_log_t *);
void my_log_continue_new_line(const char *, my_log_t *);
BOOL my_log_assert(BOOL test, enum e_log_lvl lvl, const char *file, int line, const char * text, my_log_t * const);

void global_my_log(enum e_log_lvl lvl, const char *file, int line, const char * text, const char * owner);
void global_my_log_continue(const char *);

#define LOG_ERROR(__owner, __text) global_my_log(ERROR, __FILE__, __LINE__, __text, __owner)

#endif /* LOG_H_ */


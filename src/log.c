#include "chelper/number.h"

#include "chelper/log.h"
#include <stdio.h>
#include <string.h>

char output_prefix_string[20];
char line_output_string[20];

int _stdout_output_impl(const char * str)
{
	const char *pCh = str;
	while (*pCh)
		putchar(*pCh++);
	fflush(stdout);
	return pCh - str;
}
int (*fatal_terminal_output)(const char * str) = _stdout_output_impl;

void my_log_init(my_log_t * const cobj, const char * module_tag, enum e_log_lvl default_lvl)
{
	struct s_my_log_private * log = (struct s_my_log_private *)cobj;

	log->module_tag = module_tag;
	log->default_my_log_level = default_lvl;
	log->stream_output = fatal_terminal_output;
}

void my_log_deinit(my_log_t * const cobj)
{
	struct s_my_log_private * log = (struct s_my_log_private *)cobj;
}

void my_log(enum e_log_lvl lvl, const char *file, int line, const char * text, my_log_t * const cobj)
{
	struct s_my_log_private * owner = (struct s_my_log_private *)cobj;

	if (!owner)
		return;

	if (!owner->stream_output)
		return;
	if (lvl > owner->default_my_log_level)
		return;

	if (lvl == ERROR)
	{
		strncpy(output_prefix_string, "error: ", 20);
	}
	else if (lvl == WARNING)
	{
		strncpy(output_prefix_string, "warning: ", 20);
	}
	else if (lvl == MESSAGE)
	{
		strncpy(output_prefix_string, "message: ", 20);
	}

	int_to_string(line, line_output_string, 20);

	owner->stream_output("\n");
	owner->stream_output(file);
	owner->stream_output(":");
	owner->stream_output(line_output_string);
	owner->stream_output(": ");
	owner->stream_output(output_prefix_string);
	owner->stream_output(owner->module_tag);
	owner->stream_output(": ");
	owner->stream_output(text);
}

void my_log_continue(const char * text, my_log_t * const cobj)
{
	struct s_my_log_private * owner = (struct s_my_log_private *)cobj;

	if (!owner)
		return;

	if (!owner->stream_output)
		return;

	owner->stream_output(text);
}

void my_log_continue_new_line(const char * text, my_log_t * const cobj)
{
	int i;
	struct s_my_log_private * owner = (struct s_my_log_private *)cobj;

	if (!owner)
		return;

	if (!owner->stream_output)
		return;

	owner->stream_output("\n");
	i = strlen(owner->module_tag);
	while (i--)
		owner->stream_output(" ");
	owner->stream_output("       ");
	owner->stream_output(text);
}

BOOL my_log_assert(BOOL test, enum e_log_lvl lvl, const char *file, int line, const char * text, my_log_t * const cobj)
{
	struct s_my_log_private * owner = (struct s_my_log_private *)cobj;

	if (!owner)
		return FALSE;

	if (!test)
	{
		my_log(lvl, file, line, "Assertion Failed: ", cobj);
		my_log_continue(text, cobj);
		return TRUE;
	}
	return FALSE;
}

void global_my_log(enum e_log_lvl lvl, const char *file, int line, const char * text, const char * owner)
{
	struct s_my_log_private log;

	if (!owner)
		return;

	if (!text)
		return;

	if (text < (char *)0)
		return;

	log.default_my_log_level = MESSAGE;
	log.module_tag = owner;
	log.stream_output = fatal_terminal_output;
	my_log(lvl, file, line, text, (my_log_t*)&log);
}

void global_my_log_continue(const char * text)
{
	struct s_my_log_private log;

	if (!text)
		return;

	if ((signed int)text < 0)
		return;


	log.default_my_log_level = MESSAGE;
	log.module_tag = "";
	log.stream_output = fatal_terminal_output;
	my_log_continue(text, (my_log_t*)&log);
}

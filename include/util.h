#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

int is_number(char *str);

void print_help();

void safe_fclose(FILE *file_to_close);

#endif

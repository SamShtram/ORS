#ifndef UTILS_H
#define UTILS_H

#include "surgery.h"

// Reads surgeries interactively from user input
void load_surgeries_interactive();

// Prints surgery summary after simulation ends
void print_summary();

// Safely trim newline from fgets input
void trim_newline(char* str);

#endif

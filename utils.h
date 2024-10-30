#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>
#include <stdbool.h>

#define SEND_DELAY 60000

bool read_n_bytes(const void* nb, const size_t bytes, const int bit, const bool print_progress);

void send_n_bytes_to_pid(pid_t pid, unsigned long data, int n, const bool print_progress);

void print_ascii_loading_animation(const size_t current, const size_t total);

#endif
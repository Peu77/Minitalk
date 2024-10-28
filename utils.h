#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>

typedef enum e_receive_step
{
    RECEIVE_PID = 0,
    RECEIVE_SIZE = 1,
    RECEIVE_DATA = 2
} t_receive_step;

void send_n_bytes_to_pid(pid_t pid, unsigned long data, int n);

#endif
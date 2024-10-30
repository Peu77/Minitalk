#ifndef SERVER_H
#define SERVER_H
#include <stdbool.h>
#include <sys/types.h>

typedef enum e_receive_step
{
    RECEIVE_PID = 0,
    RECEIVE_SIZE = 1,
    RECEIVE_DATA = 2
} t_receive_step;

typedef struct s_client_info
{
    pid_t pid;
    size_t size;
    char *str;
    enum e_receive_step step;
    char current_char;
    size_t char_i;
} t_client_info;

typedef bool(*receive_fun)(t_client_info* client_info);

typedef struct s_receive_step_mapper
{
    enum e_receive_step step;
    receive_fun fun;
    size_t data_size;
    void* data;
} t_receive_step_mapper;

void reset_client_info(t_client_info* client_info);

#endif
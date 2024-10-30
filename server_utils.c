#include "server.h"
#include <stdlib.h>

void reset_client_info(t_client_info* client_info)
{
    client_info->pid = 0;
    client_info->size = 0;
    if (client_info->str)
    {
        free(client_info->str);
        client_info->str = NULL;
    }
}
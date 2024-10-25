#include <stdio.h>
#include <sys/signal.h>
#include <sys/_types/_pid_t.h>
#include <unistd.h>

void signal_handler(pid_t pid){
    static int byte_i = 0;
    static char c;
    static pid_t client_pid;
    static int char_i = 0;

    const int bit = pid - 30;

    if(char_i == 0)
    {
        client_pid |= ((pid_t)bit) << byte_i;
        byte_i++;
        if(byte_i == 32)
        {
            printf("client_id: %ul\n", client_pid);
            char_i++;
            byte_i = 0;
        }
        return;
    }

    c |= (pid - 30) << (byte_i);
    byte_i += 1;
    if(byte_i == 8){
        write(1, &c, 1);
        if(c == 0)
        {
            write(1, "\n", 1);
            client_pid = 0;
            char_i = 0;
        }
        c = 0;
        byte_i = 0;
    }


}

int main(){
    signal(SIGUSR1, signal_handler );
    signal(SIGUSR2, signal_handler );

    printf("pid: %d\n", getpid());

    while(pause());
    return 0;
}

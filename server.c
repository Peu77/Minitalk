#include <stdio.h>
#include <sys/signal.h>
#include <sys/_types/_pid_t.h>
#include <unistd.h>

void signal_handler(int sig){
    static int byte_i = 0;
    static char c;

    c |= (sig - 30) << byte_i;
    byte_i += 1;
    if(byte_i == 8){
        write(1, &c, 1);
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

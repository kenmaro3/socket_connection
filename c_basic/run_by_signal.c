//gcc -o run_by_signal run_by_signal.c

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


int main(void)
{
    printf("Initialize...\n");
    // run some initialization here
    int test = 2;
    sleep(1);

    pid_t c_pid = getpid();
    printf("Send SIGCONT to PID: %d to run\n", c_pid);

    while(1)
    {
        raise(SIGTSTP);
        printf("run \n");
        printf("%d \n", test);
    }

    return 0;
}
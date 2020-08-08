//gcc -o send_signal send_signal.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>


int main(int argc, char *argv[]) {
    printf("send continue signal to PID:%s\n", argv[1]);
    kill(atoi(argv[1]), SIGCONT);
}
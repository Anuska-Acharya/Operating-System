#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = getpid();
    printf("before fork %d\n", pid);

    pid = fork();

    if (pid == 0)
    {
        printf("thisline from child,\n");
        printf("the child process id %d\n", getpid());

        execl("/bin/ls", "ls", "-1", (char *)0);

        exit(0);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("before fork %d\n", getpid());
    }
    else
    {
        printf("fork failed\n");
        exit(1);
    }

    return 0;
}
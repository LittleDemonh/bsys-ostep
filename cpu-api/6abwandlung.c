#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/wait.h"

int main()
{
    int rc = fork();
    if (rc < 0)
    { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    { // child (new process)
        printf("hello\n");
    }
    else
    { // parent goes down this path (main)
        int rc2 = fork();
        if (rc2 < 0)
        { // fork failed
            fprintf(stderr, "second fork failed\n");
            exit(1);
        }
        else if (rc2 == 0)
        { // second child (new process)
            printf("hello from second child\n");
        }
        else
        { // parent process
            int w1 = waitpid(rc, NULL, 0); // wait for first child
            int w2 = waitpid(rc2, NULL, 0); // wait for second child
            printf("goodbye\n");
            printf("waitpid() for first child: %d\n", w1);
            printf("waitpid() for second child: %d\n", w2);
        }
    }
    return 0;
}
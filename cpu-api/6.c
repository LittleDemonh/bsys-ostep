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
        int w = waitpid(rc, NULL, 0);       // 0 warten auf Childprozess bis er beendet ist
        printf("goodbye\n");
        printf("waitpid(): %d\n", w);
    }
    return 0;
}

// nützlich, wenn mehrere Childprozesse vorhanden sind
// mehr Kontrolle über das Warten auf Childprozesse
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
        int w = wait(NULL);
        printf("hello\n");          
        printf("wait(): %d\n", w);     //wenn wait() im Childprozess aufgerufen wird, gibt es -1 zurück, da es keine weiteren Childprozesse gibt
    }
    else
    { // parent goes down this path (main)
        int w = wait(NULL);
        printf("goodbye\n");
        printf("wait(): %d\n", w);  //wait() gibt die PID des Childprozesses zurück
                                    //Parent wartet auf Childprozess
    }
    return 0;
}

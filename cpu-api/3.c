#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main() 
{
    int rc = fork();
    if (rc < 0) 
    { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) 
    { // child (new process)
        printf("hello (child)\n");
    } else 
    { // parent goes down this path (main)
        sleep(1);                   //statt wait(NULL); pausiert den Elternprozess für 1 Sekunde,
                                    //CPU wird nicht blockiert
        printf("goodbye (parent)\n");
    }
    return 0;
}

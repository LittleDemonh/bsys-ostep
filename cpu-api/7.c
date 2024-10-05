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
        close(STDOUT_FILENO);               // wen fork 0 returnt, dann wird Standardausgabe geschlossen
        printf("hello (child)\n");          // wird nicht ausgegeben, da Standardausgabe geschlossen wurde
    } else 
    { // parent goes down this path (main)
        printf("goodbye (parent)\n");
    }
    return 0;
}

#define _GNU_SOURCE             // for execvpe

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <features.h>

int main() {
    char *argv[] = {"ls", (char *)NULL};
    char *envp[] = {"PATH=/bin", NULL};

    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        if (execlp("ls", "ls", (char *)NULL) == -1) {
            fprintf(stderr, "execlp failed\n");
            exit(1);
        }
    }

    wait(NULL);

    if(rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
    } else if(rc == 0) {
        if (execl("/bin/ls", "ls", (char *)NULL) == -1) {   
            fprintf(stderr, "execl failed\n");
            exit(1);
        }
    }

    wait(NULL); 

    rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        if (execle("/bin/ls", "ls", (char *)NULL, envp) == -1) {
            fprintf(stderr, "execle failed\n");
            exit(1);
        }
    }

    wait(NULL);

    rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        if (execvp("ls", argv) == -1) {
            fprintf(stderr, "execvp failed\n");
            exit(1);
        }
    }

    wait(NULL);

    rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        if (execve("/bin/ls", argv, envp) == -1) {
            fprintf(stderr, "execve failed\n");
            exit(1);
        }
    }

    wait(NULL);

    rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        if (execvpe("ls", argv, envp) == -1) {
            fprintf(stderr, "execvpe failed\n");
            exit(1);
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{

    int fds[2]; // fds[0] = read, fds[1] = write
    char buffer[50];

    if (pipe(fds) == -1) // pipe erstellen
    {
        printf("pipe failed\n");
        exit(1);
    }

    int f = fork();

    if (f < 0)
    { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (f == 0)
    {                                // childprocess
        close(fds[0]);               // read end wird geschlossen, da nicht benötigt
        dup2(fds[1], STDOUT_FILENO); // stdout wird auf den write-Ende des Pipes umgeleitet
        close(fds[1]);
        printf("Hallo (Child)");
        exit(0);
    }
    else
    { // parentprocess
        int f2 = fork();
        if (f2 < 0)
        { // fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        else if (f2 == 0)
        {
            // 2. child
            close(fds[1]);                        // write end wird geschlossen, da nicht benötigt
            read(fds[0], buffer, sizeof(buffer)); // liest vom read-Ende der pipe, wird in buffer gespeichert
            close(fds[0]);
            if (strcmp(buffer, "Hallo (Child)") == 0)
            {
                printf("%s\n", buffer);
                printf("Hallo!\n");
            }
            else
            {
                printf("failed\n");
            }
            exit(0);
        }
        else
        {
            // parentprocess
            close(fds[0]);
            close(fds[1]);
            wait(NULL); // um Zombieprozesse zu vermeiden
            wait(NULL);
        }
    }
    return 0;
}
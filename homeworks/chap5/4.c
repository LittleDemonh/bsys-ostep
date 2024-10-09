#define _GNU_SOURCE // for execvpe

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <features.h>

int main()
{
    char *argv[] = {"ls", (char *)NULL};
    char *envp[] = {"PATH=/bin", NULL};

    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // sucht im path, erfordert nicht den vollständigen Pfad, Programmname reicht
        if (execlp("ls", "ls", (char *)NULL) == -1)
        {
            fprintf(stderr, "execlp failed\n");
            exit(1);
        }
    }

    wait(NULL);

    rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // sucht nicht im path
        if (execl("/bin/ls", "ls", (char *)NULL) == -1)
        {
            fprintf(stderr, "execl failed\n");
            exit(1);
        }
    }

    wait(NULL);

    rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // sucht nicht im path, man kann Umgebungsvariablen setzen
        if (execle("/bin/ls", "ls", (char *)NULL, envp) == -1)
        {
            fprintf(stderr, "execle failed\n");
            exit(1);
        }
    }

    wait(NULL);

    rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // sucht im path, programmname reicht
        if (execvp("ls", argv) == -1)
        {
            fprintf(stderr, "execvp failed\n");
            exit(1);
        }
    }

    wait(NULL);

    rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // sucht nicht im path, pfad muss angegeben werden, Umgebungsvariablen können gesetzt werden
        if (execve("/bin/ls", argv, envp) == -1)
        {
            fprintf(stderr, "execve failed\n");
            exit(1);
        }
    }

    wait(NULL);

    rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // sucht im path, programmname reicht, Umgebungsvariablen können gesetzt werden
        if (execvpe("ls", argv, envp) == -1)
        {
            fprintf(stderr, "execvpe failed\n");
            exit(1);
        }
    }

    return 0;
}
// Flexibilität
// execl, execlp, execle: Argumente werden als separate Parameter übergeben.
// execv, execvp, execvpe: Argumente werden als Array übergeben.
// manche suchen im path, andere brauchen den vollständigen pfad
// manche können Umgebungsvariablen setzen

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("2.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd < 0)
    {
        fprintf(stderr, "open file failed\n");
        exit(1);
    }

    int x = 100;
    int rc = fork();
    if (rc < 0)
    { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    { // child (new process)
        dprintf(fd, "x child: %d\n", x);
    }
    else
    { // parent goes down this path (main)
        dprintf(fd, "x parent: %d\n", x);
    }

    close(fd);
    return 0;
}
// beide Prozesse schreiben in die Datei, da sie den gleichen filedescriptor verwenden
// es könnte zu verschachtelten Ausgaben kommen, da beide Prozesse gleichzeitig schreiben können
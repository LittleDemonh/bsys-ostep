#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    FILE* f = fopen("file.txt", "w");       //Erstellt eine Datei file.txt, w für wite
    if(f == NULL)                           //Falls Datei nicht erstellt werden kann
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
        fprintf(f, "x child: %d\n", x);
    }
    else
    { // parent goes down this path (main)
        fprintf(f, "x parent: %d\n", x);
    }
    return 0;
}
//fopen kann nur einmal geöffnet werden, daher wird die Datei nur einmal beschrieben
//fopen bei child und parent wäre nicht möglich, 2 Dateien 
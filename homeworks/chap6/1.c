#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/types.h>

#define ITERATIONS 1000000

int main()
{
    struct timeval start, end; // Start- und Endzeit

    // Präzision von gettimeofday()
    long total = 0;
    for (int i = 0; i < ITERATIONS; i++)
    {
        gettimeofday(&start, NULL);
        gettimeofday(&end, NULL);

        long seconds = end.tv_sec - start.tv_sec;        // Berechnet die Zeitdifferenz in Sekunden
        long microseconds = end.tv_usec - start.tv_usec; // Mikrosekunden
        total += seconds * 1000000 + microseconds;       // Gesamtzeit in Mikrosekunden
    }
    
    printf("Durchschnittliche Abweichung von gettimeofday(): %.6f µs\n", (double)total / ITERATIONS);

    char buffer[1];             // 1-Byte Puffer für read-Aufruf
    gettimeofday(&start, NULL); // Zeit vor den Systemaufrufen

    for (int i = 0; i < ITERATIONS; i++)
    {
        read(0, buffer, 0); // es werden 0 Bytes gelesen
    }

    gettimeofday(&end, NULL); // Zeit nach den Systemaufrufen

    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    total = seconds * 1000000 + microseconds;
    printf("Durchschnittliche Zeit pro Systemaufruf: %.6f µs\n", (double)total / ITERATIONS);

    int pipe1[2];
    int pipe2[2];

    // cpu_set_t-Objekt wird initialisiert, um die CPU-Affinität der Prozesse festzulegen
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(0, &cpu_set);

    if (pipe(pipe1) < 0)
    {
        printf("pipe error\n");
        exit(1);
    }
    if (pipe(pipe2) < 0)
    {
        printf("pipe error\n");
        exit(1);
    }

    int rc = fork();
    if (rc < 0)
    {
        printf("fork() failed\n");
        exit(1);
    }
    else if (rc == 0) // Prozess 1
    {
        sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set); // Kindprozess setzt seine CPU-Affinität auf CPU 0

        for (int i = 0; i < ITERATIONS; i++)
        {
            write(pipe1[1], NULL, 0); // schreibt in die 1. Pipe
            read(pipe2[0], NULL, 0);  // liest aus der 2. Pipe
        }
    }
    else
    {                                                             // Prozess 2
        sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set); // Der Elternprozess setzt ebenfalls seine CPU-Affinität auf CPU 0

        gettimeofday(&start, NULL);
        for (int i = 0; i < ITERATIONS; i++)
        {
            read(pipe1[0], NULL, 0);  // liest aus der 1. Pipe
            write(pipe2[1], NULL, 0); // schreibt in die 2. Pipe
        }
        gettimeofday(&end, NULL);

        seconds = end.tv_sec - start.tv_sec;
        microseconds = end.tv_usec - start.tv_usec;
        total = seconds * 1000000 + microseconds;
        printf("Durchschnittliche Zeit pro Kontextwechsel: %.6f µs\n", (double)total / ITERATIONS);
        // Muss ich die Iterations noch *2 nehmen, um die Zeit für einen Kontextwechsel zu berechnen?
    }
    return 0;
}

/*
 * Kontextwechsel wird langsamer je mehr Iterationen durchgeführt werden
 * Overhead nimmt zu, Scheduler muss mehr Daten verwalten und Prozesse wechseln
 * Viele Systemaufrufe führen zu mehr Overhead
 * Mehr Iterationen = höherer Ressourcenverbrauch (CPU-Zeit, Speicher)
 */
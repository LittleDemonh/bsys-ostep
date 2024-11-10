#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <megabytes> <duration>\n", argv[0]);
        return 1;
    }

    int megabytes = atoi(argv[1]);
    int duration = (argc > 2) ? atoi(argv[2]) : -1;

    size_t array_size = (size_t)megabytes * 1024 * 1024 / sizeof(int);
    int *array = (int *)malloc(array_size * sizeof(int));
    if (array == NULL)
    {
        perror("malloc");
        return 1;
    }

    time_t start_time = time(NULL);

    while (1)
    {
        for (size_t i = 0; i < array_size; i++)
        {
            array[i] = i;
        }

        if (duration > 0 && difftime(time(NULL), start_time) >= duration)
        {
            break;
        }
    }

    free(array);
    return 0;
}

#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <memory.h>

#define time_to_ns(t) ((t.tv_sec * 1000000) + t.tv_usec)

int main()
{
    struct timeval start;
    gettimeofday(&start, NULL);

    struct timeval current;
    memcpy(&current, &start, sizeof(struct timeval));

    uint64_t elapsed_time = time_to_ns(current) - time_to_ns(start);

    while (elapsed_time < 1000000)
    {
        gettimeofday(&current, NULL);
        elapsed_time = time_to_ns(current) - time_to_ns(start);
    }
    
    printf("%ld\n", elapsed_time);
}
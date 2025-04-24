#include <stdlib.h>

int mcpi_loop(int n_total)
{
    int n_inside = 0;
    for(int i = 0; i < n_total; ++i) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        if(x * x + y * y < 1.0)
            ++n_inside;
    }

    return n_inside;
}

#include <time.h>

static struct timespec t0;

void tik()
{
    clock_gettime(CLOCK_REALTIME, &t0);
}

double tok()
{
    struct timespec t1, dt;
    clock_gettime(CLOCK_REALTIME, &t1);

    dt.tv_nsec = t1.tv_nsec - t0.tv_nsec;
    dt.tv_sec  = t1.tv_sec  - t0.tv_sec;
    if(dt.tv_nsec < 0) {
        dt.tv_nsec += 1000000000;
        dt.tv_sec--;
    }

    int ms = dt.tv_nsec / 1000000 + dt.tv_sec * 1000;
    int ns = dt.tv_nsec % 1000000;

    return ms + 1e-6 * ns;
}

#include <stdio.h>

int main()
{
    tik();

    double pi = 4.0 * mcpi_loop(1000000) / 1000000;
    double ms = tok();

    printf("pi = %f\n", pi);
    printf("dt = %f ms\n", ms);

    return 0;
}
//To run: gcc example.c
//Then, ./a.out
//gcc example.c -o example writes the output in example
//So, ./example

#include <stdlib.h>
#include <stdio.h>

struct solution {           //declares a structure (like a tuple)
    double *T;
    double *X;
};

struct solution             //the function returns the structure
forward_Euler(double (*f)(double), double x, double t, double dt, int n)
{
    double *T = (double *)malloc(sizeof(double) * (n+1));       //allocates memory
    double *X = (double *)malloc(sizeof(double) * (n+1));       //array is of fixed size

    T[0] = t;
    X[0] = x;

    for(int i = 1; i <= n; ++i) {               //for (start, stop, increment)
        t += dt;
        x += f(x) * dt;
        T[i] = t;
        X[i] = x;
    }

    struct solution s = {T, X};
    return s;
}

void
free_solution(struct solution s)
{
    free(s.T);          //frees the memory
    free(s.X);
}

double f(double x)
{
    return x;
}

int main(int argc, char *argv[])        //executables must be in a function
{
    int n = 20;
    struct solution s = forward_Euler(f, 1, 0, 0.1, n);

    for(int i = 0; i <= n; ++i)
        printf("%f %f\n", s.T[i], s.X[i]);      //"%f %f\n" is a format string

    free_solution(s);

    return 0;
}
#include <omp.h>
#include <stdio.h>

#define NUM_THR 10

static long num_steps = 100000;
double step;

int main()
{
    int i;

    double x,pi,sum=0;

    step=1.0/(double)num_steps;



    #pragma omp parallel for reduction(+:sum) private(x)      // private ile x her bir thread için ayrı
    for(i=0; i<num_steps; i++)
    {
        x = (i+0.5)*step;
        sum += 4.0/(1.0 + x*x);
    }


    pi = step*sum;

    printf("pi: %f \n", pi);


    return 0;
}

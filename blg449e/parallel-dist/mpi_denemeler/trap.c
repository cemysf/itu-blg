#include <stdio.h>
#include <mpi/mpi.h>

// f(x) = x^2
double f(double x)
{
    return x*x;
}

//double trap(double a, double b, double local_n, double h)
//{
//    double integral;

//    for(int i=1; i<local_n; i++)
//    {

//    }
//}

/*------------------------------------------------------------------
 * Function:     Trap
 * Purpose:      Serial function for estimating a definite integral
 *               using the trapezoidal rule
 * Input args:   left_endpt
 *               right_endpt
 *               trap_count
 *               base_len
 * Return val:   Trapezoidal rule estimate of integral from
 *               left_endpt to right_endpt using trap_count
 *               trapezoids
 */
double Trap(
      double left_endpt  /* in */,
      double right_endpt /* in */,
      int    trap_count  /* in */,
      double base_len    /* in */) {
   double estimate, x;
   int i;

   estimate = (f(left_endpt) + f(right_endpt))/2.0;
   for (i = 1; i <= trap_count-1; i++) {
      x = left_endpt + i*base_len;
      estimate += f(x);
   }
   estimate = estimate*base_len;

   return estimate;
} /*  Trap  */

int main()
{
    int n = 1024, local_n;      //integralde toplam trapezoid sayısı, process başına düşen trapezoid sayısı(hepsi için eşit)
    double a=0.0, b=3.0;        //bütündeki sınırlar
    double local_a, local_b;    //process başına düşen sınırlar
    double h;                   //process başına height (hepsi için eşit)
    double local_integration, total_integration=0.0; //process başına ve toplamın integralleri

    // Paralel başl.
    int my_rank, comm_size;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    h=(b-a)/n;
    local_n = n/comm_size;

    local_a = a + my_rank*local_n*h;
    local_b = local_a + local_n*h;

    local_integration = Trap(local_a, local_b, local_n, h);

//    if(my_rank != 0)
//    {
//        MPI_Send (&local_integration, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
//    } else
//    {
//        total_integration = local_integration;
//        for(int i = 1; i<comm_size; i++)
//        {
//            MPI_Recv(&local_integration, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//            printf("received %f from %d\n", local_integration, i);

//            total_integration += local_integration;
//        }
//    }



    /// MPI_Reduce
    /// Her process bunu çalıştırıyor, operasyon sonucu dest process'e (rank0) dönüyor
//    MPI_Reduce (&local_integration, &total_integration, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

//    if(my_rank == 0)
//        printf("total integration: %f\n", total_integration);




    /// MPI_Allreduce
    /// Operasyon sonucu tek bir process'e değil tüm processlere gönderiliyor
    MPI_Allreduce (&local_integration, &total_integration, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    if(my_rank != 0)    /// Diğer processler rank0'a gönderiyor
        MPI_Send (&total_integration,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    else
    {
        double buff;
        for(int i=1; i<comm_size; i++)
        {
            MPI_Recv (&buff, 1, MPI_DOUBLE,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf("received %f from %d\n", buff, i);
        }
    }

    if(my_rank == 0)
        printf("total integration: %f\n", total_integration);

    MPI_Finalize();
    return 0;
}

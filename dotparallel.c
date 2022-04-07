// Basado en https://www.hpc.kaust.edu.sa/sites/default/files/files/public/KSL_WS_MPI.pdf
//Producto punto entre dos vectores
#include <mpi.h>
#include <stdio.h>

const int N=5000;

//Los vectores se autogeneran usando un parametro n y agregando los numeros respectivos
double dotProduct(double *x, double *y, int n) {
  int i;
  double prod = 0.0;
  for (i = 0; i < n; i++) {
    prod += x[i]*y[i];
  }
  return prod;

// Se realiza el proceso paralelo para realizar los calculos y al final se imprime el resultado del producto punto
int main(int argc, char *argv[]) {
  int i;
  double prod;
  int my_rank;
  int num_procs;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  int local_N = N / num_procs; 
  double local_x[local_N];
  double local_y[local_N];

  for(i = 0; i < local_N; i++) {
    local_x[i] = 0.02 * (i + my_rank * local_N);
    local_y[i] = 0.04 * (i + my_rank * local_N);
  }
  double local_prod;
  local_prod = dotProduct(local_x,local_y,local_N);

  MPI_Reduce(&local_prod, &prod, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (my_rank == 0) {
    printf("Producto punto: %f\n", prod);
  }  
  MPI_Finalize();

  return 0;
}
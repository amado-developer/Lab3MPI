/* File:     vector_add.c
 *
 * Purpose:  Implement vector addition
 *
 * Compile:  gcc -g -Wall -o vector_add vector_add.c
 * Run:      ./vector_add
 *
 * Input:    The order of the vectors, n, and the vectors x and y
 * Output:   The sum vector z = x+y
 *
 * Note:
 *    If the program detects an error (order of vector <= 0 or malloc
 * failure), it prints a message and terminates
 *
 * IPP:      Section 3.4.6 (p. 109)
 */

/*
 * Ref. for generating random vectors Ahttps://www.codespeedy.com/generate-a-random-array-in-c-or-cpp/
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Read_n(int* n_p);
void Allocate_vectors(double** x_pp, double** y_pp, double** z_pp, int n);
void Print_vector(double b[], int n, char title[]);
void Vector_sum(double x[], double y[], double z[], int n);
void Random_vector_creator(double a[], int n, char vec_name[]);

/* Funcion principal */
int main(void) {
   int n;
   double *x, *y, *z;

   Read_n(&n);

   Allocate_vectors(&x, &y, &z, n);


   Random_vector_creator(x, n, "x");
   Random_vector_creator(y, n, "y");

   Print_vector(x, n, "x ->");
   Print_vector(y, n, "y ->");
   
   double time_spent = 0.0;
   clock_t begin = clock();
   Vector_sum(x, y, z, n);
   clock_t end = clock();

   Print_vector(z, n, "The sum is");

   time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   printf("Suma de vector: %f seconds\n", time_spent);

   free(x);
   free(y);
   free(z);

   return 0;
} 

/* Obtener el orden de los vectores de stdin */
void Read_n(int* n_p /* out */) {
   printf("Cual es el orden?\n");
   scanf("%d", n_p);
   if (*n_p <= 0) {
      fprintf(stderr, "El orden deberia ser positivo\n");
      exit(-1);
   }
}

/* Asignar almacenamiento para los vectores */
void Allocate_vectors(
      double**  x_pp , 
      double**  y_pp , 
      double**  z_pp , 
      int       n    ) {
   *x_pp = malloc(n*sizeof(double));
   *y_pp = malloc(n*sizeof(double));
   *z_pp = malloc(n*sizeof(double));
   if (*x_pp == NULL || *y_pp == NULL || *z_pp == NULL) {
      fprintf(stderr, "No se puede asignar\n");
      exit(-1);
   }
}

void Random_vector_creator(
      double  a[]  , 
      int     n    , 
      char    vec_name[] ) {
   int i;
   printf("Vector generador %s\n", vec_name);

   for(i=0; i<n; i++){
      a[i]=rand()%100;
   }
}

/* Imprimir en pantalla el contenido  */
void Print_vector(
      double  b[] , 
      int     n   , 
      char    title[] ) {
   int i;
   printf("%s\n", title);
   for (i = n-10; i < n; i++)
      printf("%f ", b[i]);
   printf("\n");
} 

/* Sumar vectores */
void Vector_sum(
      double  x[]  , 
      double  y[]  , 
      double  z[]  , 
      int     n    ) {
   int i;

   for (i = 0; i < n; i++)
      z[i] = x[i] + y[i];
} 

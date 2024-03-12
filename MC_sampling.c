/* Program for using Monte Carlo (i.e., random) sampling to calculate
the evolution of f_0 in the two-hammer potential. */

#include <math.h> /* include value of pi */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* used for setting random seed */

/* parameters for our two hammers */
int t1 = 0, t2 = 100;
int n1 = 1, n2 = 3;
double A1 = 0.1, A2 = 0.2;

/* timepoints */
const double tstep = 0.1;
const int tfinal = 300;
const int num_tsteps = (int) (tfinal / tstep) + 1;
double ts[num_tsteps];
double tolerance = 0.9*tstep; /* tolerance for comparing t with t1,t2 */

/* values of theta and J at timepoints */
double thetas[num_tsteps];
double Js[num_tsteps];

/* Represents the Omega(J). */
double compute_Omega(double J) {
   /* parameters of Omega(J) */
   double a = 1. / sqrt(2);
   double b = 3 * sqrt(2) / pow(M_PI,2);

   return a / pow(1. + b*J, 1./3);
}

/* Compute the (theta,J) time series for one particle starting at 
   (theta_0, J_0), storing the results in thetas and Js. */
void compute_coords(double theta_0, double J_0) {

   /* initial Omega, theta, J, and t; these values will be 
   updated throughout the loop */
   double Omega = compute_Omega(J_0);
   double theta = theta_0, J = J_0;
   double t = 0;

   /* initial conditions */
   thetas[0] = theta_0, Js[0] = J_0;

   for (int i = 1; i < num_tsteps; i++) {
      /* update J, Omega iff there's a hammer */
      if (fabs(t - t1) < tolerance) {
         J += n1 * A1 * sin(n1 * theta);
         Omega = compute_Omega(J);
      }
      if (fabs(t - t2) < tolerance) {
         J += n2 * A2 * sin(n2 * theta);
         Omega = compute_Omega(J);
      }

      /* limit angular values to [0, 2pi) */
      theta += Omega * tstep;  
      thetas[i] = fmod(theta, 2*M_PI);

      Js[i] = J;
      t += tstep;
   }
}

/* Use Monte Carlo sampling to set a random initial condition 
   (theta_0, J_0). */
void MC_sample(double* pdTheta_0, double* pdJ_0) {

   double theta_max = 2*M_PI, J_max = 25.;

   *pdTheta_0 = ((double)rand()/(double)(RAND_MAX)) * theta_max;
   /* TODO: consider sampling J from f_0(J) */
   *pdJ_0 = ((double)rand()/(double)(RAND_MAX)) * J_max;
}

/* Save the theta and J series for N different particles; i.e.,
sets of initial conditions. */
void save_data_series(int N) {

   /* Save the t, theta, and J values in csv files.
      The t series is one row since it's the same for all 
      N particles, while thetas and Js each have N rows. */
   FILE *ts_csv, *thetas_csv, *Js_csv;
   int i, j; /* index variables */

   /* open files */
   ts_csv = fopen("ts_analytic.csv", "w");
   thetas_csv = fopen("thetas_analytic.csv", "w");
   Js_csv = fopen("Js_analytic.csv", "w");

   /* save time series */
   for (i = 0; i < num_tsteps; i++)
      fprintf(ts_csv, "%.2f,", ts[i]);
   fclose(ts_csv);

   /* save (theta, J) series for each particle */
   for (i = 0; i < N; i++) {
      /* set initial coords for this particle */
      double theta_0, J_0; 
      MC_sample(&theta_0, &J_0);

      compute_coords(theta_0, J_0);
      /* save (theta,J) series for this particle */
      for (j = 0; j < num_tsteps; j++) {
         fprintf(thetas_csv, "%.4f,", thetas[j]);
         fprintf(Js_csv, "%.4f,", Js[j]);
      }

      if (i == (N-1))
         break;
      fprintf(thetas_csv, "\n");
      fprintf(Js_csv, "\n");
   }

   fclose(thetas_csv);
   fclose(Js_csv);
}

/* Tests our implementaiton. */
int main(int argc, char *argv[])
{

   int N = 10;
   int seed = time(NULL);
   /* set random seed */
   srand(seed);

   /* initialize timepoints */
   for (int i = 0; i < num_tsteps; i++)
      ts[i] = i*tstep;

   save_data_series(N);

   return 0;
}
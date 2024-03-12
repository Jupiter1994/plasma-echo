/* Module for using the leapfrog method to solve 
Hamilton's equations for the two-hammer potential. */

#include <math.h> /* include value of pi */
#include <stdio.h>
#include <stdlib.h>

const double tstep = 0.1;
const int tfinal = 300;
const int num_tsteps = (int) (tfinal / tstep) + 1;

/* values of timepoints at integer steps */
double ts[num_tsteps];

/* values of theta and J at integer time steps */
double thetas[num_tsteps];
double Js[num_tsteps];

/* values of theta and J at half-integer time steps; 
J_half[i] is the timepoint between Js[i] and Js[i+1], and similarly
for theta */
double theta_half[num_tsteps]; /* as of 2/27, not being used */
double J_half[num_tsteps];

/* Represents the RHS of dtheta / dt = dH/dJ = Omega(J) for a given
J and at a given timepoint t. (Since Omega is independent of t,
I will omit t as a funciton parameter.) */
double dtheta_dt(double J) {
   /* parameters of Omega(J) */
   double a = 1. / sqrt(2);
   double b = 3 * sqrt(2) / pow(M_PI,2);

   return a / pow(1. + b*J, 1./3);
}

/* Represents the RHS of dJ / dt = -dH/dtheta for a given
theta and at a given timepoint t. */
double dJ_dt(double theta, double t) {
   /* parameters for our two hammers */
   int t1 = 0, t2 = 100;
   int n1 = 1, n2 = 3;
   double A1 = 0.1, A2 = 0.2;
   double tolerance = 0.9*tstep; /* tolerance for comparing t with t1,t2 */

   if (fabs(t - t1) < tolerance)
      return n1 * A1 * sin(n1 * theta);
   else if (fabs(t - t2) < tolerance)
      return n2 * A2 * sin(n2 * theta);
   else 
      return 0;
}

static void leapfrog() {

   /* RK2 to get the initial values for half-integer values 
   [do we need this given the kick-drift-kick implementation?] */


   /* kick-drift-kick leapfrog routine, using theta,J instead of x,v
   TODO: double-check this pseudocode
   for t in range(...):
      J_(n+1/2) = J_n + (dJ/dt * tstep/2) [dJ/dt at theta_n, t_n]
      theta_(n+1) = theta_n + (dtheta_dt * tstep) [dtheta_dt at J_(n+1/2)]
      J_(n+1) = J_(n+1/2) + (dJ/dt * tstep/2) [dJ_dt at theta_(n+1), t_(n+1)]

   */
   
   /* save the t, theta, and J values in csv files */
   FILE *ts_csv, *thetas_csv, *Js_csv;

   /* arbitrary initial conditions */
   double theta_0 = 0.13, J_0 = 5.1;
   thetas[0] = theta_0, Js[0] = J_0, ts[0] = 0.;

   /* open files */
   ts_csv = fopen("ts.csv", "w");
   thetas_csv = fopen("thetas.csv", "w");
   Js_csv = fopen("Js.csv", "w");
   
   for (int i = 0; i < num_tsteps-1; i++) {
      ts[i+1] = ts[i] + tstep; /* t_(n+1) timepoint */

      J_half[i] = Js[i] + (dJ_dt(thetas[i], ts[i])*tstep/2);
      thetas[i+1] = thetas[i] + dtheta_dt(J_half[i])*tstep;
      Js[i+1] = J_half[i] + (dJ_dt(thetas[i+1], ts[i+1])*tstep/2);

      /* limit angular values to [0, 2pi) */
      thetas[i] = fmod(thetas[i], 2*M_PI);

      /* write out values at t_n */
      fprintf(ts_csv, "%.10f,", ts[i]);
      fprintf(thetas_csv, "%.10f,", thetas[i]);
      fprintf(Js_csv, "%.10f,", Js[i]);
   }

   /* write out final values */
   fprintf(ts_csv, "%.10f", ts[num_tsteps-1]);
   thetas[num_tsteps-1] = fmod(thetas[num_tsteps-1], 2*M_PI);
   fprintf(thetas_csv, "%.10f", thetas[num_tsteps-1]);
   fprintf(Js_csv, "%.10f", Js[num_tsteps-1]);

   fclose(ts_csv);
   fclose(thetas_csv);
   fclose(Js_csv);
}

/* Tests our implementaiton. */
int main(int argc, char *argv[])
{
   leapfrog();

   return 0;
}
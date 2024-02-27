/* Module for using the leapfrog method to solve 
a set of coupled differential equations. */

#include <math.h> /* include value of pi */
#include <stdio.h>
#include <stdlib.h>

const double tstep = 0.1;
const int tfinal = 300;
const int num_tsteps = tfinal / tstep;

/* values of theta and J at integer time steps */
int J[num_tsteps];
int theta[num_tsteps];

/* values of theta and J at half-integer time steps */
int J_half[num_tsteps];
int theta_half[num_tsteps];

/* Represents the RHS of dtheta / dt = dH/dJ = Omega(J) for a given
J and at a given timepoint t. (Since Omega is independent of t,
I will omit t as a funciton parameter.) */
double dtheta_dt(double J) {
   /* parameters of Omega(J) */
   double a = 1. / sqrt(2);
   double b = 3. * sqrt(2) / pow(M_PI,2);

   return a / pow(1 + b*J, 1/3);
}

/* Represents the RHS of dJ / dt = -dH/dtheta for a given
theta and at a given timepoint t. */
double dJ_dt(double theta, double t) {
   /* parameters for our two hammers */
   int t1 = 0, t2 = 100;
   int n1 = 1, n2 = 3;
   double A1 = 0.1, A2 = 0.2;

   if (t == t1)
      return n1 * A1 * sin(n1 * theta);
   else if (t == t2)
      return n2 * A2 * sin(n2 * theta);
   else 
      return 0;
}

static void leapfrog() {

   /* RK2 to get the initial values for half-integer values 
   [do we need this given the kick-drift-kick implementation?] */



   /* kick-drift-kick leapfrog routine, using theta,J instead of x,v
   for t in range(...):
      J_(n+1/2) = J_n + (dJ/dt * tstep/2)
      theta_(n+1) = theta_n + (dtheta_dt * tstep)
      J_(n+1) = J_(n+1/2) + (dJ/dt * tstep/2)

   */

   

}

/* Tests our implementaiton. */
int main(int argc, char *argv[])
{
   printf("Hello world!");
   return 0;
}
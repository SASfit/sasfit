/*
 * Author(s) of this file:
 *   <your name> (<email address>)
 */

#include "include/private.h"
#include <sasfit_error_sq.h>

// define shortcuts for local parameters/variables
#define R	param->p[0]
#define N	param->p[1]
#define Q   param->p[MAXPAR-1]

scalar RLCA_F(scalar i, scalar d, scalar e, scalar f, int m) {
    if (m==1) return d*(i-e)/((i-e)+f);
    return d*gsl_pow_int(i-e,m)/(gsl_pow_int(i-e,m)+f);
}

scalar gRLCA(scalar r, void *pam)
{
    sasfit_param * param;
	param = (sasfit_param *) pam;
    scalar Nnn, a, b, c, h, gamma,xi, kf, Df;

	h = 0.91;
	kf=0.94;kf=0.33;
	Df=2.05;
    Nnn = RLCA_F(N,2.0415, 1.1511, 1.0086,1);
    a   = RLCA_F(N,0.0138, 2.7544, 4.1792, 2);
    if (N<10) {
        b = 0;
    } else {
        b = RLCA_F(N, 0.4857, 9.6836, 11.6665, 1);
    }
    xi = h*R*pow(N/kf,1./Df);
    if (N<3.7786) {
        gamma = 3;
    } else {
        gamma = RLCA_F(N, 2.16, 0.1966, -3.5926, 2);
    }
    c = (N-1-Nnn-4*M_PI*a/(b+3)*(pow(4,b+3)-pow(2,b+3)))/
         (4*M_PI/gamma*pow(xi/R,Df)*gsl_sf_gamma(Df/gamma)*(1-gsl_sf_gamma_inc(pow(4*R/xi,gamma),Df/gamma)));
    c = (gamma*((3 + b)*(-1 + N - Nnn) + pow(2,5 + b)*a*M_PI - pow(4,4 + b)*a*M_PI))/
        (4.*(3 + b)*M_PI*pow(xi/R,Df)*
            gsl_sf_gamma_inc(Df/gamma,pow(4,gamma)*pow(R/xi,gamma)));
    if (2*R<=r && r<=4*R) {
        return a/pow(R,b+3)*pow(r,b);
    } else if (r>4*R) {
        return c/pow(R,Df)*pow(r,Df-3)*exp(-pow(r/xi,gamma));
    }
	return  0;
}

scalar zRfunc(scalar r, void * pam)
{
    sasfit_param * param;
	param = (sasfit_param *) pam;
	return  gRLCA(r,pam)*4*M_PI*r*r*gsl_sf_bessel_j0(Q*r);
}

scalar sasfit_sq_rlca_incl_nn_pertubation(scalar q, sasfit_param * param)
{
    scalar qR, Nnn;
    scalar *aw, res,err,eps_nriq;
    int lenaw=4000;
	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	SASFIT_CHECK_COND1((q < 0.0), param, "q(%lg) < 0",q);
	SASFIT_CHECK_COND1((R < 0.0), param, "R(%lg) < 0",R); // modify condition to your needs
	SASFIT_CHECK_COND1((N < 1.0), param, "N(%lg) < 1",N); // modify condition to your needs

	// insert your code here
	Q=q;
//	return RLCA_F(q, 2.16, 0.1966, -3.5926, 2);
//	return gRLCA(q,param);

    qR= q*R;
	aw = (scalar *)malloc((lenaw)*sizeof(scalar));
	eps_nriq=sasfit_eps_get_nriq();
    sasfit_intdeoini(lenaw, GSL_DBL_MIN, eps_nriq, aw);
    sasfit_intdeo(&zRfunc,2*R,q, aw, &res, &err, param);
    free(aw);

    Nnn = RLCA_F(N,2.0415, 1.1511, 1.0086,1);
	return (1+Nnn*gsl_sf_bessel_j0(2*qR)+res);
}

scalar sasfit_sq_rlca_incl_nn_pertubation_f(scalar q, sasfit_param * param)
{
	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	// insert your code here
	return 0.0;
}

scalar sasfit_sq_rlca_incl_nn_pertubation_v(scalar q, sasfit_param * param, int dist)
{
	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	// insert your code here
	return 0.0;
}

/*
 * Author(s) of this file:
 *   Joachim Kohlbrecher (joachim.kohlbrecher@psi.ch)
 */

#include "include/private.h"
#include <sasfit_error_ff.h>

// define shortcuts for local parameters/variables
#define RG	param->p[0]
#define WI	param->p[1]
#define PSI_DEG	param->p[2]
#define Q   param->p[MAXPAR-1]
#define PSI	param->p[MAXPAR-2]

scalar fexpQRn2(scalar x,void *pam){
	sasfit_param * param;
	param = (sasfit_param *) pam;
	scalar mu;
	mu = fabs(x);
	return gsl_pow_2(Q*RG)*(mu+gsl_pow_4(M_PI)/180.*gsl_pow_2(mu*WI*cos(PSI))*(1+mu-mu*mu/4.-2*gsl_pow_3(mu)+gsl_pow_4(mu)));
}

scalar gsl_fexpQRn2(scalar x,sasfit_param * param){
	return 2*(1-x)*exp(-fexpQRn2(x,param));
}

int shearflow_kernel_cub(unsigned ndim, const double *x, void *pam,
      unsigned fdim, double *fval) {
	sasfit_param * param;
	param = (sasfit_param *) pam;
	if ((ndim < 1) || (fdim < 1)) {
		sasfit_out("false dimensions fdim:%d ndim:%d\n",fdim,ndim);
		return 1;
	}
	fval[0]=gsl_fexpQRn2(x[0],param);
	return 0;
}

scalar shearflow_kernel_OOURA(scalar x, void *pam) {
	sasfit_param * param;
	param = (sasfit_param *) pam;
	return gsl_fexpQRn2(x,param);
}

scalar sasfit_ff_polymer_under_shearflow(scalar q, sasfit_param * param)
{	scalar *aw, res,err,sum;
    scalar cubxmin[2], cubxmax[2], fval[1], ferr[1];
    int intstrategy, lenaw=4000;

	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	SASFIT_CHECK_COND1((q < 0.0), param, "q(%lg) < 0",q);
	SASFIT_CHECK_COND1((RG < 0.0), param, "Rg(%lg) < 0",RG); // modify condition to your needs
	SASFIT_CHECK_COND1((WI < 0.0), param, "Wi(%lg) < 0",WI); // modify condition to your needs

	// insert your code here

	PSI = sasfit_param_override_get_psi(PSI_DEG * M_PI/180.);
	Q = q;

	cubxmin[0]=0;
	cubxmax[0]=1;

	intstrategy = sasfit_get_int_strategy();
//    intstrategy=OOURA_CLENSHAW_CURTIS_QUADRATURE;
	switch(intstrategy) {
    case OOURA_DOUBLE_EXP_QUADRATURE: {
            aw = (scalar *)malloc((lenaw)*sizeof(scalar));
            sasfit_intdeini(lenaw, GSL_DBL_MIN, sasfit_eps_get_nriq(), aw);
            sasfit_intde(&shearflow_kernel_OOURA,0,1, aw, &res, &err, param);
			sum=res;
            free(aw);
            break;
            }
    case OOURA_CLENSHAW_CURTIS_QUADRATURE: {
            aw = (scalar *)malloc((lenaw+1)*sizeof(scalar));
            sasfit_intccini(lenaw, aw);
            sasfit_intcc(&shearflow_kernel_OOURA, 0,1, sasfit_eps_get_nriq(), lenaw, aw, &res, &err,param);
			sum=res;
            free(aw);
            break;
            }
    case H_CUBATURE: {
			hcubature(1, &shearflow_kernel_cub,param,1, cubxmin, cubxmax,
				100000, 0.0, sasfit_eps_get_nriq(), ERROR_PAIRED,
				fval, ferr);
			sum = fval[0];
            break;
            }
    case P_CUBATURE: {
			pcubature(1, &shearflow_kernel_cub,param,1, cubxmin, cubxmax,
				100000, 0.0, sasfit_eps_get_nriq(), ERROR_PAIRED,
				fval, ferr);
			sum = fval[0];
            break;
            }
    default: {
//		    sasfit_out("This is default sasfit_integrate routine\n");
			sum = sasfit_integrate(0,1,&gsl_fexpQRn2,param);
            break;
            }
    }
    return sum;
}

scalar sasfit_ff_polymer_under_shearflow_f(scalar q, sasfit_param * param)
{
	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	// insert your code here
	return 0.0;
}

scalar sasfit_ff_polymer_under_shearflow_v(scalar q, sasfit_param * param, int dist)
{
	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	// insert your code here
	return 0.0;
}

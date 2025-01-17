/*
 * Author(s) of this file:
 *   Joachim Kohlbrecher (joachim.kohlbrecher@psi.ch)
 */

#include "include/private.h"
#include <sasfit_error_ff.h>

// define shortcuts for local parameters/variables
#define ETA	param->p[0]
#define XI	param->p[1]
#define D	param->p[2]

scalar sasfit_ff_teubner_strey(scalar q, sasfit_param * param)
{
	scalar a, b, k, c;

	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	SASFIT_CHECK_COND1((q < 0.0), param, "q(%lg) < 0",q);
	SASFIT_CHECK_COND1((ETA < 0.0), param, "eta(%lg) < 0",ETA); // modify condition to your needs
	SASFIT_CHECK_COND1((XI < 0.0), param, "xi(%lg) < 0",XI); // modify condition to your needs
	SASFIT_CHECK_COND1((D < 0.0), param, "d(%lg) < 0",D); // modify condition to your needs

	// insert your code here

	SASFIT_ASSERT_PTR(param);

	k = 2.*M_PI/D;
	a = k*k + 1./(XI*XI);
	b = k*k - 1./(XI*XI);
	c = a*a - 2.*b*q*q + q*q*q*q;

	SASFIT_CHECK_COND1((c == 0.0), param, "c == 0",c);

	return ETA*ETA*8*M_PI/XI/c;
}

scalar sasfit_ff_teubner_strey_f(scalar q, sasfit_param * param)
{
	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	// insert your code here
	return 0.0;
}

scalar sasfit_ff_teubner_strey_v(scalar q, sasfit_param * param, int dist)
{
	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	// insert your code here
	return 0.0;
}


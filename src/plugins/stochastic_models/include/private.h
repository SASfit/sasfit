/*
 * Author(s) of this file:
 *   <your name> (<email address>)
 */

#ifndef STOCHASTIC_MODELS_PRIVATE_H
#define STOCHASTIC_MODELS_PRIVATE_H

/*
 * Header file for the implementation of the form factor itself.
 */

// optional, depends on form factor implementation
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf.h>

// mandatory, no adjustments necessary
#include <sasfit_common.h>

// mandatory, no adjustments necessary
#ifdef MAKE_SASFIT_PLUGIN
  // mandatory, no adjustments necessary
  #include <sasfit_plugin.h>

  SASFIT_PLUGIN_INFO_DECL;

#else


#endif

// adjust according to the plugins name
#include "sasfit_stochastic_models.h"

//
// add local defines here:
// #define P0 param->p[0]
//
#define SCALE	param->p[0]
#define FP	param->p[1]
#define MU	param->p[2]
#define SIGMA	param->p[3]
#define Q   param->p[MAXPAR-1]

scalar gammaBoolean(scalar, void *);
scalar gammaDeadLeaves(scalar, void *);
double ThetaK(scalar , sasfit_param *);

#endif // end of file

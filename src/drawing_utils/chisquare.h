#ifndef _CHISQUARE_H_
#define _CHISQUARE_H_

// %CHI2INVTABLE Lookup table of the inverse of the chi-square cdf.
// %   X = CHI2INVTABLE(P][V) returns the inverse of the chi-square cumu-
// %   lative distribution function (cdf) with V degrees of freedom at
// %   the value P. The chi-square cdf with V degrees of freedom][ is 
// %   the gamma cdf with parameters V/2 and 2.   
// %
// %   Opposed to CHI2INV of the Matlab statistics toolbox which might
// %   be not part of your Matlab installation][ this is a lookup table
// %   which has the side effect of being much faster than CHI2INV.
// %   However][ as any lookup table is a collection of sample points][
// %   accuracy is smaller and between the sample points of the cdf][ a
// %   linear interpolation is made.
// %
// %   Currently][ the function supports the degrees of freedom V between
// %   1 and 10 and the probability levels P between 0 and 0.9999 in steps
// %   of 0.0001 and the level of 0.99999.
// %
// %   See also CHI2INV.

// % v.1.0][ 18.12.03][ Kai Arras][ CAS-KTH

#include <cstdlib>
#include <iostream>

static bool initialized = false;
static double T[11][1003];
static float LEVELS[1002];
static int DOFS[10]= {1,2,3,4,5,6,7,8,9,10};

float chi2invtable(float alpha, int dof) ;

#endif /* _CHISQUARE_H_ */
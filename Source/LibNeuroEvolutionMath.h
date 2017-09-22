/*
    Programmer: Lucas Winkelman
    File: LibNeuroEvolutionMath.h
    Date: 9/22/2017
    Purpose: LibNeuroEvolutionMath.h contains declarations for math functions
        needed by LibNeuroEvolution.
*/

#ifndef LIBNEUROEVOLUTIONMATH_H
#define LIBNEUROEVOLUTIONMATH_H

#include <cstdlib>

namespace LNE
{

    float GetProb ( ) ;

    float Relu ( float Input ) ;

    float Heaviside ( float Input ) ;
}

#endif

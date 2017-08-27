#ifndef LIBNEUROEVOLUTIONMATH_H
#define LIBNEUROEVOLUTIONMATH_H

#include <cstdlib>

namespace LNE
{

    float GetProb ( )
    {
        float Output = ( ( float ) rand ( ) ) / RAND_MAX ;
        return Output ;
    }

    float Relu ( float Input )
    {
        if ( Input < 0 )
        {
            Input = 0 ;
        }
        return Input ;
    }
}

#endif

#include "LibNeuroEvolutionMath.h"

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

    float Heaviside ( float Input )
    {
        if ( Input < 0.5 )
        {
            Input = 0 ;
        }
        else
        {
            Input = 1 ;
        }
        return Input ;
    }
}
